#pragma once
#include "IndicatorElement.h"
class IntParameterElement :
    public IndicatorElement<int>
{
    int currentDigit = 1;
};

