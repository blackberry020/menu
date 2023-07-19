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
                    new ParameterElement<int>("P1", 123)
                })
            })
    );
    InputDevice* inputDevice = new InputDevice(menu);

    inputDevice << Key::Down;
    inputDevice << Key::Left;
    inputDevice << Key::Enter;
    inputDevice << Key::Left;
    inputDevice << Key::Up;
    
    /// ... add checkers 

    return 0;
}