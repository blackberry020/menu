#pragma once
#include <string>
#include "MenuInterface.h"
#include "Key.h"
class InputDevice
{
private:
	MenuInterface* menuInterface;
public:
	explicit InputDevice(MenuInterface* menu);

	friend InputDevice* operator<<(InputDevice* device, const Key& key);
	friend InputDevice& operator<<(InputDevice& device, const Key& key);

	~InputDevice();

	MenuInterface* getMenu();
};

