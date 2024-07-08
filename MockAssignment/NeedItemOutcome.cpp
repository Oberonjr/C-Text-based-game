#include "NeedItemOutcome.hpp"

// Implementation of NeedItemOutcome class
NeedItemOutcome::NeedItemOutcome(int index, const std::string& result, const Item& requiredItem, Inventory* inventory, const MessageNode* nextNode)
    : MessageOutcome(index, result, nextNode), requiredItem(requiredItem), inventory(inventory) {}

const Item& NeedItemOutcome::getReqItem() const{
    return requiredItem;
}

const MessageNode* NeedItemOutcome::PerformOutcome(int choice, const MessageNode* currentMessageNode) {
    if (inventory->hasItem(getReqItem())) {
        std::cout << getResult() << "\n";
        currentMessageNode = getNextNode();
    }
    else {
        std::cout << "You need the item '" << requiredItem.getName() << "' to proceed.\n";
        // Optionally delete the needed item from the inventory
        // inventory->deleteItem(item);
        currentMessageNode = currentMessageNode;  // Go back to the same node
    }
    return currentMessageNode;
}