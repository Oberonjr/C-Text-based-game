#pragma once

#include <string>

class MessageOutcome;  // Forward declaration

class MessageNode {
private:
    int index;
    std::string description;
    std::string optionA;
    std::string optionB;
    MessageOutcome* nextMessageA;
    MessageOutcome* nextMessageB;

public:
    MessageNode(int index, const std::string& description, const std::string& optionA, const std::string& optionB);
    void displayMessage() const;
    void setNextNodes(MessageOutcome* node1, MessageOutcome* node2);
    std::string getResultA() const;
    std::string getResultB() const;
    const MessageNode* getNextNode1() const;
    const MessageNode* getNextNode2() const;
    virtual const MessageNode* performOutcome(int choice, MessageNode* currentMessageNode) const;
};
