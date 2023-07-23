#pragma once
#include "ParameterElement.h"
#include "math.h"

class IntParameterElement :
    public ParameterElement<int>
{
private:
    // !!! use maxDigit !!! ???????

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

    IntParameterElement(std::string name, int defaultValue) :
        ParameterElement<int>(name, defaultValue) {

    };

    IntParameterElement(std::string name, int defaultValue, int _maxValueLength) :
        ParameterElement<int>(name, defaultValue),
        maxValueLength(_maxValueLength) {

    };

    void prepareForEditing() override {
        ParameterElement<int>::prepareForEditing();
        curDigit = 1;
    };

    void incCurValueDigit() override {
        // check value length limitations
        if (getLength(ParameterElement<int>::value + curDigit) <= maxValueLength)
            ParameterElement<int>::value += curDigit;
    };

    void decCurValueDigit() override {
        ParameterElement<int>::value -= curDigit;
        if (getValueLength() < getDigitLength()) curDigit /= 10;
    };

    void incDigit() override {
        if (getDigitLength() < getValueLength()) curDigit *= 10;
        else curDigit = 1;
    };

    void decDigit() override {
        if (curDigit > 1) curDigit /= 10;
        else curDigit = pow(10, getValueLength() - 1); // unsafe, write your own function
    };

    void addNewDigitLeft() override {
        if (getDigitLength() < maxValueLength) {
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

