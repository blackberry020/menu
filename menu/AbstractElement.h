#pragma once
#include <string>
#include <iostream>
#include <vector>

class AbstractElement
{

private:
	std::string elementName;
	std::vector <AbstractElement*> subElements;
	int amountOfSubElements;
	int curIndexOfSubElement;

public :

	// constuctor/destructor
	explicit AbstractElement(std::string name);
	virtual ~AbstractElement() = 0;

	// attrs
	virtual bool isEditable() = 0;
	virtual bool isOpenable() = 0;


	// getter
	std::string getElementName();

	//functions

	virtual std::string getContent() = 0;

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

};

