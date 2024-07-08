#pragma once

#include "MessageOutcome.hpp"

class RandomMessageOutcome : public MessageOutcome {
private:
    std::string randomResult;
    double probability;
    const MessageNode* randomNextNode;

public:
    RandomMessageOutcome(int index, const std::string& result, const std::string& randomResult, double probability,const MessageNode* nextNode, const MessageNode* randomNextNode = nullptr);
    std::string getRandomResult() const;
    double getProbability() const;
    const MessageNode* getNextRandomNode() const;
    virtual const MessageNode* PerformOutcome(int choice, const MessageNode* currentMessageNode) override;
};