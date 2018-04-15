#include "GildedRose.h"

#include <iostream>

using namespace std;

ostream& operator<<(ostream& s, Item& item)
{
    s << item.GetName() << ", " << item.GetDaysRemaining_() << ", " << item.GetQuality();
    return s;
}

int main()
{
    const int kBackstageItemMaxQuality = 50;
    ItemContainer items;
    items.push_back(ItemFactory<NormalItem>("+5 Dexterity Vest", 10, 20));
    items.push_back(ItemFactory<AgedBrieItem>("Aged Brie", 2, 0));
    items.push_back(ItemFactory<NormalItem>("Elixir of the Mongoose", 5, 7));
    items.push_back(ItemFactory<SulfurasItem>("Sulfuras, Hand of Ragnaros", 0, 80));
    items.push_back(ItemFactory<SulfurasItem>("Sulfuras, Hand of Ragnaros", -1, 80));
    items.push_back(
        ItemFactory<BackstageItem>("Backstage passes to a TAFKAL80ETC concert", 15, 20, kBackstageItemMaxQuality));
    items.push_back(
        ItemFactory<BackstageItem>("Backstage passes to a TAFKAL80ETC concert", 10, 49, kBackstageItemMaxQuality));
    items.push_back(
        ItemFactory<BackstageItem>("Backstage passes to a TAFKAL80ETC concert", 5, 49, kBackstageItemMaxQuality));
    GildedRose app(items);

    cout << "OMGHAI!" << endl;

    for (int day = 0; day <= 30; day++)
    {
        cout << "-------- day " << day << " --------" << endl;
        cout << "name, days remaining, quality" << endl;
        for (auto item : items)
        {
            cout << *item << endl;
        }
        cout << endl;

        app.updateQuality();
    }
}
