#pragma once

#include "MessageOutcome.hpp"

class RandomMessageOutcome : public MessageOutcome {
private:
    std::string randomResult;
    double probability;
    MessageNode* randomNextNode;

public:
    RandomMessageOutcome(int index, const std::string& result, const std::string& randomResult, double probability, MessageNode* nextNode, MessageNode* randomNextNode = nullptr);
    std::string getRandomResult() const;
    double getProbability() const;
    MessageNode* getNextRandomNode() const;
    virtual MessageNode* PerformOutcome(int choice, MessageNode* currentMessageNode) override;
};