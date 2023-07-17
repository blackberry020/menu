#include "IndicatorElement.h"

template<class T>
IndicatorElement<T>::IndicatorElement(std::string name) : AbstractElement(name)
{	
	//// load value from storage
	//value = storage->getValue<T>(getElementName());
}

template<class T>
std::string IndicatorElement<T>::getContent() {
	return getElementName() + "\t" + std::to_string(value);
}

template<class T>
bool IndicatorElement<T>::isEditable()
{
	return false;
}

template<class T>
bool IndicatorElement<T>::isOpenable()
{
	return false;
}