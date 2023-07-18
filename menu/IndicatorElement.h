#pragma once
#include "AbstractElement.h"
#include "SettingsStorage.h"
template<class T>
class IndicatorElement : public AbstractElement
{
private:
	T value;
public :

	IndicatorElement(std::string name, T defaultValue) : AbstractElement(name) {
		value = defaultValue;
	}

	// ??? add constructor with children (multi-indicator)

	std::string getContent() override {
		return getElementName() + "\t" + std::to_string(value);
	}

	// attrs
	bool isEditable() override {
		return false;
	}
	bool isOpenable() override {
		return false;
	}

	void injectStorage(SettingsStorageInterface* s) override {
		AbstractElement::injectStorage(s);
		value = getStorage()->getValue(getElementName(), value);
	}

	
};
