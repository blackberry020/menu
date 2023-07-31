#pragma once
#include "AbstractElement.h"
#include "SettingsStorage.h"
#include "StrConverter.h"
#include "ElementSpeaker.h"
#include <fstream>
#include <functional>
using namespace std;

template<class T>
class IndicatorElement : public AbstractElement
{
private:
	T value;
	std::function<T(T, SettingsStorageInterface*)> recalculateFunction = [](T oldValue, SettingsStorageInterface*) { return oldValue; };
	ElementSpeaker* elementSpeaker;

protected:
	ElementSpeaker* getElementSpeaker() {
		return elementSpeaker;
	}
public :

	IndicatorElement(std::string name, T defaultValue) : AbstractElement(name) {
		value = defaultValue;
	}

	IndicatorElement(
		std::string name,
		T defaultValue,
		ElementSpeaker* speaker,
		std::function<T(T, SettingsStorageInterface*)> _recalculateFunction
	)
		: AbstractElement(name),
		recalculateFunction(_recalculateFunction),
		elementSpeaker(speaker)
	{
		value = defaultValue;
		elementSpeaker->notifier->addElement(this);
	}

	// ??? add constructor with children (multi-indicator)

	T getValue() {
		return value;
	}

	void setValue(T newValue) {
		value = newValue;
	}

	void updateElement() override {
		// recalculating a value
		value = recalculateFunction(value, getStorage());

		// updating value in a storage
		getStorage()->setValue(getElementName(), value);
	}

	std::string getContent(bool isEditMode) override {
		// udpating value from storage(sensors)
		T curValue = getStorage()->getValue(getElementName(), value);
		if (curValue != value) {
			elementSpeaker->valueChanged();
		}
		value = curValue;
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
		updateElement();
	}

	
};
