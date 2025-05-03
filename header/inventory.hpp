#pragma once

#include <string>
#include <unordered_map>
#include <vector>

/**
 * @class Inventory
 * @brief A simple inventory management system for storing items with quantity and price.
 *
 * The Inventory class allows adding, deleting, and querying items based on price or stock level.
 * Each item is uniquely identified by name and stores price and quantity.
 *
 * Example usage:
 * @code
 * Inventory inv(100);
 * inv.add_item("Medkit", 25.5, 10);
 * inv.delete_item("Medkit");
 * @endcode
 */

class Inventory {
private:
    /**
         * @struct Item
         * @brief Represents a single inventory item with name, price, and quantity.
    */
    
    struct Item {
        std::string name;
        double price;
        int quantity;
    };

    int max_capacity; ///< Maximum number of items allowed in the inventory (by quantity).
    int item_count;///< Current number of items in the inventory (total quantity).
    std::unordered_map<std::string, Item> items; ///< Map from item name to Item data.

public:
    /**
         * @brief Constructs an inventory with a maximum capacity.
         * @param capacity The maximum total quantity the inventory can hold.
         */
    explicit Inventory(int capacity);

    /**
         * @brief Adds a new item to the inventory.
         * @param name Name of the item.
         * @param price Price of the item.
         * @param quantity Quantity to add.
         * @return True if the item was added successfully, false otherwise (e.g., already exists or exceeds capacity).
    */
    bool add_item(const std::string& name, double price, int quantity);
    
    /**
         * @brief Deletes an item from the inventory by name.
         * @param name Name of the item to delete.
         * @return True if the item existed and was removed, false otherwise.
    */
    
    bool delete_item(const std::string& name);
    /**
         * @brief Retrieves names of all items within a specific price range.
         * @param min_price Minimum price (inclusive).
         * @param max_price Maximum price (inclusive).
         * @return Vector of item names in the given price range.
    */
    std::vector<std::string> get_items_in_price_range(double min_price, double max_price) const;
    /**
         * @brief Gets the name of the item with the highest quantity in stock.
         * @return Name of the most stocked item, or an empty string if inventory is empty.
    */
    std::string get_most_stocked_item() const;
};
