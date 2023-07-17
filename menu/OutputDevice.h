#pragma once
#include <string>
class OutputDevice
{	
public:
	virtual void onUpdate(std::string data) = 0;
	virtual ~OutputDevice() = 0;
};

