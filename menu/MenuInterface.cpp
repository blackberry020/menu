#include "MenuInterface.h"

// collect data from models
// update output device state;
void MenuInterface::update() {
	outputDevice <<
		getInstructions() + 
		"\n" +
		"\n" + openedElementsSequence.top()->getContent();
}

// By default, edit mode is false (when device started)
MenuInterface::MenuInterface(OutputDevice * oDevice, FolderElement* rootFolder) : outputDevice(oDevice), isEditMode(false) {
	// root folder is always opened
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

}
void MenuInterface::keyPressed(Key key) {
	AbstractElement* curElement = openedElementsSequence.top();
	if (isEditMode) {
		switch (key)
		{
			case Key::Up:
				curElement->getCurSubElement()->incCurValueDigit();
				break;

			case Key::Down:
				curElement->getCurSubElement()->decCurValueDigit();
				break;

			// 1[0]0 Maybe (right = decrease digit) ? 10[0] ????
			case Key::Right:
				curElement->getCurSubElement()->incDigit();
				break;

			// same as with Right
			case Key::Left:
				curElement->getCurSubElement()->decDigit();
				break;

			case Key::Escape:
				curElement->getCurSubElement()->saveValueChanges();
				break;

			// ????
			case Key::Enter:
				break;

			default:
				break;
		}
	}
	else {

		switch (key)
		{
		case Key::Up:
			// we cannot up, if we are at the root
			if (openedElementsSequence.size() > 1)
				openedElementsSequence.pop();
			break;
		case Key::Down:
			if (curElement->requestOpenSubElement()) {
				openedElementsSequence.push(curElement->getCurSubElement());
			}
			break;
		case Key::Left:
			curElement->goPrevElement();
			break;
		case Key::Right:
			curElement->goNextElement();
			break;
		case Key::Enter:
			isEditMode = curElement->requestEditModeSubElement();
			break;

		// ???
		case Key::Escape:
			//ignore
			break;
		default:
			break;
		}

	}

	update();
}