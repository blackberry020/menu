#include "AbstractElement.h"

AbstractElement::AbstractElement(std::string name, std::vector <AbstractElement*> _subElements) : 
	elementName(name),
	curIndexOfSubElement(0),
	subElements(_subElements)
{
	amountOfSubElements = subElements.size();
}

AbstractElement::AbstractElement(std::string name, SettingsStorageInterface* storageInterface, std::vector <AbstractElement*> _subElements) :
	elementName(name),
	curIndexOfSubElement(0),
	subElements(_subElements)
{
	injectStorage(storageInterface);
	amountOfSubElements = subElements.size();
}

AbstractElement::~AbstractElement()
{
	amountOfSubElements = subElements.size();
}

AbstractElement::AbstractElement(std::string name) :
	elementName(name),
	// empty subElements (no children)
	curIndexOfSubElement(0)
{

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
	if (curIndexOfSubElement)
		curIndexOfSubElement--;
	else
		curIndexOfSubElement = amountOfSubElements - 1;
}

void AbstractElement::goNextElement() {
	if (curIndexOfSubElement < amountOfSubElements)
		curIndexOfSubElement++;
	else curIndexOfSubElement = 0;
}

void AbstractElement::injectStorage(SettingsStorageInterface* storageInterface)
{
	storage = storageInterface;
	for (AbstractElement* el : subElements) {
		el->injectStorage(storage);
	}
}

// for sub elements !!!
bool AbstractElement::requestEditModeSubElement() {
	return getCurSubElement()->isEditable();
}

// for sub elements !!!
bool AbstractElement::requestOpenSubElement() {
	return getCurSubElement()->isOpenable();
}

void AbstractElement::incAmountOfChildrenPages() {
	amountOfSubElements++;
};