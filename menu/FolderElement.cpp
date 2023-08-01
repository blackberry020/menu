#include "FolderElement.h"

bool FolderElement::isOpenable() {
	return true;
}

bool FolderElement::isEditable() {
	return false;
}


FolderElement::FolderElement(std::string name, CArray <AbstractElement*> _subElements) :
	AbstractElement(name, _subElements)
{

}

FolderElement::FolderElement(std::string name, SettingsStorageInterface* storageInterface, CArray <AbstractElement*> _subElements) :
	AbstractElement(name, storageInterface, _subElements)
{
}

// Display a current child
std::string FolderElement::getContent(bool isEditMode) {
	return "[" + getElementName() + "]\n\t-> " + getCurSubElement()->getPreview(isEditMode);
}

std::string FolderElement::getPreview(bool isEditMode) {
	return getElementName();
}

