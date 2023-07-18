#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "SettingsStorage.h"

class AbstractElement
{

protected:
	std::string elementName;
	std::vector <AbstractElement*> subElements;
	SettingsStorageInterface* storage;
	int amountOfSubElements;
	int curIndexOfSubElement;

public :

	// constuctors/destructor

	// 1. just element, no children
	explicit AbstractElement(std::string name);

	// 2. element with children
	explicit AbstractElement(std::string name, std::vector <AbstractElement*> _subElements);

	// 3. for root folder (children + each child injection)
	explicit AbstractElement(std::string name, SettingsStorageInterface* storageInterface, std::vector <AbstractElement*> _subElements);
	

	virtual ~AbstractElement();

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

	//injection function for this element and all children
	//??????? mem optimization ?????????
	virtual void injectStorage(SettingsStorageInterface* storageInterface);

	// for sub elements !!!
	bool requestEditMode();
	bool requestOpenSubElement();

	void incAmountOfChildrenPages();

};

