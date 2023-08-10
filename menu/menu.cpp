#include <iostream>
#include "Win32Menu.h"
#include "FolderElement.h"
#include "IntParameterElement.h"
#include "InputDevice.h"
#include "TestStorage.h"
#include "IndicatorElement.h"
#include "Key.h"
#include <Windows.h>
#include "CArray.h"
#include <fstream>
#include <ctime>
#include <functional>
#include "CArray.h"
#include "PrettyNotifier.h"
using namespace std;

int main() {

    // EXAMPLE of Initializing CArray
    // CArray<int*> a = { new int* [3] {new int, new int, new int}, 3};

    PrettyNotifier* prettyNotifier = new PrettyNotifier();
    Win32Menu* menu = new Win32Menu(
        new FolderElement("root", { 4, new AbstractElement* [4] {
                new FolderElement("root1", { 1, new AbstractElement* [1] {
                        new FolderElement("root2", { 1, new AbstractElement* [1] {
                                new FolderElement("root3", { 1, new AbstractElement* [1] { new IntParameterElement("DOP", 450, 0, 1000) }})
                            }})
                    }}),
                new IndicatorElement<int>(
                    "PI_TIMER", 0, prettyNotifier),
                new IndicatorElement<int>(
                    "PI_TIMER_X2", 0, prettyNotifier, [](int value, SettingsStorageInterface* settings) {
                        return settings->getValue("PI_TIMER", 0) * 2;
                    }),
                new IntParameterElement(
                    "WEIGHT_LOAD",
                    { 3, new AbstractElement * [3] {
                        new IntParameterElement("WEIGHT_MAX", 1455, 0, 2000),
                        new IntParameterElement("WEIGHT_CUR", 300, 0, 2000, [](int value, SettingsStorageInterface* storage) {
                            return (int)((storage->getValue("WEIGHT_PERCENTAGE", 1) * (double)storage->getValue("WEIGHT_MAX", 1)));
                        }),
                        new IntParameterElement("WEIGHT_LOAD_PERCENTAGE", 0, 0, 100, [](int value, SettingsStorageInterface* storage){
                                return (storage->getValue("WEIGHT_CUR", 1) / (double)storage->getValue("WEIGHT_MAX", 1)) * 100;
                        }, true),
                    }}
                )
            }}),
        new TestStorage(std::time(0))
    );

    InputDevice* inputDevice = new InputDevice(menu);

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD inp;
    DWORD num_of_events;
    bool exit = false;

    int cntLeftPressed = 0;

    while (!exit)
    {   
        GetNumberOfConsoleInputEvents(hIn, &num_of_events);
        if (num_of_events > 0) {
            ReadConsoleInput(hIn, &inp, 1, &num_of_events);

            if (inp.Event.KeyEvent.bKeyDown) {

                if (inp.EventType == KEY_EVENT)
                {
                    switch (inp.Event.KeyEvent.wVirtualKeyCode)
                    {
                    case VK_LEFT:
                        cntLeftPressed++;
                        break;
                    case VK_RIGHT:
                        inputDevice << Key::Right;
                        break;
                    case VK_UP:
                        inputDevice << Key::Up;
                        break;
                    case VK_DOWN:
                        inputDevice << Key::Down;
                        break;
                    case VK_RETURN:
                        inputDevice << Key::Enter;
                        break;
                    case VK_ESCAPE:
                        inputDevice << Key::Escape;
                        break;
                    case VK_BACK:
                        exit = true;
                        break;
                    default:
                        break;
                    }
                }
            }
            else if (inp.EventType == KEY_EVENT && inp.Event.KeyEvent.wVirtualKeyCode == VK_LEFT)
                 {
                    if (cntLeftPressed == 1) inputDevice << Key::Left;
                    else inputDevice << Key::LongLeft;

                    cntLeftPressed = 0;
                 }
        }
        menu->refreshData();
        menu->update();
        Sleep(100);
    }

    delete inputDevice;
    delete menu;

    return 0;
}