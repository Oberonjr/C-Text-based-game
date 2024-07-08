#pragma once

#include <string>
#include <iostream>

class MessageNode;  // Forward declaration

class MessageOutcome {
private:
    int index;
    std::string result;
    const MessageNode* nextNode;

public:
    MessageOutcome(int index, const std::string& result, const MessageNode* nextNode);
    std::string getResult() const;
    const MessageNode* getNextNode() const;
    virtual const MessageNode* PerformOutcome(int choice, const MessageNode* currentMessageNode);
};
