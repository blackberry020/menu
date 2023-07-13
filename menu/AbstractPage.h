#pragma once
#include <string>

using namespace std;

class AbstractPage
{
	string pageName;
	string getInstructions();
	virtual string getContent() = 0;
	void showPage();

	virtual ~AbstractPage() = 0;
};

