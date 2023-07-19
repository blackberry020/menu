#pragma once
#include "AbstractElement.h"
#include "SettingsStorage.h"

#include <fstream>
using namespace std;

template<class T>
class IndicatorElement : public AbstractElement
{
protected:
	T value;
public :

	IndicatorElement(std::string name, T defaultValue) : AbstractElement(name) {
		value = defaultValue;

		fstream deb;
		deb.open("localDebug.txt");
		deb << "value " << value;
		deb.close();
	}

	// ??? add constructor with children (multi-indicator)

	std::string getContent() override {
		return getElementName() + "\t" + std::to_string(value);
	}

	std::string getPreview() override {
		return getContent();
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
