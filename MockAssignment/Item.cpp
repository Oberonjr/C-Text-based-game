#include "Item.hpp"

//Implementation of Item class
std::string Item::getName()const { return name; }

bool Item:: operator==(const Item& other) const {
    return name == other.name;
}