#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Item
{
  public:
    string name;
    int days_remaining;
    int quality;

    Item(string name, int days_remaining, int quality)
        : name(std::move(name)), days_remaining(days_remaining), quality(quality)
    {
    }

    virtual void update() = 0;

    virtual ~Item() = default;
};

using ItemPointer = std::shared_ptr<Item>;
using ItemContainer = vector<ItemPointer>;

class NormalItem : public Item
{
  public:
    NormalItem(const string& name, int days_remaining, int quality) : Item(name, days_remaining, quality){};
    void update() override;
};

class AgedBrieItem : public Item
{
  public:
    AgedBrieItem(const string& name, int days_remaining, int quality) : Item(name, days_remaining, quality){};

    void update() override;
};

class SulfurasItem : public Item
{
  public:
    SulfurasItem(string name, int days_remaining, int quality) : Item(name, days_remaining, quality){};

    void update() override;
};

class BackstageItem : public Item
{
  public:
    BackstageItem(string name, int days_remaining, int quality) : Item(name, days_remaining, quality) {}

    void update() override;
};

class GildedRose
{
  public:
    ItemContainer items;

    GildedRose(ItemContainer& items);

    void updateQuality();
};
