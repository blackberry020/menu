#pragma once
#include "AbstractElement.h"
#include <stack>
#include "FolderElement.h"
#include "OutputDevice.h"
#include "Key.h"

class MenuInterface
{

private:

	std::stack <AbstractElement*> openedElementsSequence;
	FolderElement* rootFolder;
	OutputDevice* outputDevice;
	SettingsStorageInterface* storage;

	bool isEditMode;

protected:

	virtual const std::string getInstructions();

public:

	virtual ~MenuInterface();

	explicit MenuInterface(OutputDevice* oDevice, SettingsStorageInterface* _storage, FolderElement* rootFolder);

	virtual void update();

	void refreshData();

	OutputDevice* getOutputDevice();

	virtual void keyPressed(Key);
};

