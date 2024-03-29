#include "AbstractElement.h"

AbstractElement::AbstractElement(std::string name, CArray <AbstractElement*> _subElements) : 
	elementName(name),
	curIndexOfSubElement(0),
	subElements(_subElements)
{
	amountOfSubElements = subElements.size();
}

AbstractElement::AbstractElement(std::string name, SettingsStorageInterface* storageInterface, CArray <AbstractElement*> _subElements) :
	elementName(name),
	curIndexOfSubElement(0),
	subElements(_subElements)
{
	injectStorage(storageInterface);
	amountOfSubElements = subElements.size();
}

AbstractElement::~AbstractElement()
{
	for (int i = 0; i < subElements.size(); i++) {
		if (subElements[i] != nullptr)
			delete subElements[i];
	}
}

AbstractElement::AbstractElement(std::string name, bool recalcAtStart) :
	elementName(name), recalculateAtStart(recalcAtStart),
	curIndexOfSubElement(0)
{

}

std::string AbstractElement::getPrefix()
{
	return std::string();
}

std::string AbstractElement::getPostfix()
{
	return std::string();
}

std::string AbstractElement::getElementName() {
	return elementName;
}

CArray <AbstractElement*> AbstractElement::getSubElements() {
	return subElements;
};

SettingsStorageInterface* AbstractElement::getStorage() {
	return storage;
};

int AbstractElement::getAmountOfSubElements() {
	return amountOfSubElements;
};

int AbstractElement::getCurIndexOfSubElement() {
	return curIndexOfSubElement;
}
bool AbstractElement::getRecalculateAtStartStatus()
{
	return recalculateAtStart;
}
void AbstractElement::setRecalculateAtStartStatus(bool s)
{
	recalculateAtStart = s;
}
void AbstractElement::updateElement()
{
	for (int i = 0; i < subElements.size(); i++)
		subElements[i]->updateElement();
}
void AbstractElement::dataChanged(std::string changedId)
{
}
;

void AbstractElement::injectPrettyNotifier(PrettyNotifier* notifier)
{
}

void AbstractElement::prepareForEditing() {
	// no reaction by default
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
}

void AbstractElement::addNewDigitLeft() {
	// no reaction by default
}

void AbstractElement::saveChanges()
{
	for (int i = 0; i < subElements.size(); i++)
		subElements[i]->saveChanges();
}
void AbstractElement::applyChanges()
{
}
void AbstractElement::tryNotify()
{
	for (int i = 0; i < subElements.size(); i++)
		subElements[i]->tryNotify();
}
;

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
	if (curIndexOfSubElement + 1 < amountOfSubElements)
		curIndexOfSubElement++;
	else curIndexOfSubElement = 0;
}

void AbstractElement::injectStorage(SettingsStorageInterface* storageInterface)
{
	storage = storageInterface;
	for (int i = 0; i < subElements.size(); i++) {
		subElements[i]->injectStorage(storage);
	}
}

void AbstractElement::postInitRecalculation()
{
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