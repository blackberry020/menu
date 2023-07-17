#pragma once
#include <string>
#include <iostream>
#include <vector>

class AbstractElement
{

public :

	std::string elementName;
	const std::string getInstructions();

	virtual std::string getContent() = 0;

	// attrs
	virtual bool isEditable() = 0;
	virtual bool isOpenable() = 0;


	//functions

	virtual void incCurValueDigit() {
		// no reaction by default
	};

	virtual void decCurValueDigit() {
		// no reaction by default
	};

	virtual void incDigit() {
		// no reaction by default
	};

	virtual void decDigit() {
		// no reaction by default
	};

	virtual void saveValueChanges() {
		// no reaction by default
	};


	AbstractElement* getCurSubElement() {
		return subElements[curIndexOfSubElement];
	}

	void goPrevElement() {
		if (curIndexOfSubElement) curIndexOfSubElement--;
	}

	void goNextElement() {
		if (curIndexOfSubElement != amountOfSubElements - 1) curIndexOfSubElement--;
	}

	// for sub elements !!!
	bool requestEditMode() {
		return getCurSubElement()->isEditable();
	}

	// for sub elements !!!
	bool requestOpenSubElement() {
		return getCurSubElement()->isOpenable();
	}

	void incAmountOfChildrenPages() {
		amountOfSubElements++;
	};


	virtual ~AbstractElement() = 0;

private:
	std::vector <AbstractElement*> subElements;
	int amountOfSubElements;
	int curIndexOfSubElement;
};

