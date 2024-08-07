#include "AddItemOutcome.hpp"

// Implementation of AddItemOutcome class
AddItemOutcome::AddItemOutcome(int index, const std::string& result, Item* itemToAdd, Inventory* inventory, MessageNode* nextNode)
    : MessageOutcome(index, result, nextNode), itemToAdd(itemToAdd), inventory(inventory) {}

const MessageNode* AddItemOutcome::PerformOutcome(int choice, const MessageNode* currentMessageNode) {
    inventory->addItem(itemToAdd);
    std::cout << getResult() << "\n" << " You obtained: " << itemToAdd->getName() << "!" << "\n";
    currentMessageNode = getNextNode();
    return currentMessageNode;
}
