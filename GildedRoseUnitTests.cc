#include <gtest/gtest.h>

#include "GildedRose.h"

ItemContainer UpdateQualityForItemWith(int days_remaining,
                                       int quality,
                                       string name = "normal item",
                                       int sell_in_decrease = 1)
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

    ItemContainer items{item};

    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(items[0]->days_remaining, days_remaining - sell_in_decrease);
    return items;
}

TEST(GildedRoseTest, normal_item_before_sell_date)
{

    auto items = UpdateQualityForItemWith(5, 10);
    EXPECT_EQ(9, items[0]->quality);
}

TEST(GildedRoseTest, normal_item_on_sell_date)
{

    auto items = UpdateQualityForItemWith(0, 10);
    EXPECT_EQ(8, items[0]->quality);
}

TEST(GildedRoseTest, normal_item_after_sell_date)
{

    auto items = UpdateQualityForItemWith(-10, 10);
    EXPECT_EQ(8, items[0]->quality);
}

TEST(GildedRoseTest, normal_item_of_zero_quality)
{

    auto items = UpdateQualityForItemWith(5, 0);
    EXPECT_EQ(0, items[0]->quality);
}

TEST(GildedRoseTest, brie_before_sell_date)
{

    auto items = UpdateQualityForItemWith(5, 10, "Aged Brie");
    EXPECT_EQ(11, items[0]->quality);
}

TEST(GildedRoseTest, brie_before_sell_date_with_max_quality)
{

    auto items = UpdateQualityForItemWith(5, 50, "Aged Brie");
    EXPECT_EQ(50, items[0]->quality);
}

TEST(GildedRoseTest, brie_on_sell_date)
{

    auto items = UpdateQualityForItemWith(0, 10, "Aged Brie");
    EXPECT_EQ(12, items[0]->quality);
}

TEST(GildedRoseTest, brie_on_sell_date_near_max_quality)
{

    auto items = UpdateQualityForItemWith(5, 49, "Aged Brie");
    EXPECT_EQ(50, items[0]->quality);
}

TEST(GildedRoseTest, brie_on_sell_date_with_max_quality)
{

    auto items = UpdateQualityForItemWith(5, 50, "Aged Brie");
    EXPECT_EQ(50, items[0]->quality);
}

TEST(GildedRoseTest, brie_after_sell_date)
{

    auto items = UpdateQualityForItemWith(-10, 10, "Aged Brie");
    EXPECT_EQ(12, items[0]->quality);
}

TEST(GildedRoseTest, brie_after_sell_date_with_max_quality)
{

    auto items = UpdateQualityForItemWith(-10, 50, "Aged Brie");
    EXPECT_EQ(50, items[0]->quality);
}

TEST(GildedRoseTest, sulfuras_before_sell_date)
{

    auto items = UpdateQualityForItemWith(5, 80, "Sulfuras, Hand of Ragnaros", 0);
    EXPECT_EQ(80, items[0]->quality);
}

TEST(GildedRoseTest, sulfuras_on_sell_date)
{

    auto items = UpdateQualityForItemWith(0, 80, "Sulfuras, Hand of Ragnaros", 0);
    EXPECT_EQ(80, items[0]->quality);
}

TEST(GildedRoseTest, sulfuras_after_sell_date)
{

    auto items = UpdateQualityForItemWith(-10, 80, "Sulfuras, Hand of Ragnaros", 0);
    EXPECT_EQ(80, items[0]->quality);
}

TEST(GildedRoseTest, backstage_pass_long_before_sell_date)
{

    auto items = UpdateQualityForItemWith(11, 10, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(11, items[0]->quality);
}

TEST(GildedRoseTest, backstage_pass_medium_close_to_sell_date_upper_bound)
{

    auto items = UpdateQualityForItemWith(10, 10, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(12, items[0]->quality);
}

TEST(GildedRoseTest, backstage_pass_medium_close_to_sell_date_upper_bound_at_max_quality)
{

    auto items = UpdateQualityForItemWith(10, 50, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(50, items[0]->quality);
}

TEST(GildedRoseTest, backstage_pass_medium_close_to_sell_date_lower_bound)
{

    auto items = UpdateQualityForItemWith(6, 10, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(12, items[0]->quality);
}

TEST(GildedRoseTest, backstage_pass_medium_close_to_sell_date_lower_bound_at_max_quality)
{

    auto items = UpdateQualityForItemWith(6, 50, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(50, items[0]->quality);
}

TEST(GildedRoseTest, backstage_pass_very_close_to_sell_date_upper_bound)
{

    auto items = UpdateQualityForItemWith(5, 10, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(13, items[0]->quality);
}

TEST(GildedRoseTest, backstage_pass_very_close_to_sell_date_upper_bound_at_max_quality)
{

    auto items = UpdateQualityForItemWith(5, 50, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(50, items[0]->quality);
}

TEST(GildedRoseTest, backstage_pass_very_close_to_sell_date_lower_bound)
{

    auto items = UpdateQualityForItemWith(1, 10, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(13, items[0]->quality);
}

TEST(GildedRoseTest, backstage_pass_very_close_to_sell_date_lower_bound_at_max_quality)
{

    auto items = UpdateQualityForItemWith(1, 50, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(50, items[0]->quality);
}

TEST(GildedRoseTest, backstage_pass_on_sell_date)
{

    auto items = UpdateQualityForItemWith(0, 10, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(0, items[0]->quality);
}

TEST(GildedRoseTest, backstage_pass_after_sell_date)
{

    auto items = UpdateQualityForItemWith(-10, 10, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(0, items[0]->quality);
}
//
// void example()
//{
//    vector<Item> items;
//    items.push_back(Item("+5 Dexterity Vest", 10, 20));
//    items.push_back(Item("Aged Brie", 2, 0));
//    items.push_back(Item("Elixir of the Mongoose", 5, 7));
//    items.push_back(Item("Sulfuras, Hand of Ragnaros", 0, 80));
//    items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 15,
//    20));
//    items.push_back(Item("Conjured Mana Cake", 3, 6));
//    GildedRose app(items);
//    app.updateQuality();
//}
