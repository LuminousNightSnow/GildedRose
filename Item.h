#ifndef CPP_ITEM_H
#define CPP_ITEM_H

#include <string>

class Item
{
  public:
    Item(std::string name, int days_remaining, int quality, int max_quality)
        : max_quality_(max_quality), name_(std::move(name)), days_remaining_(days_remaining), quality_(quality)
    {
    }

    virtual ~Item() = default;

    virtual void Update() = 0;
    std::string GetName() { return name_; };

    int GetDaysRemaining_() const { return days_remaining_; }

    int GetQuality() const { return quality_; }

    void DecreaseDaysRemaining();
    void IncreaseQuality(int value);
    void DecreaseQuality(int value);
    void SetQualityToMin();

  protected:
    const int max_quality_;
    const int min_quality_{0};

  private:
    const std::string name_;
    int days_remaining_;
    int quality_;
};

class NormalItem : public Item
{
  public:
    NormalItem(const std::string& name, int days_remaining, int quality, int max_quality = INT16_MAX)
        : Item(name, days_remaining, quality, max_quality){};
    void Update() override;
};

class AgedBrieItem : public Item
{
  public:
    AgedBrieItem(const std::string& name, int days_remaining, int quality, int max_quality = INT16_MAX)
        : Item(name, days_remaining, quality, max_quality){};

    void Update() override;
};

class SulfurasItem : public Item
{
  public:
    SulfurasItem(std::string name, int days_remaining, int quality, int max_quality = INT16_MAX)
        : Item(name, days_remaining, quality, max_quality){};

    void Update() override;
};

class BackstageItem : public Item
{
  public:
    BackstageItem(std::string name, int days_remaining, int quality, int max_quality = INT16_MAX)
        : Item(name, days_remaining, quality, max_quality)
    {
    }

    void Update() override;

  private:
    const int close_to_sell_date{10};
    const int very_close_to_sell_date{5};
};

#endif  // CPP_ITEM_H
