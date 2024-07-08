#include "MessageNode.hpp"
#include "MessageOutcome.hpp"


MessageOutcome::MessageOutcome(int index, const std::string& result, const MessageNode* nextNode)
    : index(index), result(result), nextNode(nextNode) {}

std::string MessageOutcome::getResult() const{
    return result;
}

const MessageNode* MessageOutcome::getNextNode() const{
    return nextNode;
}

const MessageNode* MessageOutcome::PerformOutcome(int choice, const MessageNode* currentMessageNode) {
    std::cout << getResult() << "\n";
    currentMessageNode = nextNode;
    return currentMessageNode;
}