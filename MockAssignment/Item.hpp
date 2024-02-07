#pragma once
#include <string>

class Item {
private:
    std::string name;
public:
    Item(const std::string& name) : name(name) {}
    std::string getName()const;
    bool operator==(const Item& other) const;
    ~Item() { }
};