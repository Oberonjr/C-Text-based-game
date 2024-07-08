#pragma once
#include "MessageOutcome.hpp"
#include "Item.hpp"
#include "Inventory.hpp"

class NeedItemOutcome : public MessageOutcome {
private:
    const Item& requiredItem;
    Inventory* inventory;
public:
    NeedItemOutcome(int index, const std::string& result, const Item& requiredItem, Inventory* inventory, const MessageNode* nextNode);
    const Item& getReqItem() const;
    virtual const MessageNode* PerformOutcome(int choice, const MessageNode* currentMessageNode) override;
};