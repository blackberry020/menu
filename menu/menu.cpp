#include <iostream>
#include "Win32Menu.h"
#include "FolderElement.h"
#include "IntParameterElement.h"
#include "InputDevice.h"
#include "TestStorage.h"
#include "IndicatorElement.h"
#include "Key.h"
#include <Windows.h>
#include <vector>

int main() {

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD inp;
    DWORD num_of_events;
    bool exit = false;


    Win32Menu* menu = new Win32Menu(
        new FolderElement("root", new TestStorage(), {
            new FolderElement("C", {
                    new IndicatorElement<int>("PI40", 0),
                    new IndicatorElement<int>("PI45", 0),
                    new IndicatorElement<int>("PI412", 0),

                    // 123 - is a default value (if not found on storage)
                    // if value exists in storage, we use storage value !!!
                    new IntParameterElement("P1", 123)
                })
            })
    );

    InputDevice* inputDevice = new InputDevice(menu);

    while (!exit)
    {
        ReadConsoleInput(hIn, &inp, 1, &num_of_events);

        if (inp.Event.KeyEvent.bKeyDown)
            switch (inp.EventType)
            {
                case KEY_EVENT:
                    switch (inp.Event.KeyEvent.wVirtualKeyCode)
                    {
                        case VK_LEFT:
                            inputDevice << Key::Left;
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

                        // EXIT ON BACKSPACE 
                        case VK_BACK:
                            exit = true;
                            break;
                    }
                    break;
             }
        Sleep(10);
    }


    
    /// ... add checkers */

    return 0;
}