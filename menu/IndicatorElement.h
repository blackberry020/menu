#pragma once
#include "AbstractElement.h"
#include "SettingsStorage.h"
#include "StrConverter.h"
#include "ElementSpeaker.h"
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
	ElementSpeaker* elementSpeaker;
	PrettyNotifier* prettyNotifier;
	bool changed = false;

protected:
	ElementSpeaker* getElementSpeaker() {
		return elementSpeaker;
	}
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



	

	// ??? add constructor with children (multi-indicator)

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


	virtual void saveChanges() override {
		getStorage()->setValue(getElementName(), value);
	}

	void dataChanged(std::string id) override {
		// We need recalculate THIS element, but SAVE TO STORAGE later
		value = recalculateFunction(value, getStorage());
		//recalculateElement();
	}

	// when is multiindicator (we are inside IndicatorElement)
	std::string getContent(bool isEditMode) override {
		// Meow meow meow meow meow meow meow
		// Meow Meow meow meow meow meow meow
		// Meow meow Meow meow meow meow meow
		// Meow meow meow Meow meow meow meow
		// Meow meow meow meow Meow meow meow
		// Meow meow meow meow meow Meow meow
		// Meow meow meow meow meow meow Meow 

		return getSubElements()[getCurIndexOfSubElement()]->getPreview(isEditMode);
	}

	std::string getPreview(bool isEditMode) override {
		return "[I] " +  getElementName() + (isOpenable() ? "" : ("\t" + StrConverter::toString(value)));
	}

	// attrs
	bool isEditable() override {
		return false;
	}
	bool isOpenable() override {
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
