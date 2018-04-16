#include <gtest/gtest.h>

#include "GildedRose.h"

class ItemTest : public testing::Test
{
  protected:
    ItemPointer UpdateQualityForItem(int sell_in_decrease = 1);
    virtual void MakeAndUpdateItem(int sell_in_decrease = 1) = 0;

    ItemPointer item_;
    int days_remaining_;
    int initial_quality_{10};
    std::string item_name_;
};

class OrdinaryItemTest : public ItemTest
{
  public:
    OrdinaryItemTest() { item_name_ = "normal item"; }

  protected:
    void MakeAndUpdateItem(int sell_in_decrease = 1) override
    {
        item_ = ItemFactory<OrdinaryItem>(item_name_, days_remaining_, initial_quality_);
        UpdateQualityForItem(sell_in_decrease);
    }
};

ItemPointer ItemTest::UpdateQualityForItem(int sell_in_decrease)
{
    ItemContainer items{item_};

    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(items[0]->GetDaysRemaining_(), days_remaining_ - sell_in_decrease);
    return items[0];
}

ItemContainer UpdateQualityForItemWith(int days_remaining,
                                       int quality,
                                       std::string name = "normal item",
                                       int sell_in_decrease = 1)
{
    ItemPointer item;
    if (name == "Aged Brie")
    {
        item.reset(new AgedBrieItem{name, days_remaining, quality, 50});
    }
    else if (name == "Sulfuras, Hand of Ragnaros")
    {
        item.reset(new SulfurasItem{name, days_remaining, quality});
    }
    else if (name == "Backstage passes to a TAFKAL80ETC concert")
    {
        item.reset(new BackstageItem(name, days_remaining, quality, 50));
    }
    else
    {
        item.reset(new OrdinaryItem{name, days_remaining, quality});
    }

    ItemContainer items{item};

    GildedRose app(items);
    app.updateQuality();
    EXPECT_EQ(items[0]->GetDaysRemaining_(), days_remaining - sell_in_decrease);
    return items;
}

TEST_F(OrdinaryItemTest, normal_item_before_sell_date)
{
    days_remaining_ = 5;
    MakeAndUpdateItem();
    EXPECT_EQ(9, item_->GetQuality());
}

TEST_F(OrdinaryItemTest, normal_item_on_sell_date)
{
    days_remaining_ = 0;
    MakeAndUpdateItem();
    EXPECT_EQ(8, item_->GetQuality());
}

TEST_F(OrdinaryItemTest, normal_item_after_sell_date)
{
    days_remaining_ = -10;
    MakeAndUpdateItem();
    EXPECT_EQ(8, item_->GetQuality());
}

TEST_F(OrdinaryItemTest, normal_item_at_sell_date_quality_one)
{
    days_remaining_ = 0;
    initial_quality_ = 1;
    MakeAndUpdateItem();
    EXPECT_EQ(0, item_->GetQuality());
}

TEST_F(OrdinaryItemTest, normal_item_of_zero_quality)
{
    days_remaining_ = 5;
    initial_quality_ = 0;
    MakeAndUpdateItem();
    EXPECT_EQ(0, item_->GetQuality());
}

TEST(GildedRoseTest, brie_before_sell_date)
{

    auto items = UpdateQualityForItemWith(5, 10, "Aged Brie");
    EXPECT_EQ(11, items[0]->GetQuality());
}

TEST(GildedRoseTest, brie_before_sell_date_with_max_quality)
{

    auto items = UpdateQualityForItemWith(5, 50, "Aged Brie");
    EXPECT_EQ(50, items[0]->GetQuality());
}

TEST(GildedRoseTest, brie_on_sell_date)
{

    auto items = UpdateQualityForItemWith(0, 10, "Aged Brie");
    EXPECT_EQ(12, items[0]->GetQuality());
}

TEST(GildedRoseTest, brie_on_sell_date_near_max_quality)
{

    auto items = UpdateQualityForItemWith(5, 49, "Aged Brie");
    EXPECT_EQ(50, items[0]->GetQuality());
}

TEST(GildedRoseTest, brie_on_sell_date_with_max_quality)
{

    auto items = UpdateQualityForItemWith(5, 50, "Aged Brie");
    EXPECT_EQ(50, items[0]->GetQuality());
}

TEST(GildedRoseTest, brie_after_sell_date)
{

    auto items = UpdateQualityForItemWith(-10, 10, "Aged Brie");
    EXPECT_EQ(12, items[0]->GetQuality());
}

TEST(GildedRoseTest, brie_after_sell_date_with_max_quality)
{

    auto items = UpdateQualityForItemWith(-10, 50, "Aged Brie");
    EXPECT_EQ(50, items[0]->GetQuality());
}

TEST(GildedRoseTest, sulfuras_before_sell_date)
{

    auto items = UpdateQualityForItemWith(5, 80, "Sulfuras, Hand of Ragnaros", 0);
    EXPECT_EQ(80, items[0]->GetQuality());
}

TEST(GildedRoseTest, sulfuras_on_sell_date)
{

    auto items = UpdateQualityForItemWith(0, 80, "Sulfuras, Hand of Ragnaros", 0);
    EXPECT_EQ(80, items[0]->GetQuality());
}

TEST(GildedRoseTest, sulfuras_after_sell_date)
{

    auto items = UpdateQualityForItemWith(-10, 80, "Sulfuras, Hand of Ragnaros", 0);
    EXPECT_EQ(80, items[0]->GetQuality());
}

TEST(GildedRoseTest, backstage_pass_long_before_sell_date)
{

    auto items = UpdateQualityForItemWith(11, 10, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(11, items[0]->GetQuality());
}

TEST(GildedRoseTest, backstage_pass_medium_close_to_sell_date_upper_bound)
{

    auto items = UpdateQualityForItemWith(10, 10, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(12, items[0]->GetQuality());
}

TEST(GildedRoseTest, backstage_pass_medium_close_to_sell_date_upper_bound_at_max_quality)
{

    auto items = UpdateQualityForItemWith(10, 50, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(50, items[0]->GetQuality());
}

TEST(GildedRoseTest, backstage_pass_medium_close_to_sell_date_lower_bound)
{

    auto items = UpdateQualityForItemWith(6, 10, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(12, items[0]->GetQuality());
}

TEST(GildedRoseTest, backstage_pass_medium_close_to_sell_date_lower_bound_at_max_quality)
{

    auto items = UpdateQualityForItemWith(6, 50, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(50, items[0]->GetQuality());
}

TEST(GildedRoseTest, backstage_pass_very_close_to_sell_date_upper_bound)
{

    auto items = UpdateQualityForItemWith(5, 10, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(13, items[0]->GetQuality());
}

TEST(GildedRoseTest, backstage_pass_very_close_to_sell_date_upper_bound_at_max_quality)
{

    auto items = UpdateQualityForItemWith(5, 50, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(50, items[0]->GetQuality());
}

TEST(GildedRoseTest, backstage_pass_very_close_to_sell_date_lower_bound)
{

    auto items = UpdateQualityForItemWith(1, 10, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(13, items[0]->GetQuality());
}

TEST(GildedRoseTest, backstage_pass_very_close_to_sell_date_max_quality)
{

    auto items = UpdateQualityForItemWith(1, 49, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(50, items[0]->GetQuality());
}

TEST(GildedRoseTest, backstage_pass_close_to_sell_date_max_quality)
{

    auto items = UpdateQualityForItemWith(9, 49, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(50, items[0]->GetQuality());
}

TEST(GildedRoseTest, backstage_pass_very_close_to_sell_date_lower_bound_at_max_quality)
{

    auto items = UpdateQualityForItemWith(1, 50, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(50, items[0]->GetQuality());
}

TEST(GildedRoseTest, backstage_pass_on_sell_date)
{

    auto items = UpdateQualityForItemWith(0, 10, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(0, items[0]->GetQuality());
}

TEST(GildedRoseTest, backstage_pass_after_sell_date)
{

    auto items = UpdateQualityForItemWith(-10, 10, "Backstage passes to a TAFKAL80ETC concert");
    EXPECT_EQ(0, items[0]->GetQuality());
}
