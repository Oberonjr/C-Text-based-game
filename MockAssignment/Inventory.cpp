#include "Inventory.hpp"
#include <iostream>

// Implementation of Inventory class
////std::unique_ptr<Inventory> Inventory::instance;
Inventory* Inventory::singleton_ = nullptr;;

Inventory* Inventory::getInstance(const std::string& value) {
    // Create the instance if it doesn't exist
    if (singleton_ == nullptr) {
        singleton_ = new Inventory(value);//std::make_unique<Inventory>();
    }
    return singleton_;
}

void Inventory::addItem(Item* item) { items.push_back(item); }

void Inventory::deleteItem(Item* item) {
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
        delete item;
    }
}

bool Inventory::hasItem(const Item& itemName) const {

    return std::any_of(items.begin(), items.end(), [&itemName](const Item* item) {
        return *item == itemName;
        });
}

 void Inventory::displayInventory() const{
    std::cout << "Inventory:\n";
    for (const auto& item : items) {
        std::cout << "- " << item->getName() << "\n";
    }
}

Inventory::~Inventory() {
    // Cleanup: Delete all items in the inventory
    for (auto& item : items) {
        delete item;
    }
}

void Inventory::clearInventory() {
    for (auto& item : items) {
        delete item;
    }
    items.clear();
}