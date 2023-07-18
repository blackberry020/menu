#include "TestStorage.h"


int TestStorage::getValue(std::string id, int defaultValue)
{
    if (id == "PI40")
        return 5;
    if (id == "PI45")
        return 12;
    if (id == "PI412")
        return -4;

    return defaultValue;
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

}

void TestStorage::setValue(std::string id, bool value)
{
}

void TestStorage::setValue(std::string id, std::string value)
{
}
