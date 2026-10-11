#include "Item.h"
#include "ItemType.h"
#include "Utilities.h"

Item::Item()
    : myType(nullptr), myName(""), myWeight(0), myModifiers(new StatModifiers())
{
}

Item::Item(const Item& aOther)
    : myType(aOther.myType), myName(aOther.myName), myWeight(aOther.myWeight),
      myModifiers(aOther.myModifiers ? new StatModifiers(*aOther.myModifiers) : new StatModifiers())
{
}

Item& Item::operator=(const Item& aOther)
{
    if (this != &aOther)
    {
        myType = aOther.myType;
        myName = aOther.myName;
        myWeight = aOther.myWeight;
        delete myModifiers;
        myModifiers = aOther.myModifiers ? new StatModifiers(*aOther.myModifiers) : new StatModifiers();
    }
    return *this;
}

Item::~Item()
{
    delete myModifiers;
    myModifiers = nullptr;
}

Item::Item(const std::string& aName, const int aWeight, const StatModifiers& aModifiers)
    : myType(nullptr), myName(aName), myWeight(aWeight), myModifiers(new StatModifiers(aModifiers))
{
}

Item::Item(const ItemType& aType)
    : myType(&aType), myName(aType.GetName()), myWeight(aType.GetWeight()), myModifiers(new StatModifiers(aType.GetModifiers()))
{
}

Item::Item(const ItemType* aType)
    : myType(aType),
      myName(aType ? aType->GetName() : ""),
      myWeight(aType ? aType->GetWeight() : 0),
      myModifiers(new StatModifiers(aType ? aType->GetModifiers() : StatModifiers()))
{
}

Item::Item(const ItemType& aType, const StatModifiers& aExtraModifiers)
    : myType(&aType), myName(aType.GetName()), myWeight(aType.GetWeight()), myModifiers(new StatModifiers(aType.GetModifiers()))
{
    myModifiers->Add(aExtraModifiers);
}

const StatModifiers& Item::GetModifiers() const
{
    return *myModifiers;
}

void Item::DisplayInfo() const
{
    std::cout << myName << " (Weight: " << myWeight << ") [Modifiers: ";
    if (myModifiers)
    {
        myModifiers->PrintModifiers();
    }
    else
    {
        std::cout << "None";
    }
    std::cout << "]\n";
}