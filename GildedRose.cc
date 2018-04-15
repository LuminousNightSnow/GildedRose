#include "GildedRose.h"

GildedRose::GildedRose(ItemContainer& items) : items(items)
{
}

void GildedRose::updateQuality()
{
    for (auto& item : items)
    {
        item->Update();
    }
    return;
}

