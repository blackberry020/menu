#include "FolderElement.h"

bool FolderElement::isOpenable() {
	return true;
}

bool FolderElement::isEditable() {
	return false;
}


// Display a current child
std::string FolderElement::getContent() {
	return getCurSubElement()->getContent();
}


void FolderElement::saveValueChanges()
{
	// nothing to save, because cannot edit folder
}
