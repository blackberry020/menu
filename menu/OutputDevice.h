#pragma once
#include <string>
class OutputDevice
{	
public:
	virtual void onUpdate(std::string data) = 0;
	virtual ~OutputDevice();

	friend OutputDevice* operator<<(OutputDevice* device, const std::string& data);
	friend OutputDevice& operator<<(OutputDevice& device, const std::string& data);

private:

};

