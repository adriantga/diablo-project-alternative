#pragma once
#include <string>
#include <vector>

#include "Item.h"

class Chest
{
    std::string myName;
    std::vector<Item> myItems;
    bool myIsOpen = false;
    
public:
    Chest() = default;
   
    Chest(const std::string aName) : myName(aName)
    {
        
    }
    
    Chest(const std::string aName, const std::vector<Item>& aItems) : myName(aName), myItems(aItems)
    {
        
    }
    
    const std::string& GetName() const { return myName; }
    const std::vector<Item>& GetItems() const { return myItems; }
    bool IsOpen() const { return myIsOpen; }
    void SetOpen(const bool aIsOpen) { myIsOpen = aIsOpen; }
    
    void AddItem(const Item& aItem)
    {
        myItems.push_back(aItem);
    }
    
    std::vector<Item> OpenAndTakeItems()
    {
        myIsOpen = true;
        std::vector<Item> dropped = myItems;
        myItems.clear();
        return dropped;
    }
};