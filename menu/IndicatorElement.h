#pragma once
#include "AbstractElement.h"
template<class T>
class IndicatorElement : public AbstractElement
{
public :
	T value;

	bool isEditable() override {
		return false;
	};
	bool isOpenable() override {
		return false;
	};
};

