#pragma once

#include <string>
#include <algorithm>
#include <memory>
#include <vector>
#include "Item.hpp"


class Inventory {
protected:
    Inventory(const std::string value) : value_(value) {}
    static Inventory* singleton_;
    std::string value_;
private:
    std::vector<Item*> items;

    //static std::unique_ptr<Inventory> instance;
    //Inventory(){}
public:
    ~Inventory();
    static Inventory* getInstance(const std::string&);
    void addItem(Item* item);
    void deleteItem(Item* item);
    bool hasItem(const Item& itemName) const;
    void displayInventory() const;
    void clearInventory();
    Inventory(Inventory& other) = delete;
    void operator=(const Inventory&) = delete;
    std::string value()const {
        return value_;
    }
};