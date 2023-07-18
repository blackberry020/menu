#include "FolderElement.h"

bool FolderElement::isOpenable() {
	return true;
}

bool FolderElement::isEditable() {
	return false;
}


FolderElement::FolderElement(std::string name, std::vector <AbstractElement*> _subElements) :
	AbstractElement(name, _subElements)
{

}

FolderElement::FolderElement(std::string name, SettingsStorageInterface* storageInterface, std::vector <AbstractElement*> _subElements) :
	AbstractElement(name, storageInterface, _subElements)
{
}

// Display a current child
std::string FolderElement::getContent() {
	return "[" + getElementName() + "]\n\t-> " + getCurSubElement()->getElementName();
}

