#pragma once
#include "AbstractElement.h"
#include <stack>
#include "FolderElement.h"
#include "OutputDevice.h"
#include "Key.h"

class MenuInterface
{

private:

	// abstract element also can have a sub element;
	std::stack <AbstractElement*> openedElementsSequence;

	OutputDevice* outputDevice;

	bool isEditMode;
protected:

	virtual void update();

	virtual const std::string getInstructions();

	virtual ~MenuInterface();

public:
	explicit MenuInterface(OutputDevice* oDevice, FolderElement* rootFolder);

	OutputDevice* getOutputDevice();

	virtual void keyPressed(Key);

	~MenuInterface();
};

