#include "MenuInterface.h"
#include <fstream>
using namespace std;

// collect data from models
// update output device state;
void MenuInterface::update() {
	outputDevice <<
		getInstructions() + 
		"\n" +
		"\n" + openedElementsSequence.top()->getContent(isEditMode);
}

MenuInterface::MenuInterface(OutputDevice * oDevice, SettingsStorageInterface* _storage, FolderElement* rootFolder) : 
	outputDevice(oDevice),
	storage(_storage),
	isEditMode(false) {

	// root folder is always opened
	rootFolder->injectStorage(storage);
	openedElementsSequence.push(rootFolder);
	update();
}


OutputDevice* MenuInterface::getOutputDevice()
{
	return outputDevice;
}

const std::string MenuInterface::getInstructions() {
	return "use arrows for navigation:"
		"\n left and right for moving between folders on the same level, "
		"\n down and up for moving between layers"
		"\n enter to edit a value"
		"\n ESC to undo changes in value"
		"\n and arrows for editing value's digits"
		"\n\n Extra (for debugging): "
		"\n\t [FOLDERNAME]\t- current opened folder" 
		"\n\t -> ELEMENT\t- current selected element in folder";
}
MenuInterface::~MenuInterface()
{	

	if (outputDevice != nullptr) 
		delete outputDevice;

	if (storage != nullptr)
		delete storage;
	
	while (openedElementsSequence.size() != 1) {
		openedElementsSequence.pop();
	}

	delete openedElementsSequence.top();
	openedElementsSequence.pop();
}

void MenuInterface::keyPressed(Key key) {

	AbstractElement* curElement = openedElementsSequence.top();

	if (isEditMode) {

		switch (key)
		{
			case Key::LongLeft:
				curElement->getCurSubElement()->addNewDigitLeft();
				break;

			case Key::Up:
				curElement->getCurSubElement()->incCurValueDigit();
				break;

			case Key::Down:
				curElement->getCurSubElement()->decCurValueDigit();
				break;

			case Key::Right:
				curElement->getCurSubElement()->decDigit();
				break;

			case Key::Left:
				curElement->getCurSubElement()->incDigit();
				break;

			case Key::Escape:
				isEditMode = false;
				curElement->getCurSubElement()->cancelValueChanges();
				break;

			case Key::Enter:
				isEditMode = false;
				curElement->getCurSubElement()->saveChanges();
				break;

			default:
				break;
		}
	}
	else {

		switch (key)
		{
		case Key::Up:
			//if (openedElementsSequence.size() > 1)
			//	openedElementsSequence.pop();
			break;
		case Key::Down:
			//if (curElement->requestOpenSubElement()) {
			//	openedElementsSequence.push(curElement->getCurSubElement());
			//}
			break;
		case Key::Left:
			curElement->goPrevElement();
			break;
		case Key::Right:
			curElement->goNextElement();
			break;
		case Key::Enter:
			isEditMode = curElement->requestEditModeSubElement();
			if (isEditMode)
				curElement->getCurSubElement()->prepareForEditing();
			else if (curElement->requestOpenSubElement()) {
				openedElementsSequence.push(curElement->getCurSubElement());
			}
			break;

		case Key::Escape:
			if (openedElementsSequence.size() > 1)
				openedElementsSequence.pop();
			break;
		default:
			break;
		}

	}

	update();
}