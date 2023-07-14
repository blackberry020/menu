#pragma once
#include "AbstractPage.h"
template<class T>
class IndicatorPage : public AbstractPage
{
public :
	T value;
};

