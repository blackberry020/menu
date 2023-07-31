#pragma once
#include "AbstractElement.h"
#include "SettingsStorage.h"
#include "StrConverter.h"
#include <fstream>
#include <functional>
using namespace std;



template<class T>
class IndicatorElement : public AbstractElement
{
private:
	T value;
	std::function<T(T, SettingsStorageInterface*)> recalculateFunction = [](T oldValue, SettingsStorageInterface*) { return oldValue; };
public :

	IndicatorElement(std::string name, T defaultValue) : AbstractElement(name) {
		value = defaultValue;
	}

	IndicatorElement(
		std::string name,
		T defaultValue,
		std::function<T(T, SettingsStorageInterface*)> recalcFunction
	)
		: AbstractElement(name),
		recalculateFunction(recalcFunction)
	{
		value = defaultValue;
	}

	// ??? add constructor with children (multi-indicator)

	T getValue() {
		return value;
	}

	void setValue(T newValue) {
		value = newValue;
	}

	void recalculate() {
		// recalculating a value
		value = recalculateFunction();

		// updating value in a storage
		getStorage()->setValue(value);
	}

	std::string getContent(bool isEditMode) override {
		// udpating value from storage(sensors)
		value = getStorage()->getValue(getElementName(), value);
		return "[I] " + getElementName() + "\t" + StrConverter::toString(value);
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
