#include "FolderElement.h"

bool FolderElement::isOpenable() {
	return true;
}

void FolderElement::postInitRecalculation()
{
	for (int i = 0; i < getSubElements().size(); i++) {
		getSubElements()[i]->postInitRecalculation();
	}
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
	return getCurSubElement()->getPreview(isEditMode);
}

std::string FolderElement::getPreview(bool isEditMode) {
	return getElementName();
}

