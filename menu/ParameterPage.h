#pragma once
#include "IndicatorPage.h"
template<class T>
class ParameterPage :
    public IndicatorPage<T>
{
public:
    virtual void incrementValue() = 0;
    virtual void decrementValue() = 0;
};


