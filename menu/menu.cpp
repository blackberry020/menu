#include <iostream>
#include "Win32Menu.h"
#include "FolderElement.h"
#include "IntParameterElement.h"
#include "InputDevice.h"
#include "TestStorage.h"
#include "IndicatorElement.h"
#include "Key.h"
#include <vector>
int main() {

    Win32Menu* menu = new Win32Menu(
        new FolderElement("root", new TestStorage(), {
            new FolderElement("C", {
                    new IndicatorElement<int>("PI40", 0),
                    new IndicatorElement<int>("PI45", 0),
                    new IndicatorElement<int>("PI412", 0),
                })
            })
    );
    InputDevice* inputDevice = new InputDevice(menu);

    inputDevice << Key::Down;
    inputDevice << Key::Right;
    inputDevice << Key::Right;

    /// ... add checkers 

    return 0;
}