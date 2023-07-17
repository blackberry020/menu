#include "FolderElement.h"

bool FolderElement::isOpenable() {
	return true;
}

bool FolderElement::isEditable() {
	return false;
}

std::string FolderElement::getContent() {
	//!!!!!
	return "CCC";
}

void FolderElement::saveValueChanges()
{
	// save child!!!!
	getCurSubElement()->saveValueChanges();
}
