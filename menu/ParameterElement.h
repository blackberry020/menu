#pragma once
#include "IndicatorElement.h"
template<class T>
class ParameterElement :
    public IndicatorElement<T>
{
private:
    int curDigit;
public:

    bool isEditable() override {
        return true;
    }
    bool isOpenable() override {
        return false;
    }
};


