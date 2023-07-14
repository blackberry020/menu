#pragma once
#include "AbstractPage.h"
class FolderPage :
    public AbstractPage
{
    string getContent() override;
};

