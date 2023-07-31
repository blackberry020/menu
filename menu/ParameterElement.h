#pragma once
#include "IndicatorElement.h"
#include <fstream>

using namespace std;

template<class T>
class ParameterElement :
    public IndicatorElement<T>
{
protected:
    T valueBackup;
    // for numeric parameters, maybe for text it won't be string but enum
    T minEditValue;
    T maxEditValue;
public:

    ParameterElement(std::string name, T defaultValue, T minVal, T maxVal) : IndicatorElement<T>(name, defaultValue) {
        minEditValue = minVal;
        maxEditValue = maxVal;
    };

    ParameterElement(
        std::string name,
        T defaultValue, 
        T minVal, 
        T maxVal,
        ElementSpeaker* speaker,
        std::function<T(T, SettingsStorageInterface*)> _recalculateFunction
    ) : IndicatorElement<T>(
        name,
        defaultValue,
        speaker,
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
        return "[P] " + IndicatorElement<T>::getElementName() + "\t" + StrConverter::toString(IndicatorElement<T>::getValue());
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
        valueBackup = IndicatorElement<T>::getValue();
    };

    void cancelValueChanges() override {
        IndicatorElement<T>::setValue(valueBackup);
    }

    void saveChanges() override {
        IndicatorElement<T>::getStorage()->setValue(
            IndicatorElement<T>::getElementName(),
            IndicatorElement<T>::getValue()
        );
    }
};


