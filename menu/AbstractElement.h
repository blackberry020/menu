#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "SettingsStorage.h"

class AbstractElement
{

private:
	std::string elementName;
	std::vector <AbstractElement*> subElements;
	SettingsStorageInterface* storage;
	int amountOfSubElements;
	int curIndexOfSubElement;

public :

	// constuctor/destructor
	explicit AbstractElement(std::string name);

	// for root folder + child injection
	explicit AbstractElement(std::string name, SettingsStorageInterface* storageInterface);
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

	//injection function for this element and all child
	//??????? mem optimization ?????????
	void injectStorage(SettingsStorageInterface* storageInterface);

	// for sub elements !!!
	bool requestEditMode();
	bool requestOpenSubElement();

	void incAmountOfChildrenPages();

};

