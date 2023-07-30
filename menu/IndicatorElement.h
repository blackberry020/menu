#pragma once
#include "AbstractElement.h"
#include "SettingsStorage.h"
#include "StrConverter.h"
#include <fstream>
using namespace std;

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

	T getValue() {
		return value;
	}

	void setValue(T newValue) {
		value = newValue;
	}

	std::string getContent(bool isEditMode) override {
		setValue(getStorage()->getValue(getElementName(), getValue()));
		return "[I] " + getElementName() + "\t" + StrConverter::toString(getValue());
	}

	std::string getPreview(bool isEditMode) override {
		return getContent(isEditMode);
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
