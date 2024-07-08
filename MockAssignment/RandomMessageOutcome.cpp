#include "RandomMessageOutcome.hpp"


// Implementation of RandomMessageOutcome class
RandomMessageOutcome::RandomMessageOutcome(int index, const std::string& result, const std::string& randomResult, double probability, const MessageNode* nextNode, const MessageNode* randomNextNode)
    : MessageOutcome(index, result, nextNode), randomResult(randomResult), probability(probability), randomNextNode(randomNextNode) {}

std::string RandomMessageOutcome::getRandomResult() const{
    return randomResult;
}

double RandomMessageOutcome::getProbability() const{
    return probability;
}

const MessageNode* RandomMessageOutcome::getNextRandomNode() const{
    return randomNextNode;
}

const MessageNode* RandomMessageOutcome::PerformOutcome(int choice, const MessageNode* currentMessageNode) {
    if (rand() / static_cast<double>(RAND_MAX) < probability) {
        std::cout << getRandomResult() << "\n";
        if (randomNextNode != nullptr) {
            currentMessageNode = getNextRandomNode();
        }
        else {
            currentMessageNode = getNextNode();
        }
    }
    else {
        std::cout << getResult() << "\n";
        currentMessageNode = getNextNode();
    }
    return currentMessageNode;
}