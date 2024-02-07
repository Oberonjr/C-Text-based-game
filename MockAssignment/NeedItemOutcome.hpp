#pragma once
#include "MessageOutcome.hpp"
#include "Item.hpp"
#include "Inventory.hpp"

class NeedItemOutcome : public MessageOutcome {
private:
    const Item& requiredItem;
    Inventory* inventory;
public:
    NeedItemOutcome(int index, const std::string& result, const Item& requiredItem, Inventory* inventory, MessageNode* nextNode);
    const Item& getReqItem() const;
    virtual MessageNode* PerformOutcome(int choice, MessageNode* currentMessageNode) override;
};