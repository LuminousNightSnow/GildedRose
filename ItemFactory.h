#ifndef CPP_ITEMFACTORY_H
#define CPP_ITEMFACTORY_H

#include <vector>
#include "Item.h"

using ItemPointer = std::shared_ptr<Item>;
using ItemContainer = std::vector<ItemPointer>;

template <typename Item_T>
ItemPointer ItemFactory(std::string name, int days_remaining, int quality, int max_quality = INT16_MAX)
{
    return ItemPointer(new Item_T{name, days_remaining, quality, max_quality});
}

#endif  // CPP_ITEMFACTORY_H
