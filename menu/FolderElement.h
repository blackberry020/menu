#pragma once
#include "AbstractElement.h"
class FolderElement :
    public AbstractElement
{   
public:

    std::string getContent() override;

    // attrs
    bool isEditable() override;
    bool isOpenable() override;

    void saveValueChanges() override;
};
