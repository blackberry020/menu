#pragma once
#include <string>
#include <iostream>
#include "SettingsStorage.h"
#include "CArray.h"
class AbstractElement
{

private:
	std::string elementName = "no_name";
	CArray<AbstractElement*> subElements;
	SettingsStorageInterface* storage = nullptr;
	int amountOfSubElements = 0;
	int curIndexOfSubElement = 0;

public :

	// constuctors/destructor

	// 1. just element, no children
	explicit AbstractElement(std::string name);

	// 2. element with children
	explicit AbstractElement(std::string name, CArray <AbstractElement*> _subElements);

	// 3. for root folder (children + each child injection)
	explicit AbstractElement(std::string name, SettingsStorageInterface* storageInterface, CArray <AbstractElement*> _subElements);
	

	virtual ~AbstractElement();

	// attrs
	virtual bool isEditable() = 0;
	virtual bool isOpenable() = 0;


	// getters
	std::string getElementName();
	CArray <AbstractElement*> getSubElements();
	SettingsStorageInterface* getStorage();
	int getAmountOfSubElements();
	int getCurIndexOfSubElement();

	//functions

	virtual void updateElement();

	virtual std::string getContent(bool isEditMode) = 0;
	virtual std::string getPreview(bool isEditMode) = 0;

	virtual void prepareForEditing();
	virtual void cancelValueChanges();
	virtual void saveChanges();

	virtual void incCurValueDigit();
	virtual void decCurValueDigit();
	virtual void incDigit();
	virtual void decDigit();

	virtual void addNewDigitLeft();

	AbstractElement* getCurSubElement();

	void goPrevElement();
	void goNextElement();

	//injection function for this element and all children
	//??????? mem optimization ?????????
	virtual void injectStorage(SettingsStorageInterface* storageInterface);

	// for sub elements !!!
	bool requestEditModeSubElement();
	bool requestOpenSubElement();

	void incAmountOfChildrenPages();

};

