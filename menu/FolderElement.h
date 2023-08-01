#pragma once
#include "AbstractElement.h"
#include "CArray.h"
class FolderElement :
    public AbstractElement
{   
public:

    explicit FolderElement(std::string name, CArray <AbstractElement*> _subElements);
    explicit FolderElement(std::string name, SettingsStorageInterface* storageInterface, CArray <AbstractElement*> _subElements);
    std::string getContent(bool isEditMode) override;
    std::string getPreview(bool isEditMode) override;

    // attrs
    bool isEditable() override;
    bool isOpenable() override;
};
