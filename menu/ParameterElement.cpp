#include "ParameterElement.h"

template <class T> bool ParameterElement<T>::isOpenable() {
	return true;
}


template <class T> bool ParameterElement<T>::isEditable() {
	return false;
}
