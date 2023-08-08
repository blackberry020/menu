#pragma once

class ObservableObject {
public:
	virtual void dataChanged(std::string changedId) = 0;
	virtual void saveChanges() = 0;
};