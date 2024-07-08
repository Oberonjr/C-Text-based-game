#pragma once
#include "RandomMessageOutcome.hpp"
#include "Item.hpp"
#include "Inventory.hpp"

class RandomItemOutcome : public RandomMessageOutcome {
private:
    Item* newItem;

public:
    RandomItemOutcome(int index, const std::string& result, const std::string& randomResult, double probability, const MessageNode* nextNode, const MessageNode* randomNextNode, Item* newItem);
    virtual const MessageNode* PerformOutcome(int choice, const MessageNode* currentMessageNode) override;
};