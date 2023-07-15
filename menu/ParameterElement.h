#pragma once
#include "IndicatorElement.h"
template<class T>
class ParameterElement :
    public IndicatorElement<T>
{
public:
    int curDigit = 1;
    bool isEditable() override;
    bool isOpenable() override;
};


