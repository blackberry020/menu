#pragma once
#include <string>
#include <functional>

class SettingsStorageInterface
{

public:

	virtual int getValue(std::string id, int defaultValue) = 0;
	virtual bool getValue(std::string id, bool defaultValue) = 0;
	virtual std::string getValue(std::string id, std::string defaultValue) = 0;

	virtual void setValue(std::string id, int value) = 0;
	virtual void setValue(std::string id, bool value) = 0;
	virtual void setValue(std::string id, std::string value) = 0;


	virtual ~SettingsStorageInterface() = default;
};

