#pragma once
#include "AbstractElement.h"
#include "SettingsStorage.h"
template<class T>
class IndicatorElement : public AbstractElement
{
private:
	T value;

	// How to load value without passing an SettingsStorageInterface argument each time?
	// ????
	// ? Tree Injection ?
	SettingsStorageInterface* storage;
public :

	std::string getContent() override;

	// attrs
	bool isEditable() override;
	bool isOpenable() override;

	
};
