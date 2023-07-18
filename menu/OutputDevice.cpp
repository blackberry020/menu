#include "OutputDevice.h"

OutputDevice* operator<<(OutputDevice* device, const std::string& data)
{
	device->onUpdate(data);

	return device;
}

OutputDevice& operator<<(OutputDevice& device, const std::string& data)
{
	device.onUpdate(data);

	return device;
}

OutputDevice::~OutputDevice()
{
}
