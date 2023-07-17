#pragma once
#include "IndicatorElement.h"
template<class T>
class ParameterElement :
    public IndicatorElement<T>
{
private:
    int curDigit;
public:

    bool isEditable() override;
    bool isOpenable() override;
};


