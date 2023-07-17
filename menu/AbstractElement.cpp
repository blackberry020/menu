#include "AbstractElement.h"

AbstractElement::AbstractElement(std::string name) : elementName(name), curIndexOfSubElement(0)
{

}

AbstractElement::AbstractElement(std::string name, SettingsStorageInterface* storageInterface) : elementName(name), curIndexOfSubElement(0)
{
	injectStorage(storageInterface);
}

std::string AbstractElement::getElementName() {
	return elementName;
}

void AbstractElement::incCurValueDigit() {
	// no reaction by default
};

void AbstractElement::decCurValueDigit() {
	// no reaction by default
};

void AbstractElement::incDigit() {
	// no reaction by default
};

void AbstractElement::decDigit() {
	// no reaction by default
};

void AbstractElement::saveValueChanges() {
	// no reaction by default
};


AbstractElement* AbstractElement::getCurSubElement() {
	return subElements[curIndexOfSubElement];
}

void AbstractElement::goPrevElement() {
	if (curIndexOfSubElement) curIndexOfSubElement--;
}

void AbstractElement::goNextElement() {
	if (curIndexOfSubElement != amountOfSubElements - 1) curIndexOfSubElement--;
}

void AbstractElement::injectStorage(SettingsStorageInterface* storageInterface)
{
	storage = storageInterface;
	for (AbstractElement* el : subElements) {
		el->injectStorage(storage);
	}
}

// for sub elements !!!
bool AbstractElement::requestEditMode() {
	return getCurSubElement()->isEditable();
}

// for sub elements !!!
bool AbstractElement::requestOpenSubElement() {
	return getCurSubElement()->isOpenable();
}

void AbstractElement::incAmountOfChildrenPages() {
	amountOfSubElements++;
};