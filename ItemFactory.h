#ifndef CPP_ITEMFACTORY_H
#define CPP_ITEMFACTORY_H

#include "Item.h"
#include <vector>

using ItemPointer = std::shared_ptr<Item>;
using ItemContainer = std::vector<ItemPointer>;

ItemPointer ItemFactory(int days_remaining, int quality, std::string name);
#endif //CPP_ITEMFACTORY_H
