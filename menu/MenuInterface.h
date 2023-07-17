#pragma once
#include "AbstractElement.h"
#include <stack>
#include "FolderElement.h"
#include "OutputDevice.h"

enum class Key {
	Up, Down, Left, Right, Enter, Escape
};

class MenuInterface
{	
public:
	MenuInterface(OutputDevice* device) : outputDevice(device) { }
protected:
	bool isEditMode;
	OutputDevice* outputDevice;

	// abstract element also can have a sub element;
	std::stack <AbstractElement*> openedElementsSequence;

	void update();
	virtual void keyPressed(Key);
	virtual ~MenuInterface() = 0;
};

