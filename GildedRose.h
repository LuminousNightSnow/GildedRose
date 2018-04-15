#ifndef CPP_GILDED_ROSE
#define CPP_GILDED_ROSE

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "ItemFactory.h"


class GildedRose
{
  public:
    ItemContainer items;

    GildedRose(ItemContainer& items);

    void updateQuality();
};
#endif

