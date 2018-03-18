#include <gtest/gtest.h>

#include "GildedRose.h"

vector<Item> UpdateQualityForItemWith(int sell_in, int quality,
                                      string name = "normal item",
                                      int sell_in_decrease = 1) {
  Item item{name, sell_in, quality};
  vector<Item> items{item};
  GildedRose app(items);
  app.updateQuality();
  EXPECT_EQ(items[0].sellIn, sell_in - sell_in_decrease);
  return items;
}

TEST(GildedRoseTest, normal_item_before_sell_date) {

  auto items = UpdateQualityForItemWith(5, 10, "normal");
  EXPECT_EQ(9, items[0].quality);
}

TEST(GildedRoseTest, normal_item_on_sell_date) {

  auto items = UpdateQualityForItemWith(0, 10, "normal");
  EXPECT_EQ(8, items[0].quality);
}

TEST(GildedRoseTest, normal_item_after_sell_date) {

  auto items = UpdateQualityForItemWith(-10, 10, "normal");
  EXPECT_EQ(8, items[0].quality);
}

TEST(GildedRoseTest, normal_item_of_zero_quality) {

  auto items = UpdateQualityForItemWith(5, 0, "normal");
  EXPECT_EQ(0, items[0].quality);
}

TEST(GildedRoseTest, brie_before_sell_date) {

  auto items = UpdateQualityForItemWith(5, 10, "Aged Brie");
  EXPECT_EQ(11, items[0].quality);
}

TEST(GildedRoseTest, brie_before_sell_date_with_max_quality) {

  auto items = UpdateQualityForItemWith(5, 50, "Aged Brie");
  EXPECT_EQ(50, items[0].quality);
}

TEST(GildedRoseTest, brie_on_sell_date) {

  auto items = UpdateQualityForItemWith(0, 10, "Aged Brie");
  EXPECT_EQ(12, items[0].quality);
}

TEST(GildedRoseTest, brie_on_sell_date_near_max_quality) {

  auto items = UpdateQualityForItemWith(5, 49, "Aged Brie");
  EXPECT_EQ(50, items[0].quality);
}

TEST(GildedRoseTest, brie_on_sell_date_with_max_quality) {

  auto items = UpdateQualityForItemWith(5, 50, "Aged Brie");
  EXPECT_EQ(50, items[0].quality);
}

TEST(GildedRoseTest, brie_after_sell_date) {

  auto items = UpdateQualityForItemWith(-10, 10, "Aged Brie");
  EXPECT_EQ(12, items[0].quality);
}

TEST(GildedRoseTest, brie_after_sell_date_with_max_quality) {

  auto items = UpdateQualityForItemWith(-10, 50, "Aged Brie");
  EXPECT_EQ(50, items[0].quality);
}

TEST(GildedRoseTest, sulfuras_before_sell_date) {

  auto items = UpdateQualityForItemWith(5, 80, "Sulfuras, Hand of Ragnaros", 0);
  EXPECT_EQ(80, items[0].quality);
}

TEST(GildedRoseTest, sulfuras_on_sell_date) {

  auto items = UpdateQualityForItemWith(0, 80, "Sulfuras, Hand of Ragnaros", 0);
  EXPECT_EQ(80, items[0].quality);
}

TEST(GildedRoseTest, sulfuras_after_sell_date) {

  auto items =
      UpdateQualityForItemWith(-10, 80, "Sulfuras, Hand of Ragnaros", 0);
  EXPECT_EQ(80, items[0].quality);
}

void example() {
  vector<Item> items;
  items.push_back(Item("+5 Dexterity Vest", 10, 20));
  items.push_back(Item("Aged Brie", 2, 0));
  items.push_back(Item("Elixir of the Mongoose", 5, 7));
  items.push_back(Item("Sulfuras, Hand of Ragnaros", 0, 80));
  items.push_back(Item("Backstage passes to a TAFKAL80ETC concert", 15, 20));
  items.push_back(Item("Conjured Mana Cake", 3, 6));
  GildedRose app(items);
  app.updateQuality();
}

/*
 * # This simplest thing is to clone Jim's repo
(https://github.com/jimweirich/gilded_rose_kata) and then
# put this file in the root directory.

gem 'minitest', '~> 4.7'

require "minitest/autorun"
require "minitest/reporters"
MiniTest::Reporters.use! MiniTest::Reporters::SpecReporter.new

require_relative './gilded_rose'


class GildedRoseTest < MiniTest::Unit::TestCase

  def update_quality_for_item_with(sell_in,
                                   quality,
                                   name             = 'normal item',
                                   sell_in_decrease = 1)

    item = Item.new(name, sell_in, quality)
    update_quality([item])
    assert_equal item.sell_in, sell_in - sell_in_decrease
    item
  end



  def test_normal_item_of_zero_quality
    item = update_quality_for_item_with(5, 0, 'normal')
    assert_equal 0, item.quality
  end

  def test_brie_before_sell_date
    item = update_quality_for_item_with(5, 10, 'Aged Brie')
    assert_equal 11, item.quality
  end

  def test_brie_before_sell_date_with_max_quality
    item = update_quality_for_item_with(5, 50, 'Aged Brie')
    assert_equal 50, item.quality
  end

  def test_brie_on_sell_date
    item = update_quality_for_item_with(0, 10, 'Aged Brie')
    assert_equal 12, item.quality
  end

  def test_brie_on_sell_date_near_max_quality
    item = update_quality_for_item_with(5, 49, 'Aged Brie')
    assert_equal 50, item.quality
  end

  def test_brie_on_sell_date_with_max_quality
    item = update_quality_for_item_with(5, 50, 'Aged Brie')
    assert_equal 50, item.quality
  end

  def test_brie_after_sell_date
    item = update_quality_for_item_with(-10, 10, 'Aged Brie')
    assert_equal 12, item.quality
  end

  def test_brie_after_sell_date_with_max_quality
    item = update_quality_for_item_with(-10, 50, 'Aged Brie')
    assert_equal 50, item.quality
  end

  def test_sulfuras_before_sell_date
    item = update_quality_for_item_with(5, 80, 'Sulfuras, Hand of Ragnaros', 0)
    assert_equal 80, item.quality
  end

  def test_sulfuras_on_sell_date
    item = update_quality_for_item_with(0, 80, 'Sulfuras, Hand of Ragnaros', 0)
    assert_equal 80, item.quality
  end

  def test_sulfuras_after_sell_date
    item = update_quality_for_item_with(-10, 80, 'Sulfuras, Hand of Ragnaros',
0)
    assert_equal 80, item.quality
  end

  def test_backstage_pass_long_before_sell_date
    item = update_quality_for_item_with(11, 10, 'Backstage passes to a
TAFKAL80ETC concert')
    assert_equal 11, item.quality
  end

  def test_backstage_pass_medium_close_to_sell_date_upper_bound
    item = update_quality_for_item_with(10, 10, 'Backstage passes to a
TAFKAL80ETC concert')
    assert_equal 12, item.quality
  end

  def test_backstage_pass_medium_close_to_sell_date_upper_bound_at_max_quality
    item = update_quality_for_item_with(10, 50, 'Backstage passes to a
TAFKAL80ETC concert')
    assert_equal 50, item.quality
  end

  def test_backstage_pass_medium_close_to_sell_date_lower_bound
    item = update_quality_for_item_with(6, 10, 'Backstage passes to a
TAFKAL80ETC concert')
    assert_equal 12, item.quality
  end

  def test_backstage_pass_medium_close_to_sell_date_lower_bound_at_max_quality
    item = update_quality_for_item_with(6, 50, 'Backstage passes to a
TAFKAL80ETC concert')
    assert_equal 50, item.quality
  end

  def test_backstage_pass_very_close_to_sell_date_upper_bound
    item = update_quality_for_item_with(5, 10, 'Backstage passes to a
TAFKAL80ETC concert')
    assert_equal 13, item.quality
  end

  def test_backstage_pass_very_close_to_sell_date_upper_bound_at_max_quality
    item = update_quality_for_item_with(5, 50, 'Backstage passes to a
TAFKAL80ETC concert')
    assert_equal 50, item.quality
  end

  def test_backstage_pass_very_close_to_sell_date_lower_bound
    item = update_quality_for_item_with(1, 10, 'Backstage passes to a
TAFKAL80ETC concert')
    assert_equal 13, item.quality
  end

  def test_backstage_pass_very_close_to_sell_date_lower_bound_at_max_quality
    item = update_quality_for_item_with(1, 50, 'Backstage passes to a
TAFKAL80ETC concert')
    assert_equal 50, item.quality
  end

  def test_backstage_pass_on_sell_date
    item = update_quality_for_item_with(0, 10, 'Backstage passes to a
TAFKAL80ETC concert')
    assert_equal 0, item.quality
  end

  def test_backstage_pass_after_sell_date
    item = update_quality_for_item_with(-10, 10, 'Backstage passes to a
TAFKAL80ETC concert')
    assert_equal 0, item.quality
  end

  def test_conjured_item_before_sell_date
    item = update_quality_for_item_with(5, 10, 'Conjured Mana Cake')
    assert_equal 8, item.quality
  end

  def test_conjured_item_at_zero_quality
    item = update_quality_for_item_with(5, 0, 'Conjured Mana Cake')
    assert_equal 0, item.quality
  end

  def test_conjured_item_on_sell_date
    item = update_quality_for_item_with(0, 10, 'Conjured Mana Cake')
    assert_equal 6, item.quality
  end

  def test_conjured_item_on_sell_date_at_zero_quality
    item = update_quality_for_item_with(0, 0, 'Conjured Mana Cake')
    assert_equal 0, item.quality
  end

  def test_conjured_item_after_sell_date
    item = update_quality_for_item_with(-10, 10, 'Conjured Mana Cake')
    assert_equal 6, item.quality
  end

  def test_conjured_item_after_sell_date_at_zero_quality
    item = update_quality_for_item_with(-10, 0, 'Conjured Mana Cake')
    assert_equal 0, item.quality
  end

  def test_several_items
    items = [Item.new("normal item", 5, 10),
             Item.new("Aged Brie", 3, 10)]

    update_quality(items)
    assert_equal  9, items[0].quality
    assert_equal  4, items[0].sell_in
    assert_equal 11, items[1].quality
    assert_equal  2, items[1].sell_in
  end

end
 */