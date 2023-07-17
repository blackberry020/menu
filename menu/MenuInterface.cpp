#include "MenuInterface.h"

// collect data from models
// update output device state;
void MenuInterface::update() {
	
	outputDevice->onUpdate(
		getInstructions() + 
		"\n" + openedElementsSequence.top()->getContent()
	);
}

// By default, edit mode is false (when device started)
MenuInterface::MenuInterface(OutputDevice * device) : outputDevice(device), isEditMode(false) {

}

const std::string MenuInterface::getInstructions() {
	return "use arrows for navigation:" \
		"\n left and right for moving between folders on the same level, " \
		"\n down and up for moving between layers" \
		"\n enter to edit a value" \
		"\n ESC to undo changes in value"
		"\n and arrows for editing value's digits";
}
void MenuInterface::keyPressed(Key key) {
	AbstractElement* curElement = openedElementsSequence.top();
	if (isEditMode) {
		switch (key)
		{
			case Key::Up:
				curElement->incCurValueDigit();
				break;

			case Key::Down:
				curElement->decCurValueDigit();
				break;

			// 1[0]0 Maybe (right = decrease digit) ? 10[0] ????
			case Key::Right:
				curElement->incDigit();
				break;

			// same as with Right
			case Key::Left:
				curElement->decDigit();
				break;

			case Key::Escape:
				curElement->saveValueChanges();
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
			isEditMode = curElement->requestEditMode();
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