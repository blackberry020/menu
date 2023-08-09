#include "TestStorage.h"

TestStorage::TestStorage(int _startTime) : startTime(_startTime){
    storageMap = {
        {"MAX_WEIGHT", 450},
        {"CUR_WEIGHT", 70},
        {"WEIGHT_LOAD_A", 2324},
        {"WEIGHT_LOAD_B", 3344},
    };
}

int TestStorage::getValue(std::string id, int defaultValue)
{
    if (id == "PI_TIMER")
        return std::time(0) - startTime;
    if (id == "WEIGHT_LOAD_A")
        return (std::time(0) - startTime);
    return storageMap[id];
}

bool TestStorage::getValue(std::string id, bool defaultValue)
{   
    if (id == "PB30")
        return false;
    return defaultValue;
}

std::string TestStorage::getValue(std::string id, std::string defaultValue)
{   
    if (id == "PS20")
        return "";
    return defaultValue;
}

void TestStorage::setValue(std::string id, int value)
{
    storageMap[id] = value;
}

void TestStorage::setValue(std::string id, bool value)
{
}

void TestStorage::setValue(std::string id, std::string value)
{
}
