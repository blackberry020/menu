#pragma once
#include <string>
#include <iostream>
#include <vector>

class AbstractElement
{

public :

	virtual std::string getContent() = 0;

	// attrs
	virtual bool isEditable() = 0;
	virtual bool isOpenable() = 0;


	//functions

	std::string getElementName();

	virtual void incCurValueDigit();
	virtual void decCurValueDigit();
	virtual void incDigit();
	virtual void decDigit();

	virtual void saveValueChanges();

	AbstractElement* getCurSubElement();

	void goPrevElement();
	void goNextElement();

	// for sub elements !!!
	bool requestEditMode();
	bool requestOpenSubElement();

	void incAmountOfChildrenPages();

	virtual ~AbstractElement() = 0;

private:
	std::string elementName;
	std::vector <AbstractElement*> subElements;
	int amountOfSubElements;
	int curIndexOfSubElement;
};

