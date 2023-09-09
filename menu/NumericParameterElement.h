#pragma once
#include "ParameterElement.h"
#include "math.h"
#include <functional>
template <class T>
class NumericParameterElement :
    public ParameterElement<T>
{
private:
    
    int maxValueLength = 6;  // TODO move to output device

    int curDigit = 1;

    int getDigitLength() {
        return getLength(curDigit);
    }

    int getTempValueLength() {
        return getLength(ParameterElement<T>::getTempValue());
    }

    int getLength(T num) {
        if (num < 0) num *= -1;
        return std::to_string(num).length();
    }

public:

    // If no sub elements
    NumericParameterElement(
        std::string name,
        T defaultValue,
        T minVal,
        T maxVal
        ) :
        ParameterElement<T>(name, defaultValue, minVal, maxVal) {};

    // If no sub elements, but defined maxValueLengh
    NumericParameterElement(std::string name, T defaultValue, T _maxValueLength) :
        ParameterElement<T>(name, defaultValue, INT_MIN, INT_MAX),
        maxValueLength(_maxValueLength) {};

    // If no sub elements and connected prettyNotifier
    NumericParameterElement(
        std::string name,
        T defaultValue,
        T minVal,
        T maxVal,
        PrettyNotifier* prettyNotifier
    ) :
        ParameterElement<T>(
            name,
            defaultValue,
            minVal,
            maxVal,
            prettyNotifier
        ) {};

    // If no sub elements
    // which will be recalculated
    NumericParameterElement(
        std::string name,
        T defaultValue,
        T minVal,
        T maxVal,
        std::function<T(T, SettingsStorageInterface*)> recalculateFunction,
        bool recalcAtStart = false
    ) : ParameterElement<T>(
        name,
        defaultValue,
        minVal,
        maxVal,
        recalculateFunction,
        recalcAtStart
    ) {}


    // If there are sub elements
    NumericParameterElement(
        std::string name,
        CArray<AbstractElement*> subEl
    )
        : ParameterElement<T>(
            name,
            subEl
        ) {}
    
    // If there are sub elements and notifier
    NumericParameterElement(
        std::string name,
        PrettyNotifier* prettyNotifier,
        CArray<AbstractElement*> subEl
    ) : ParameterElement(
        name,
        prettyNotifier,
        subEl
    ) {}

    void incCurValueDigit() override {
        
        if (isValidForChange(ParameterElement<T>::getTempValue() + curDigit)) {
            ParameterElement<T>::setTempValue(ParameterElement<T>::getTempValue() + curDigit);
        }

        if (getTempValueLength() < getDigitLength()) fullUpdateCurDigit();
    };

    void decCurValueDigit() override {

        if (isValidForChange(ParameterElement<T>::getTempValue() - curDigit)) {
            ParameterElement<T>::setTempValue(ParameterElement<T>::getTempValue() - curDigit);
        }

        if (getTempValueLength() < getDigitLength()) fullUpdateCurDigit();
    };

    void incDigit() override {
        if (getDigitLength() < getTempValueLength()) curDigit *= 10;
        else curDigit = 1;
    };

    void fullUpdateCurDigit() {
        curDigit = pow(10, getTempValueLength() - 1); // TODO unsafe, write your own function
    }

    void decDigit() override {
        if (curDigit > 1) curDigit /= 10;
        else fullUpdateCurDigit();
    };

    bool isLastDigit() {
        return getDigitLength() == getTempValueLength();
    }

    bool isValidForChange(T expectedValue) override {
        return (getDigitLength() < maxValueLength && expectedValue <= ParameterElement<T>::maxEditValue && expectedValue >= ParameterElement<T>::minEditValue);
    }

    void addNewDigitLeft() override {

        T expectedValue = ParameterElement<T>::getTempValue();

        if (expectedValue < 0) expectedValue -= curDigit * 10;
        else expectedValue += curDigit * 10;

        if (isValidForChange(expectedValue) && isLastDigit()) {
            curDigit *= 10;
            ParameterElement<T>::setTempValue(expectedValue);
        }
    }

    std::string getEditViewValue() override {

        std::string res = std::to_string(ParameterElement<T>::getTempValue());
        int curDigitIndex = getTempValueLength() - std::to_string(curDigit).length();

        if (ParameterElement<T>::getTempValue() < 0) curDigitIndex++;
        
        res.insert(curDigitIndex, "[");
        res.insert(curDigitIndex + 2, "]");

        return res;
    }
};

