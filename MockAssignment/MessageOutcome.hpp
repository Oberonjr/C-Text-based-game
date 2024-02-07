#pragma once

#include <string>
#include <iostream>

class MessageNode;  // Forward declaration

class MessageOutcome {
private:
    int index;
    std::string result;
    MessageNode* nextNode;

public:
    MessageOutcome(int index, const std::string& result, MessageNode* nextNode);
    std::string getResult() const;
    MessageNode* getNextNode() const;
    virtual MessageNode* PerformOutcome(int choice, MessageNode* currentMessageNode);
};
