#include "InputDevice.h"

InputDevice* operator<<(InputDevice* device, const Key& key)
{	
	device->getMenu()->keyPressed(key);
	return device;
}

InputDevice& operator<<(InputDevice& device, const Key& key)
{	
	device.getMenu()->keyPressed(key);
	return device;
}

InputDevice::InputDevice(MenuInterface* menu) : menuInterface(menu)
{

}

MenuInterface* InputDevice::getMenu()
{
	return menuInterface;
}
