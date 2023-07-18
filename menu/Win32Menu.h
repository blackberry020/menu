#pragma once
#include "MenuInterface.h"

class Win32OutputDevice : public OutputDevice {
	void onUpdate(std::string data) override;
};

class Win32Menu : public MenuInterface
{	
public:
	explicit Win32Menu(FolderElement* rootFolder);
};

