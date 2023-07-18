#pragma once
#include "AbstractElement.h"
class FolderElement :
    public AbstractElement
{   
public:

    explicit FolderElement(std::string name, std::vector <AbstractElement*> _subElements);
    explicit FolderElement(std::string name, SettingsStorageInterface* storageInterface, std::vector <AbstractElement*> _subElements);
    std::string getContent() override;

    // attrs
    bool isEditable() override;
    bool isOpenable() override;

    void saveValueChanges() override;
};
