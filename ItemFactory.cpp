#include "ItemFactory.h"

ItemPointer ItemFactory(int days_remaining, int quality, std::string name)
{
    ItemPointer item;
    if (name == "Aged Brie")
    {
        item.reset(new AgedBrieItem{name, days_remaining, quality});
    }
    else if (name == "Sulfuras, Hand of Ragnaros")
    {
        item.reset(new SulfurasItem{name, days_remaining, quality});
    }
    else if (name == "Backstage passes to a TAFKAL80ETC concert")
    {
        item.reset(new BackstageItem(name, days_remaining, quality));
    }
    else
    {
        item.reset(new NormalItem{name, days_remaining, quality});
    }

    return item;
}