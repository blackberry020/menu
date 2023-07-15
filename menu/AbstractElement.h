#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class AbstractElement
{

public :

	string elementName;
	const string getInstructions();
	virtual string getContent() = 0;

	virtual ~AbstractElement() = 0;

	void incAmountOfChildrenPages() {
		amountOfSubElements++;
	};

	virtual bool isEditable() = 0;
	virtual bool isOpenable() = 0;

	virtual void incCurValueDigit() {};
	virtual void decCurValueDigit() {};
	virtual void incDigit() {};
	virtual void decDigit() {};
	virtual void saveValueChanges() {};

	AbstractElement* getCurSubElement() {
		return subElements[curIndexOfSubElement];
	}

	void goPrevElement() {
		if (curIndexOfSubElement) curIndexOfSubElement--;
	}

	void goNextElement() {
		if (curIndexOfSubElement != amountOfSubElements - 1) curIndexOfSubElement--;
	}

	bool requestEditMode() {
		return subElements[curIndexOfSubElement]->isEditable();
	}

private:
	vector <AbstractElement*> subElements;
	int amountOfSubElements;
	int curIndexOfSubElement;
};

