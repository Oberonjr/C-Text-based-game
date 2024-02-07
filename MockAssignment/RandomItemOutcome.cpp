#include "RandomItemOutcome.hpp"

// Implementation of RandomItemOutcome class
RandomItemOutcome::RandomItemOutcome(int index, const std::string& result, const std::string& randomResult, double probability, MessageNode* nextNode, MessageNode* randomNextNode, Item* newItem)
    : RandomMessageOutcome(index, result, randomResult, probability, nextNode, randomNextNode), newItem(std::move(newItem)) {}

MessageNode* RandomItemOutcome::PerformOutcome(int choice, MessageNode* currentMessageNode) {
    if (rand() / static_cast<double>(RAND_MAX) < getProbability()) {
        std::cout << getRandomResult() << "\n";
        if (getNextRandomNode() != nullptr) {
            currentMessageNode = getNextRandomNode();

            // Add the new item to the inventory
            if (newItem) {
                Inventory::getInstance("INVENTORY")->addItem(newItem);
            }
        }
    }
    else {
        std::cout << getResult() << "\n";
        currentMessageNode = getNextNode();
    }
    return currentMessageNode;
}