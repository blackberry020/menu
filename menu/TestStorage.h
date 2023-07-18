#pragma once
#include "SettingsStorage.h"

class TestStorage :
    public SettingsStorageInterface
{
    int getValue(std::string id, int defaultValue) override;
	bool getValue(std::string id, bool defaultValue) override;
	std::string getValue(std::string id, std::string defaultValue) override;

	void setValue(std::string id, int value) override;
	void setValue(std::string id, bool value) override;
	void setValue(std::string id, std::string value) override;
};

