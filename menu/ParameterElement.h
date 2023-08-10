#pragma once
#include "IndicatorElement.h"
#include <fstream>
#include "CArray.h"
using namespace std;

template<class T>
class ParameterElement :
	public IndicatorElement<T>
{
protected:
	// the value, we are changing and then applying
	T tempValue;
	// for numeric parameters, maybe for text it won't be string but enum
	T minEditValue;
	T maxEditValue;
public:

	//If no sub elements
	ParameterElement(
		std::string name,
		T defaultValue, 
		T minVal, 
		T maxVal
	) : IndicatorElement<T>(
		name,
		defaultValue
	),
		minEditValue(minVal),
		maxEditValue(maxVal),
		tempValue(IndicatorElement<T>::getValue()) {}


	// If no sub elements
	// For sub elements, which will be recalculated
	ParameterElement(
		std::string name,
		T defaultValue,
		T minVal,
		T maxVal,
		std::function<T(T, SettingsStorageInterface*)> recalculateFunction
	) : IndicatorElement<T>(
		name,
		defaultValue,
		recalculateFunction
	),
		minEditValue(minVal),
		maxEditValue(maxVal) {}


	// If no sub elements and connected prettyNotifier
	ParameterElement(
		std::string name,
		T defaultValue,
		T minVal,
		T maxVal,
		PrettyNotifier* prettyNotifier
	)
		: IndicatorElement<T>(
			name,
			defaultValue,
			prettyNotifier
		),
		minEditValue(minVal),
		maxEditValue(maxVal),
		tempValue(IndicatorElement<T>::getValue()) {}

	// If no sub elements and connected prettyNotifier
	ParameterElement(
		std::string name,
		T defaultValue,
		T minVal,
		T maxVal,
		PrettyNotifier* prettyNotifier,
		std::function<T(T, SettingsStorageInterface*)> recalculateFunction
	)
		: IndicatorElement<T>(
			name,
			defaultValue,
			prettyNotifier,
			recalculateFunction
		),
		minEditValue(minVal),
		maxEditValue(maxVal),
		tempValue(IndicatorElement<T>::getValue()) {}


	// If there are sub elements
	ParameterElement(
		std::string name,
		CArray<AbstractElement*> subEl
	)
		: IndicatorElement<T>(
			name,
			subEl
		) {}

	// If there are sub elements and notifier
	ParameterElement(
		std::string name,
		PrettyNotifier* prettyNotifier,
		CArray<AbstractElement*> subEl
	)
		: IndicatorElement<T>(
			name,
			prettyNotifier,
			subEl
		) {}
	
	

	
	virtual std::string getEditViewValue() = 0;
	virtual bool isValidForChange(T) = 0;

	virtual std::string getPrefix() override {
		return "[P]";
	}
	//std::string getContent(bool isEditMode) override {
	//	return IndicatorElement<T>::getContent(isEditMode);//getPrefix() + IndicatorElement<T>::getElementName() + "\t" + StrConverter::toString(isEditMode ? tempValue : IndicatorElement<T>::getValue());
	//}

	std::string getPreview(bool isEditMode) override {
		if (isEditMode)
			return IndicatorElement<T>::getElementName() + "\t" + getEditViewValue();

		if (!IndicatorElement<T>::isOpenable()) {
			return getPrefix() + " " + IndicatorElement<T>::getElementName() + "\t" + StrConverter::toString(isEditMode ? tempValue : IndicatorElement<T>::getValue());
		}

		return IndicatorElement<T>::getPreview(isEditMode);
	}
	
	T getTempValue() {
		return tempValue;
	}

	void setTempValue(T other) {
		tempValue = other;
	}
	

	bool isEditable() override {
		return IndicatorElement<T>::getSubElements().size() == 0;
	}

	void prepareForEditing() override {
		tempValue = IndicatorElement<T>::getValue();
	}

	void applyChanges() override {
		IndicatorElement<T>::setValue(tempValue);
		IndicatorElement<T>::setChangeStatus(true);
		IndicatorElement<T>::saveChanges();
		IndicatorElement<T>::getPrettyNotifier()->notifyListeners(IndicatorElement<T>::getElementName());
	}

	void injectStorage(SettingsStorageInterface* s) override {
		IndicatorElement<T>::injectStorage(s);
		tempValue = IndicatorElement<T>::getValue();
	}
};


