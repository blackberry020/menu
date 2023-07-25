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
#include <fstream>

using namespace std;

int main() {

    Win32Menu* menu = new Win32Menu(
        new FolderElement("root", new TestStorage(), {
            new FolderElement("C", {
                    new IndicatorElement<int>("PI40", 0),
                    new IndicatorElement<int>("PI45", 0),
                    new IndicatorElement<int>("PI412", 0),
                    new IntParameterElement("P1", 123)
                })
            })
    );

    InputDevice* inputDevice = new InputDevice(menu);

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD inp;
    DWORD num_of_events;
    bool exit = false;

    int cntLeftPressed = 0;

    while (!exit)
    {
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
        else {
            if (inp.EventType == KEY_EVENT && inp.Event.KeyEvent.wVirtualKeyCode == VK_LEFT)
            {
                if (cntLeftPressed == 1) inputDevice << Key::Left;
                else inputDevice << Key::LongLeft;

                cntLeftPressed = 0;
            }
        }

    }

    return 0;
}