#pragma once
#include "MenuInterface.h"

class Win32OutputDevice : public OutputDevice {
	void onUpdate(std::string data) override;
};
class Win32Menu : public MenuInterface
{	
	Win32Menu() : MenuInterface(new Win32OutputDevice()) {
	
	}
};

