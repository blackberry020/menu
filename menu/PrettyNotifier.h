#pragma once
#include <vector>
#include <string>
#include "ObservableObject.h"
class PrettyNotifier {
private:
	std::vector<ObservableObject*> elements;
public:
	void notifyListeners(std::string id) {
		if (elements.size() > 0) {
			for (auto el : elements)
				el->dataChanged(id);
			for (auto el : elements)
				el->saveChanges();
		}
	}

	void addElement(ObservableObject* obj) {
		elements.push_back(obj);
	}
};