#include "Win32Menu.h"
void Win32OutputDevice::onUpdate(std::string data) {
	system("cls");
	std::cout << data;
}

Win32Menu::Win32Menu(FolderElement* rootFolder) : MenuInterface(new Win32OutputDevice(), rootFolder) {

}
