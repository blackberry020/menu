#pragma once
#include <string>
#include <iostream>

using namespace std;

class AbstractPage
{

public :
	string pageName;
	const string getInstructions();
	virtual string getContent() = 0;
	void showPage();

	virtual ~AbstractPage() = 0;
};

