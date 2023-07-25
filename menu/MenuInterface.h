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

	SettingsStorageInterface* storage;

	bool isEditMode;
protected:

	virtual void update();

	virtual const std::string getInstructions();

public:

	virtual ~MenuInterface();

	explicit MenuInterface(OutputDevice* oDevice, SettingsStorageInterface* _storage, FolderElement* rootFolder);

	OutputDevice* getOutputDevice();

	virtual void keyPressed(Key);
};

