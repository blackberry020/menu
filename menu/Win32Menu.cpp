#include "Win32Menu.h"
void Win32OutputDevice::onUpdate(std::string data) {
	system("cls");
	std::cout << data;
}

Win32Menu::Win32Menu(FolderElement* rootFolder, SettingsStorageInterface* storage) : MenuInterface(new Win32OutputDevice(), storage, rootFolder) {

}

void Win32OutputDeviceV2::onUpdate(std::string data)
{
    // ????
    const wchar_t* wcC = (std::wstring(data.begin(), data.end())).c_str();

    int pX = 0;
    int pY = 0;
    wchar_t symbol;
    symbol = wcC[pX];
    while (symbol != '\0') {
        if (symbol == '\n') {
            pY++;
            pX = 0;
        }
        else {
            screen[pX + pY * nScreenWidth] = symbol;
            pX++;
        }

    }


    WriteConsoleOutputCharacter(
        hConsole,
        screen,
        nScreenWidth * nScreenHeight,
        { 0, 0 },
        &dwBytesWritten
    ); // Rec to buff
}

Win32OutputDeviceV2::Win32OutputDeviceV2(int w, int h) : nScreenWidth(w), nScreenHeight(h), dwBytesWritten(0)
{
	screen = new wchar_t[nScreenWidth * nScreenHeight + 1]; // array rec for buff
	screen[nScreenWidth * nScreenHeight] = L'\0';
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // Screen buff

	SetConsoleActiveScreenBuffer(hConsole); // Console setup
}
