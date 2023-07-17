#pragma once
#include <string>
#include <functional>

template <class T>
class TypeManager {
	virtual void saveValue(std::string& id, T value) = 0;
	virtual T getValue(std::string& id) = 0;

	virtual ~TypeManager() = 0;
};
class SettingsStorageInterface : public TypeManager<int>, public TypeManager<bool>
{	
	~SettingsStorageInterface() override = 0;
};

