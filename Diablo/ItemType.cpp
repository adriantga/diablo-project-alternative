#include "ItemType.h"

ItemType::ItemType(const std::string& aName, const int aWeight, const StatModifiers& aModifiers, const ItemTypes aType)
    : myName(aName), myWeight(aWeight), myModifiers(aModifiers), myItemType(aType)
{
}
