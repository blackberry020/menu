#pragma once
#include <string>
#include <iostream>
#include "SettingsStorage.h"
#include "CArray.h"
#include "ObservableObject.h"
#include "PrettyNotifier.h"
class AbstractElement : public ObservableObject
{

private:
	std::string elementName = "no_name";
	CArray<AbstractElement*> subElements;
	SettingsStorageInterface* storage = nullptr;
	int amountOfSubElements = 0;
	int curIndexOfSubElement = 0;
	bool recalculateAtStart;

public :

	// constuctors/destructor

	// 1. just element, no children
	explicit AbstractElement(std::string name, bool recalcAtStart);

	// 2. element with children
	explicit AbstractElement(std::string name, CArray <AbstractElement*> _subElements);

	// 3. for root folder (children + each child injection)
	explicit AbstractElement(std::string name, SettingsStorageInterface* storageInterface, CArray <AbstractElement*> _subElements);
	

	virtual ~AbstractElement();

	// attrs
	virtual bool isEditable() = 0;
	virtual bool isOpenable() = 0;

	virtual std::string getPrefix();
	virtual std::string getPostfix();

	// getters
	std::string getElementName();
	CArray <AbstractElement*> getSubElements();
	SettingsStorageInterface* getStorage();
	int getAmountOfSubElements();
	int getCurIndexOfSubElement();
	bool getRecalculateAtStartStatus();


	void setRecalculateAtStartStatus(bool s);

	//functions


	// updating data from sensors
	virtual void updateElement();

	virtual void dataChanged(std::string changedId) override;
	virtual void saveChanges() override;

	// for PARAMETERS
	virtual void applyChanges();

	virtual void tryNotify();

	virtual std::string getContent(bool isEditMode) = 0;
	virtual std::string getPreview(bool isEditMode) = 0;

	virtual void prepareForEditing();

	virtual void injectPrettyNotifier(PrettyNotifier* notifier);
	

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

	// apply recalculate function after each object initialization
	virtual void postInitRecalculation();

	// for sub elements !!!
	bool requestEditModeSubElement();
	bool requestOpenSubElement();

	void incAmountOfChildrenPages();

};

