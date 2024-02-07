#include "MessageNode.hpp"
#include "MessageOutcome.hpp"


MessageOutcome::MessageOutcome(int index, const std::string& result, MessageNode* nextNode)
    : index(index), result(result), nextNode(nextNode) {}

std::string MessageOutcome::getResult() const{
    return result;
}

MessageNode* MessageOutcome::getNextNode() const{
    return nextNode;
}

MessageNode* MessageOutcome::PerformOutcome(int choice, MessageNode* currentMessageNode) {
    std::cout << getResult() << "\n";
    currentMessageNode = nextNode;
    return currentMessageNode;
}