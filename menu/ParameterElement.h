#pragma once
#include "IndicatorElement.h"
template<class T>
class ParameterElement :
    public IndicatorElement<T>
{
private:
    int curDigit;
    T value;
    T valueBackup;
public:

    bool isEditable() override {
        return true;
    }
    bool isOpenable() override {
        return false;
    }

    void prepareForEditing() override {
        valueBackup = value;
        curDigit = 1;
    };

    void cancelValueChanges() override {
        value = valueBackup;
    }

    void incCurValueDigit() override {
        value += curDigit;
    };

    void decCurValueDigit() override {
        value -= curDigit;
    };

    void incDigit() override {
        curDigit *= 10;
    };
    
    void decDigit() override {
        if (curDigit != 1) curDigit /= 10;
    };
};


