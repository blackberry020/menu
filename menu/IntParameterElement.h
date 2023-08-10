#pragma once
#include "ParameterElement.h"
#include "math.h"
#include <functional>
class IntParameterElement :
    public ParameterElement<int>
{
private:
    
    int maxValueLength = 6;  // TODO move to output device

    int curDigit = 1;

    int getDigitLength() {
        return getLength(curDigit);
    }

    int getTempValueLength() {
        return getLength(ParameterElement<int>::getTempValue());
    }

    int getLength(int num) {
        if (num < 0) num *= -1;
        return std::to_string(num).length();
    }

public:

    // If no sub elements
    IntParameterElement(
        std::string name,
        int defaultValue,
        int minVal,
        int maxVal
        ) :
        ParameterElement<int>(name, defaultValue, minVal, maxVal) {};

    // If no sub elements, but defined maxValueLengh
    IntParameterElement(std::string name, int defaultValue, int _maxValueLength) :
        ParameterElement<int>(name, defaultValue, INT_MIN, INT_MAX),
        maxValueLength(_maxValueLength) {};

    // If no sub elements and connected prettyNotifier
    IntParameterElement(
        std::string name,
        int defaultValue,
        int minVal,
        int maxVal,
        PrettyNotifier* prettyNotifier
    ) :
        ParameterElement<int>(
            name,
            defaultValue,
            minVal,
            maxVal,
            prettyNotifier
        ) {};

    // If no sub elements
    // which will be recalculated
    IntParameterElement(
        std::string name,
        int defaultValue,
        int minVal,
        int maxVal,
        std::function<int(int, SettingsStorageInterface*)> recalculateFunction,
        bool recalcAtStart = false
    ) : ParameterElement(
        name,
        defaultValue,
        minVal,
        maxVal,
        recalculateFunction,
        recalcAtStart
    ) {}


    // If there are sub elements
    IntParameterElement(
        std::string name,
        CArray<AbstractElement*> subEl
    )
        : ParameterElement(
            name,
            subEl
        ) {}
    
    // If there are sub elements and notifier
    IntParameterElement(
        std::string name,
        PrettyNotifier* prettyNotifier,
        CArray<AbstractElement*> subEl
    ) : ParameterElement(
        name,
        prettyNotifier,
        subEl
    ) {}

    void incCurValueDigit() override {
        
        if (isValidForChange(ParameterElement<int>::getTempValue() + curDigit)) {
            ParameterElement<int>::setTempValue(ParameterElement<int>::getTempValue() + curDigit);
        }

        if (getTempValueLength() < getDigitLength()) fullUpdateCurDigit();
    };

    void decCurValueDigit() override {

        if (isValidForChange(ParameterElement<int>::getTempValue() - curDigit)) {
            ParameterElement<int>::setTempValue(ParameterElement<int>::getTempValue() - curDigit);
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

    bool isValidForChange(int expectedValue) override {
        return (getDigitLength() < maxValueLength && expectedValue <= maxEditValue && expectedValue >= minEditValue);
    }

    void addNewDigitLeft() override {

        int expectedValue = ParameterElement<int>::getTempValue();

        if (expectedValue < 0) expectedValue -= curDigit * 10;
        else expectedValue += curDigit * 10;

        if (isValidForChange(expectedValue) && isLastDigit()) {
            curDigit *= 10;
            ParameterElement<int>::setTempValue(expectedValue);
        }
    }

    std::string getEditViewValue() override {

        std::string res = std::to_string(ParameterElement<int>::getTempValue());
        int curDigitIndex = getTempValueLength() - std::to_string(curDigit).length();

        if (ParameterElement<int>::getTempValue() < 0) curDigitIndex++;
        
        res.insert(curDigitIndex, "[");
        res.insert(curDigitIndex + 2, "]");

        return res;
    }
};

