#pragma once
#include "AbstractElement.h"
#include <stack>
#include "FolderElement.h"

enum Key {

};

class MenuInterface
{
	virtual void keyPressed(Key) = 0;
	bool isEditMode;
	stack <FolderElement*> openedFoldersSequence;
	virtual void update() = 0;
};

