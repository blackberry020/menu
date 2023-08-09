#pragma once
#include "IndicatorElement.h"
#include <fstream>

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

    //ParameterElement(std::string name, T defaultValue, T minVal, T maxVal) : IndicatorElement<T>(name, defaultValue) {
    //    minEditValue = minVal;
    //    maxEditValue = maxVal;
    //};

    ParameterElement(
        std::string name,
        T defaultValue, 
        T minVal, 
        T maxVal,
        std::function<T(T, SettingsStorageInterface*)> _recalculateFunction = [](T v, SettingsStorageInterface*) { return v; }
    ) : IndicatorElement<T>(
        name,
        defaultValue,
        _recalculateFunction
    ) {
        minEditValue = minVal;
        maxEditValue = maxVal;
    }
    
    virtual std::string getEditViewValue() = 0;
    virtual bool isValidForChange(T) = 0;

    std::string getContent(bool isEditMode) override {
        if (isEditMode)
            return IndicatorElement<T>::getElementName() + "\t" + getEditViewValue();
        // so we can differ P - parameter and I - indicator
        return "[P] " + IndicatorElement<T>::getElementName() + "\t" + StrConverter::toString(isEditMode ? tempValue :IndicatorElement<T>::getValue());
    }

    T getTempValue() {
        return tempValue;
    }

    void setTempValue(T other) {
        tempValue = other;
    }

    std::string getPreview(bool isEditMode) override {
        return getContent(isEditMode);
    }
    

    bool isEditable() override {
        return true;
    }
    bool isOpenable() override {
        // for some, who have child, its openable !!!!!!!!!!!!!!!!!!!!!!!!!!!
        return false;
    }
    
    //

    void prepareForEditing() override {
        tempValue = IndicatorElement<T>::getValue();
    }

    /*void cancelValueChanges() override {
        IndicatorElement<T>::setValue(tempValue);
    }*/

    void saveChanges() override {
        IndicatorElement<T>::setValue(tempValue);
        IndicatorElement<T>::saveChanges();
    }

    void injectStorage(SettingsStorageInterface* s) override {
        IndicatorElement<T>::injectStorage(s);
        tempValue = IndicatorElement<T>::getValue();
    }
};


