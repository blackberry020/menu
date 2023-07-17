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
	explicit MenuInterface(OutputDevice* device);
protected:

	// Method, which provide outputDevice an output;
	void update();

	// Method, which calls when key is Pressed.
	// With default binding
	virtual void keyPressed(Key);

	virtual const std::string getInstructions();

	virtual ~MenuInterface() = 0;
private:

	// abstract element also can have a sub element;
	std::stack <AbstractElement*> openedElementsSequence;

	OutputDevice* outputDevice;

	bool isEditMode;
	
};

