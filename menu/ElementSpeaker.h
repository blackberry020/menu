#pragma once
#include "Notifier.h"
class ElementSpeaker {
public:

	explicit ElementSpeaker(Notifier* _notifier) : notifier(_notifier) {
	
	}
	Notifier* notifier;

	void valueChanged() {
		notifier->notifyListeners();
	}
};