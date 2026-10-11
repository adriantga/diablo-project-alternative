#pragma once

#include <string>

struct StatModifiers;
class ItemType;

class Item
{
    const ItemType* myType = nullptr;
    std::string myName;
    int myWeight = 0;
    StatModifiers* myModifiers = nullptr;
    
public:
    Item();
    Item(const Item& aOther);
    Item& operator=(const Item& aOther);
    ~Item();
    
    Item(const std::string& aName, int aWeight, const StatModifiers& aModifiers);
    Item(const ItemType& aType);
    Item(const ItemType* aType);
    Item(const ItemType& aType, const StatModifiers& aExtraModifiers);

    std::string GetName() const { return myName; }
    int GetWeight() const { return myWeight; }
    const StatModifiers& GetModifiers() const;
    const ItemType* GetItemType() const { return myType; }
    void DisplayInfo() const;
};
