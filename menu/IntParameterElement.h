#pragma once
#include "ParameterElement.h"
#include "math.h"

class IntParameterElement :
    public ParameterElement<int>
{
private:
    
    int maxValueLength = 6;

    int curDigit = 1;

    int getDigitLength() {
        return getLength(curDigit);
    }

    int getValueLength() {
        return getLength(ParameterElement<int>::value);
    }

    int getLength(int num) {
        return std::to_string(num).length();
    }


public:

    IntParameterElement(std::string name, int defaultValue, int minVal, int maxVal) :
        ParameterElement<int>(name, defaultValue, minVal, maxVal) {

    };

    IntParameterElement(std::string name, int defaultValue, int _maxValueLength) :
        ParameterElement<int>(name, defaultValue, INT_MIN, INT_MAX),
        maxValueLength(_maxValueLength) {

    };

    void prepareForEditing() override {
        ParameterElement<int>::prepareForEditing();
        curDigit = 1;
    };

    void incCurValueDigit() override {
        
        if (isValidForChange(ParameterElement<int>::value + curDigit)) {
            ParameterElement<int>::value = ParameterElement<int>::value + curDigit;
        }

        if (getValueLength() > getDigitLength()) curDigit *= 10;
    };

    void decCurValueDigit() override {

        if (isValidForChange(ParameterElement<int>::value - curDigit)) {
            ParameterElement<int>::value = ParameterElement<int>::value - curDigit;
        }

        if (getValueLength() < getDigitLength()) curDigit /= 10;
    };

    void incDigit() override {
        if (getDigitLength() < getValueLength()) curDigit *= 10;
        else curDigit = 1;
    };

    void decDigit() override {
        if (curDigit > 1) curDigit /= 10;
        else curDigit = pow(10, getValueLength() - 1); // TODO unsafe, write your own function
    };

    bool isLastDigit() {
        return getDigitLength() == getValueLength();
    }

    bool isValidForChange(int expectedValue) override {
        return (getDigitLength() < maxValueLength && expectedValue <= maxEditValue && expectedValue >= minEditValue);
    }

    void addNewDigitLeft() override {
        if (isValidForChange(IndicatorElement<int>::value + curDigit * 10) && isLastDigit()) {
            curDigit *= 10;
            incCurValueDigit();
        }
    }

    std::string getEditViewValue() override {
        
        std::string res = std::to_string(ParameterElement<int>::value);
        int curDigitIndex = getValueLength() - std::to_string(curDigit).length();
        
        // select a digit in number
        res.insert(curDigitIndex, "[");
        res.insert(curDigitIndex + 2, "]");

        return res;
    }
};

