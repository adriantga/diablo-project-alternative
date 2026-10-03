#pragma once
#include <string>
#include <vector>
#include "Item.h"

class Chest
{
private:
    std::string myName;
    std::vector<Item> myItems;
    bool myIsOpen = false;

public:
    Chest() = default;
    Chest(const std::string& aName) : myName(aName), myIsOpen(false) {}
    Chest(const std::string& aName, const std::vector<Item>& aItems)
        : myName(aName), myItems(aItems), myIsOpen(false) {}

    const std::string& GetName() const { return myName; }
    bool IsOpen() const { return myIsOpen; }
    void SetOpen(bool aIsOpen) { myIsOpen = aIsOpen; }

    void AddItem(const Item& aItem)
    {
        myItems.push_back(aItem);
    }

    const std::vector<Item>& GetItems() const { return myItems; }
    std::vector<Item>& GetItems() { return myItems; }

    std::vector<Item> OpenAndTakeItems()
    {
        myIsOpen = true;
        std::vector<Item> dropped = myItems;
        myItems.clear();
        return dropped;
    }
};
