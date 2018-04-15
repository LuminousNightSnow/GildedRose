#ifndef CPP_ITEMFACTORY_H
#define CPP_ITEMFACTORY_H

#include "Item.h"
#include <vector>

using ItemPointer = std::shared_ptr<Item>;
using ItemContainer = std::vector<ItemPointer>;

template<typename Item_T>
ItemPointer ItemFactory(int days_remaining, int quality, std::string name)
{
    return ItemPointer(new Item_T{name, days_remaining, quality});
}
#endif //CPP_ITEMFACTORY_H
