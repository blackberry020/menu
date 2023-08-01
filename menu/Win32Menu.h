#pragma once
#include "MenuInterface.h"

class Win32OutputDeviceV2 : public OutputDevice {
	int nScreenWidth;
	int nScreenHeight;

	wchar_t* screen;
	HANDLE hConsole;
	DWORD dwBytesWritten;

	void onUpdate(std::string data) override;
public:
	Win32OutputDeviceV2(int w, int h);
};

class Win32OutputDevice : public OutputDevice {
	void onUpdate(std::string data) override;
};

class Win32Menu : public MenuInterface
{	
public:
	explicit Win32Menu(FolderElement* rootFolder, SettingsStorageInterface* storage);
};

