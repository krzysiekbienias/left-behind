#include "inventory.hpp"
#include <iostream>

Inventory::Inventory(int capacity) : max_capacity(capacity), item_count(0) {}

bool Inventory::add_item(const std::string& name, double price, int quantity) {
    if (items.find(name) != items.end()) {
        std::cout << "Item with name '" << name << "' already exists\n";
        return false;
    }
    if (item_count + quantity > max_capacity) {
        std::cout << "Max capacity reached. Please delete something from the inventory\n";
        return false;
    }
    items[name] = Item{name, price, quantity};
    item_count += quantity;
    std::cout << "Item with name '" << name << "' added to inventory successfully.\n";
    return true;
}

bool Inventory::delete_item(const std::string& name) {
    auto it = items.find(name);
    if (it == items.end()) {
        std::cout << "Item with name '" << name << "' does not exist\n";
        return false;
    }
    item_count -= it->second.quantity;
    items.erase(it);
    std::cout << "Item with name '" << name << "' deleted successfully.\n";
    return true;
}

std::vector<std::string> Inventory::get_items_in_price_range(double min_price, double max_price) const {
    std::vector<std::string> results;
    for (const auto& [key, item] : items) {
        if (item.price >= min_price && item.price <= max_price) {
            std::cout << "Item with name '" << item.name << "' is within price range\n";
            results.push_back(item.name);
        }
    }
    return results;
}

std::string Inventory::get_most_stocked_item() const {
    int max_quantity = 0;
    std::string max_quantity_name;
    for (const auto& [key, item] : items) {
        if (item.quantity > max_quantity) {
            max_quantity = item.quantity;
            max_quantity_name = item.name;
            std::cout << "Most stocked item with name '" << item.name << "' updated\n";
        }
    }
    return max_quantity_name;
}
