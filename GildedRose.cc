#include "GildedRose.h"

GildedRose::GildedRose(ItemContainer& items) : items(items)
{
}

void GildedRose::updateQuality()
{
    for (auto& item : items)
    {
        item->update();
    }
    return;
}

void NormalItem::update()
{
    days_remaining -= 1;
    if (quality == 0)
    {
        return;
    }

    quality -= 1;
    if (days_remaining <= 0)
    {
        quality -= 1;
    }
}

void AgedBrieItem::update()
{
    days_remaining -= 1;
    if (quality >= 50)
    {
        return;
    }

    quality += 1;
    if (days_remaining <= 0)
    {
        quality += 1;
    }
}

void SulfurasItem::update()
{
}

void BackstageItem::update()
{
    days_remaining -= 1;
    if (days_remaining < 0)
    {
        quality = 0;
        return;
    }
    if (quality >= 50)
    {
        return;
    }

    quality += 1;

    if (days_remaining < 10)
    {
        quality += 1;
    }
    if (days_remaining < 5)
    {
        quality += 1;
    }
}

ItemPointer ItemFactory(int days_remaining, int quality, string name)
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