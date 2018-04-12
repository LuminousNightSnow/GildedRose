#include "GildedRose.h"

#include <iostream>

using namespace std;

ostream& operator<<(ostream& s, Item& item)
{
    s << item.name << ", " << item.days_remaining << ", " << item.quality;
    return s;
}

int main()
{
    ItemContainer items;
    items.push_back(ItemFactory(10, 20, "+5 Dexterity Vest"));
    items.push_back(ItemFactory(2, 0, "Aged Brie"));
    items.push_back(ItemFactory(5, 7, "Elixir of the Mongoose"));
    items.push_back(ItemFactory(0, 80, "Sulfuras, Hand of Ragnaros"));
    items.push_back(ItemFactory(-1, 80, "Sulfuras, Hand of Ragnaros"));
    items.push_back(ItemFactory(15, 20, "Backstage passes to a TAFKAL80ETC concert"));
    items.push_back(ItemFactory(10, 49, "Backstage passes to a TAFKAL80ETC concert"));
    items.push_back(ItemFactory(5, 49, "Backstage passes to a TAFKAL80ETC concert"));
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
