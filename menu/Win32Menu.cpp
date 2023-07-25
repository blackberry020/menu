#include "Win32Menu.h"
void Win32OutputDevice::onUpdate(std::string data) {
	system("cls");
	std::cout << data;
}

Win32Menu::Win32Menu(FolderElement* rootFolder, SettingsStorageInterface* storage) : MenuInterface(new Win32OutputDevice(), storage, rootFolder) {

}
