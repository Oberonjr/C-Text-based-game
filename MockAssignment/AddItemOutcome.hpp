#pragma once
#include "MessageOutcome.hpp"
#include "Item.hpp"
#include "Inventory.hpp"

class AddItemOutcome : public MessageOutcome {
private:
    Item* itemToAdd;
    Inventory* inventory;
public:
    AddItemOutcome(int index, const std::string& result, Item* itemToAdd, Inventory* inventory, MessageNode* nextNode);
    virtual const MessageNode* PerformOutcome(int choice, const MessageNode* currentMessageNode) override;
};
