#pragma once
#include "AbstractElement.h"
template<class T>
class IndicatorElement : public AbstractElement
{
private:
	T value;
public :
	
	std::string getContent() override;

	// attrs
	bool isEditable() override;
	bool isOpenable() override;
};
