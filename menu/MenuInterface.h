#pragma once
#include "AbstractPage.h"

class MenuInterface
{
	AbstractPage* curPage = nullptr;
	virtual void updatePage() = 0;
	virtual void onRightArrow() = 0;
	virtual void onLeftArrow() = 0;
	virtual void onDownArrow() = 0;
	virtual void onUpArrow() = 0;
	virtual void onEsc() = 0;
	virtual void onEnter() = 0;
};

