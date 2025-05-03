
#include "inventory.hpp"
#include <gtest/gtest.h>

#include <iostream>
#include <streambuf>

// Utility to mute std::cout
class CoutSilencer {
public:
    CoutSilencer() {
        old_buf = std::cout.rdbuf();
        std::cout.rdbuf(null_buf.rdbuf());  // redirect to null buffer
    }

    ~CoutSilencer() {
        std::cout.rdbuf(old_buf);  // restore original buffer
    }

private:
    std::streambuf* old_buf;
    std::ostringstream null_buf;
};


TEST(InventoryTest, AddItemSuccess) {
    CoutSilencer mute;
    Inventory inv(10);
    EXPECT_TRUE(inv.add_item("Rifle", 99.99, 2));
}

TEST(InventoryTest, AddItemDuplicate) {
    CoutSilencer mute;
    Inventory inv(10);
    inv.add_item("Medkit", 12.5, 1);
    EXPECT_FALSE(inv.add_item("Medkit", 15.0, 2));
}

TEST(InventoryTest, AddItemExceedsCapacity) {
    CoutSilencer mute;
    Inventory inv(5);
    inv.add_item("Ammo", 5.0, 4);
    EXPECT_FALSE(inv.add_item("Knife", 3.0, 2));
}

TEST(InventoryTest, DeleteItemSuccess) {
    CoutSilencer mute;
    Inventory inv(10);
    inv.add_item("Backpack", 30.0, 1);
    EXPECT_TRUE(inv.delete_item("Backpack"));
}

TEST(InventoryTest, DeleteNonexistentItem) {
    CoutSilencer mute;
    Inventory inv(10);
    EXPECT_FALSE(inv.delete_item("Tent"));
}

TEST(InventoryTest, ItemsInPriceRange) {
    CoutSilencer mute;
    Inventory inv(10);
    inv.add_item("Torch", 15.0, 1);
    inv.add_item("Map", 25.0, 1);
    inv.add_item("Compass", 5.0, 1);

    auto result = inv.get_items_in_price_range(10.0, 20.0);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "Torch");
}

TEST(InventoryTest, GetMostStockedItem) {
    CoutSilencer mute;
    Inventory inv(10);
    inv.add_item("Canteen", 9.0, 1);
    inv.add_item("Boots", 50.0, 3);
    inv.add_item("Jacket", 70.0, 2);

    EXPECT_EQ(inv.get_most_stocked_item(), "Boots");
}

TEST(InventoryTest, CanCreateEmptyInventory) {
    Inventory inv(100);
    EXPECT_TRUE(true);  // Just a sanity check yuuuhu
}
