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

    fstream db;
    db.open("localDebug.txt", ios::out);


    while (!exit)
    {
        ReadConsoleInput(hIn, &inp, 1, &num_of_events);

        if (inp.Event.KeyEvent.bKeyDown) {

            switch (inp.EventType)
            {
            case KEY_EVENT:

                db << inp.Event.KeyEvent.wRepeatCount;

                if (inp.Event.KeyEvent.wRepeatCount >= 3) {            // if it's pressed long enough

                    db << "repeat count";

                    switch (inp.Event.KeyEvent.wVirtualKeyCode)
                    {
                    case VK_LEFT:
                        inputDevice << Key::LongLeft;
                        continue;
                        //break;
                    case VK_RIGHT:
                        inputDevice << Key::LongRight;
                        continue;
                        //break;
                    }

                }

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
                case VK_BACK:
                    exit = true;
                    break;
                default:
                    break;
                }
                break;

            default:
                break;
            }
        }

    }

    db.close();

    return 0;
}