#include "Item.h"

void OrdinaryItem::Update()
{
    DecreaseDaysRemaining();
    DecreaseQuality(1);
    if (GetDaysRemaining_() <= 0)
    {
        DecreaseQuality(1);
    }
}

void AgedBrieItem::Update()
{
    DecreaseDaysRemaining();
    IncreaseQuality(1);
    if (GetDaysRemaining_() <= 0)
    {
        IncreaseQuality(1);
    }
}

void SulfurasItem::Update()
{
    // Item does not decay, so intentionally do nothing
}

void BackstageItem::Update()
{
    DecreaseDaysRemaining();
    if (GetDaysRemaining_() < 0)
    {
        SetQualityToMin();
        return;
    }
    if (GetQuality() >= max_quality_)
    {
        return;
    }

    IncreaseQuality(1);

    if (GetDaysRemaining_() < close_to_sell_date)
    {
        IncreaseQuality(1);
    }
    if (GetDaysRemaining_() < very_close_to_sell_date)
    {
        IncreaseQuality(1);
    }
}

void Item::IncreaseQuality(int value)
{

    quality_ = std::min(quality_ += value, max_quality_);
}

void Item::DecreaseQuality(int value)
{
    quality_ = std::max(quality_ -= value, min_quality_);
}

void Item::DecreaseDaysRemaining()
{
    days_remaining_ -= 1;
}

void Item::SetQualityToMin()
{
    quality_ = min_quality_;
}
