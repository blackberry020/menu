#pragma once
#include "AbstractElement.h"
class FolderElement :
    public AbstractElement
{
    string getContent() override;

    bool isEditable() override;
    bool isOpenable() override;
};
