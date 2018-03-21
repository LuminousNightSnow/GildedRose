#include "GildedRose.h"

GildedRose::GildedRose(ItemContainer& items) : items(items)
{
}

void GildedRose::updateQuality()
{
    for (auto& item : items)
    {
        item->update();
        return;
    }
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
