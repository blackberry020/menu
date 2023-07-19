#pragma once
#include "IndicatorElement.h"
#include <fstream>

using namespace std;

template<class T>
class ParameterElement :
    public IndicatorElement<T>
{
private:
    int curDigit;
    T valueBackup;
public:

    ParameterElement(std::string name, T newValue) : IndicatorElement<T>(name, newValue) {
        
    };

    bool isEditable() override {
        return true;
    }
    bool isOpenable() override {
        return false;
    }

    void prepareForEditing() override {
        valueBackup = IndicatorElement<T>::value;
        curDigit = 1;
    };

    void cancelValueChanges() override {
        IndicatorElement<T>::value = valueBackup;
    }

    void incCurValueDigit() override {
        IndicatorElement<T>::value += curDigit;
    };

    void decCurValueDigit() override {
        IndicatorElement<T>::value -= curDigit;
    };

    void incDigit() override {
        curDigit *= 10;
    };
    
    void decDigit() override {
        if (curDigit > 1) curDigit /= 10;
    };
};


