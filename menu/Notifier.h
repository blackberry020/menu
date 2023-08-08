#pragma once
#include <vector>
#include "AbstractElement.h"
class Notifier {
private:
	std::vector<AbstractElement*> elements;
public:
	void notifyListeners() {
		for (AbstractElement* el : elements)
			el->updateElement();
	}

	void addElement(AbstractElement* element) {
		elements.push_back(element);
	}
};
