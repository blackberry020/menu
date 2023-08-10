#pragma once
#include "AbstractElement.h"
#include "SettingsStorage.h"
#include "StrConverter.h"
#include <fstream>
#include <functional>
#include "PrettyNotifier.h"
using namespace std;

template<class T>
class IndicatorElement : public AbstractElement
{
private:
	T value;
	std::function<T(T, SettingsStorageInterface*)> recalculateFunction = [](T oldValue, SettingsStorageInterface*) { return oldValue; };
	PrettyNotifier* prettyNotifier;
	bool changed = false;

public :


	// If no sub elements
	IndicatorElement(std::string name, T defaultValue) : AbstractElement(name) {
		value = defaultValue;
	}

	// If no sub elements and connected prettyNotifier
	IndicatorElement(std::string name, T defaultValue, PrettyNotifier* _prettyNotifier)
		: AbstractElement(name), prettyNotifier(_prettyNotifier) {
		value = defaultValue;

		prettyNotifier->addElement(this);
	}

	// If there are sub elements
	IndicatorElement(std::string name, CArray<AbstractElement*> subEl) :
		AbstractElement(name, subEl) {

		prettyNotifier = new PrettyNotifier();
		for (int i = 0; i < getSubElements().size(); i++)
			getSubElements()[i]->injectPrettyNotifier(prettyNotifier);
	}

	// If there are sub elements and notifier
	IndicatorElement(
		std::string name,
		PrettyNotifier* _prettyNotifier,
		CArray<AbstractElement*> subEl
	)
		: AbstractElement(name, subEl),
		prettyNotifier(_prettyNotifier)
	{
		for (int i = 0; i < getSubElements().size(); i++)
			getSubElements()[i]->injectPrettyNotifier(prettyNotifier);
	}

	// For sub elements, which will be recalculated
	IndicatorElement(
		std::string name,
		T defaultValue,
		std::function<T(T, SettingsStorageInterface*)> _recalculateFunction
	)
		: AbstractElement(name),
		recalculateFunction(_recalculateFunction)
	{
		value = defaultValue;
	}

	T getValue() {
		return value;
	}

	void setValue(T newValue) {
		value = newValue;
	}

	// updating data from sensors
	void updateElement() override {

		if (getSubElements().size() == 0) {
			T curValue = getStorage()->getValue(getElementName(), value);
			if (curValue != value) {
				prettyNotifier->notifyListeners(getElementName());
				value = curValue;
				changed = true;
			}
		}
		else {
			AbstractElement::updateElement();
		}
	}
	//

	// recalculating element if it neccessary


	virtual std::string getPrefix() override{
		return "[I]";
	}

	virtual void saveChanges() override {
		getStorage()->setValue(getElementName(), value);
	}

	void dataChanged(std::string id) override {
		// We need recalculate THIS element, but SAVE TO STORAGE later

		// we just changed this element, so we dont need to recalculate it
		if (id != getElementName())
			value = recalculateFunction(value, getStorage());
	}

	// when is multiindicator (we are inside IndicatorElement)
	std::string getContent(bool isEditMode) override {
		return getSubElements()[getCurIndexOfSubElement()]->getPreview(isEditMode);
	}

	std::string getPreview(bool isEditMode) override {
		return getPrefix() + " " + getElementName() + (isOpenable() ? "" : ("\t" + StrConverter::toString(value) + getPostfix()));
	}

	// attrs
	virtual bool isEditable() override {
		return false;
	}
	virtual bool isOpenable() override {
		return getSubElements().size() != 0;
	}

	virtual void injectStorage(SettingsStorageInterface* s) override {
		AbstractElement::injectStorage(s);
		value = getStorage()->getValue(getElementName(), value);
	}

	void injectPrettyNotifier(PrettyNotifier* notifier) {
		prettyNotifier = notifier;
		if (getSubElements().size() == 0) {
			prettyNotifier->addElement(this);
		}
		else
			for (int i = 0; i < getSubElements().size(); i++)
				getSubElements()[i]->injectPrettyNotifier(prettyNotifier);
	}

	
};
