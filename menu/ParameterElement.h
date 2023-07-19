#pragma once
#include "IndicatorElement.h"
#include <fstream>

using namespace std;

template<class T>
class ParameterElement :
    public IndicatorElement<T>
{
protected:
    // !!! Digits are actual only for ints! (Maybe move this field to IntParameterElement???)

    T valueBackup;
public:

    ParameterElement(std::string name, T defaultValue) : IndicatorElement<T>(name, defaultValue) {
        
    };
    
    virtual std::string getEditViewValue() = 0;

    std::string getContent(bool isEditMode) override {
        if (isEditMode)
            return IndicatorElement<T>::getElementName() + "\t" + getEditViewValue();
        // so we can differ P - parameter and I - indicator
        return "[P] " + IndicatorElement<T>::getElementName() + "\t" + StrConverter::toString(IndicatorElement<T>::value);
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
        valueBackup = IndicatorElement<T>::value;
    };

    void cancelValueChanges() override {
        IndicatorElement<T>::value = valueBackup;
    }

    void saveChanges() override {
        IndicatorElement<T>::getStorage()->setValue(
            IndicatorElement<T>::getElementName(),
            IndicatorElement<T>::value
        );
    }
};


