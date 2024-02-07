#pragma once
#include "RandomMessageOutcome.hpp"
#include "Item.hpp"
#include "Inventory.hpp"

class RandomItemOutcome : public RandomMessageOutcome {
private:
    Item* newItem;

public:
    RandomItemOutcome(int index, const std::string& result, const std::string& randomResult, double probability, MessageNode* nextNode, MessageNode* randomNextNode, Item* newItem);
    virtual MessageNode* PerformOutcome(int choice, MessageNode* currentMessageNode) override;
};