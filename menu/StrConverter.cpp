#include "StrConverter.h"

std::string StrConverter::toString(int value) {
	return std::to_string(value);
}
std::string StrConverter::toString(std::string value) {
	return value;
}