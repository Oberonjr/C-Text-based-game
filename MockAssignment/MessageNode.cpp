#include "MessageNode.hpp"
#include "MessageOutcome.hpp"
#include "Inventory.hpp"

// Implementation of MessageNode class
MessageNode::MessageNode(int index, const std::string& description, const std::string& optionA, const std::string& optionB)
    : index(index), description(description), optionA(optionA), optionB(optionB), nextMessageA(nullptr), nextMessageB(nullptr) {}

void MessageNode::displayMessage() const {
    std::cout << description << "\n";
    std::cout << "1. " << optionA << "\n";
    std::cout << "2. " << optionB << "\n";
}

void MessageNode::setNextNodes(MessageOutcome* node1, MessageOutcome* node2) {
    nextMessageA = node1;
    nextMessageB = node2;
}

std::string MessageNode::getResultA() const {
    return nextMessageA->getResult();
}

std::string MessageNode::getResultB() const {
    return nextMessageB->getResult();
}

MessageNode* MessageNode::getNextNode1() const {
    return nextMessageA->PerformOutcome(1, nullptr);
}

MessageNode* MessageNode::getNextNode2() const {
    return nextMessageB->PerformOutcome(2, nullptr);
}

MessageNode* MessageNode::performOutcome(int choice, MessageNode* currentMessageNode) const {
    if (choice == 1) {
        return getNextNode1();
    }
    else if (choice == 2) {
        return getNextNode2();
    }
    else if (choice == 3) {
        //Inventory
        return currentMessageNode;
    }
    else {
        std::cout << "Please introduce a valid choice.\n";
        return currentMessageNode;
    }
}