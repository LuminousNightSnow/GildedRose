#include "Item.h"

void NormalItem::Update()
{
    DecreaseDaysRemaining();
    if (GetQuality() == 0)
    {
        return;
    }

    DecreaseQuality(1);
    if (GetDaysRemaining_() <= 0)
    {
        DecreaseQuality(1);
    }
}

void AgedBrieItem::Update()
{
    DecreaseDaysRemaining();
    if (GetQuality() >= 50)
    {
        return;
    }

    IncreaseQuality(1);
    if (GetDaysRemaining_() <= 0)
    {
        IncreaseQuality(1);
    }
}

void SulfurasItem::Update()
{
}

void BackstageItem::Update()
{
    DecreaseDaysRemaining();
    if (GetDaysRemaining_() < 0)
    {
        SetQualityToMin();
        return;
    }
    if (GetQuality() >= 50)
    {
        return;
    }

    IncreaseQuality(1);

    if (GetDaysRemaining_() < 10)
    {
        IncreaseQuality(1);
    }
    if (GetDaysRemaining_() < 5)
    {
        IncreaseQuality(1);
    }
}

void Item::IncreaseQuality(int value) {

    quality_  = std::min(quality_+= value, max_quality_);
}

void Item::DecreaseQuality(int value) {
    quality_ = std::max(quality_ -= value, min_quality_);
}

void Item::DecreaseDaysRemaining() {
    days_remaining_ -= 1;
}

void Item::SetQualityToMin() {
    quality_ = min_quality_;
}
