#include "MenuInterface.h"

void MenuInterface::update() {
	// collect data from models
	// update output device state;
	outputDevice->onUpdate(openedElementsSequence.top()->getContent());
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

			// 1[0]0 Maybe right = decrease digit? 10[0] ????
			case Key::Right:
				curElement->incDigit();
				break;

			// same
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