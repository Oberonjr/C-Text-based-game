
#include <cstdio>
#include <ctime>
#include <cstdlib>

#include "Item.hpp"
#include "Inventory.hpp"
#include "MessageNode.hpp"
#include "NeedItemOutcome.hpp"
#include "AddItemOutcome.hpp"
#include "RandomMessageOutcome.hpp"
#include "RandomItemOutcome.hpp"

//----------------------------------------------------------------------------------
//

int main() {
    srand(time(0));
    Inventory* inventory = Inventory::getInstance("INVENTORY");

    // Nodes
    MessageNode startNode(1, "You wake up in a mysterious forest. In front of you, there are two paths.",
        "Take the left path.", "Take the right path.");

    MessageNode leftPathNode(2, "As you walk down the left path, you find a hidden treasure chest.",
        "Open the chest.", "Leave the chest alone.");

    MessageNode rightPathNode(3, "The right path leads you to a dark cave entrance.",
        "Enter the cave.", "Continue on the path.");

    MessageNode treasureOutcome(4, "You open the chest and find a shiny gem inside!",
        "Continue down the path.", "Continue up the path.");

    MessageNode darkCaveOutcome(5, "As you enter the dark cave, you hear strange noises echoing.",
        "Investigate the noises.", "Leave the cave quickly.");

    MessageNode investigateOutcome(6, "You find a magical amulet on the ground.",
        "Continue exploring the cave.", "Leave the cave.");

    MessageNode leaveCaveOutcome(7, "You decide to leave the cave. The noises get fainter as you move away.",
        "Continue down the path.", "Continue up the path.");

    //Item list
    Item* RarePotion = new Item("Rare Potion");

    Item* RustyKey = new Item("Rusty Key");

    // Nodes with Outcomes
    MessageOutcome mainMessageOutcome(30, "I fucking hate ChatGPT and it's shitty code holy fuck they did make it worse", &startNode);


    RandomItemOutcome randomTreasureOutcome(8, "While opening the chest, you trigger a magical event!",
         "Congratulations! You found a rare potion!", 0.5f, &startNode, &treasureOutcome, new Item("Rare Potion"));

    RandomMessageOutcome randomNoisesOutcome(9, "The noises in the cave turn out to be friendly bats.",
         "The bats scatter as you approach.", 0.3f, &startNode, &treasureOutcome);


    AddItemOutcome addItemAmuletOutcome(10, "You pick up the magical amulet.", new Item("Magical Amulet"), inventory, &investigateOutcome);
    AddItemOutcome addItemKeyOutcome(11, "You find a rusty key on the cave floor.", RustyKey, inventory, &leaveCaveOutcome);

    //NeedItemOutcome test(23, "hfhfh", RustyKey, inventory)
    NeedItemOutcome needKeyOutcome(12, "You approach a locked door. The rusty key might work here.", *RustyKey, inventory, &startNode);

    // Tying Nodes Together --- shit's fucked yo
    startNode.setNextNodes(&addItemKeyOutcome, &randomNoisesOutcome);
    leftPathNode.setNextNodes(&randomTreasureOutcome, &mainMessageOutcome);
    rightPathNode.setNextNodes(&randomNoisesOutcome, &mainMessageOutcome);
    treasureOutcome.setNextNodes(&randomTreasureOutcome, &addItemAmuletOutcome);
    darkCaveOutcome.setNextNodes(&mainMessageOutcome, &mainMessageOutcome);
    investigateOutcome.setNextNodes(&mainMessageOutcome, &mainMessageOutcome);
    leaveCaveOutcome.setNextNodes(&mainMessageOutcome, &mainMessageOutcome);
    //needKeyOutcome.setNextNodes(&startNode, &startNode);

    // Display the initial message
    MessageNode* currentMessageNode = &startNode;
    while (currentMessageNode != nullptr) {
        currentMessageNode->displayMessage();

        // Get user input (1 or 2)
        std::cout << "Enter your choice (1 or 2): ";
        int userChoice;
        std::cin >> userChoice;

        // Update current node based on user choice
        currentMessageNode = currentMessageNode->performOutcome(userChoice, currentMessageNode);
    }

    return 0;
}


//------------Trash below------------------//



//class MessageNode;
//
//class Item {
//private:
//    std::string name;
//public:
//    Item(const std::string& name) : name(name) {}
//    std::string getName()const;
//    bool operator==(const Item& other) const;
//    ~Item(){ }
//};
//
//class Inventory {
//protected:
//    Inventory(const std::string value): value_(value){}
//    static Inventory* singleton_;
//    std::string value_;
//private:
//    std::vector<Item*> items;
//
//    //static std::unique_ptr<Inventory> instance;
//    //Inventory(){}
//public:
//    ~Inventory();
//    static Inventory *getInstance(const std::string&);
//    void addItem(Item* item);
//    void deleteItem(Item* item);
//    bool hasItem(const Item& itemName) const;
//    void displayInventory() const;
//    void clearInventory();
//    Inventory(Inventory &other) = delete;
//    void operator=(const Inventory &) = delete;
//    std::string value()const {
//        return value_;
//   }
//};
//
//class MessageOutcome {
//private:
//    int index;
//    std::string result;
//    MessageNode* nextNode;
//public:
//    MessageOutcome(int index, const std::string& result, MessageNode* nextNode);
//    std::string getResult();
//    MessageNode* getNextNode();
//    virtual MessageNode* PerformOutcome(int choice, MessageNode* currentMessageNode);
//};
//
//class RandomMessageOutcome : public MessageOutcome {
//private:
//    std::string randomResult;
//    double probability;
//    MessageNode* randomNextNode;
//
//public:
//    RandomMessageOutcome(int index, const std::string& result, const std::string& randomResult, double probability, MessageNode* nextNode, MessageNode* randomNextNode = nullptr);
//    std::string getRandomResult();
//    double getProbability();
//    MessageNode* getNextRandomNode();
//    virtual MessageNode* PerformOutcome(int choice, MessageNode* currentMessageNode) override;
//};
//
//class AddItemOutcome : public MessageOutcome {
//private:
//    Item* itemToAdd;
//    Inventory* inventory;
//public:
//    AddItemOutcome(int index, const std::string& result, Item* itemToAdd, Inventory* inventory, MessageNode* nextNode);
//    virtual MessageNode* PerformOutcome(int choice, MessageNode* currentMessageNode) override;
//};
//
//class NeedItemOutcome : public MessageOutcome {
//private:
//    Item requiredItem;
//    Inventory* inventory;
//public:
//    NeedItemOutcome(int index, const std::string& result, const Item& requiredItem, Inventory* inventory, MessageNode* nextNode);
//    Item& getReqItem();
//    virtual MessageNode* PerformOutcome(int choice, MessageNode* currentMessageNode) override;
//};
//
//class RandomItemOutcome : public RandomMessageOutcome {
//private:
//    Item* newItem;
//
//public:
//    RandomItemOutcome(int index, const std::string& result, const std::string& randomResult, double probability, MessageNode* nextNode, MessageNode* randomNextNode, Item* newItem);
//    virtual MessageNode* PerformOutcome(int choice, MessageNode* currentMessageNode) override;
//};
//
//class MessageNode {
//private:
//    int index;
//    std::string description;
//    std::string optionA;
//    std::string optionB;
//    MessageOutcome* nextMessageA;
//    MessageOutcome* nextMessageB;
//
//public:
//    MessageNode(int index, const std::string& description, const std::string& optionA, const std::string& optionB);
//    void displayMessage() const;
//    void setNextNodes(MessageOutcome* node1, MessageOutcome* node2);
//    std::string getResultA() const;
//    std::string getResultB() const;
//    MessageNode* getNextNode1() const;
//    MessageNode* getNextNode2() const;
//    virtual MessageNode* performOutcome(int choice, MessageNode* currentMessageNode) const;
//};
//
//
////Implementation of Item class
//std::string Item:: getName()const { return name; }
//
//bool Item:: operator==(const Item& other) const {
//    return name == other.name;
//}
//
//// Implementation of Inventory class
//////std::unique_ptr<Inventory> Inventory::instance;
//Inventory* Inventory::singleton_ = nullptr;;
//
//Inventory *Inventory::getInstance(const std::string& value) {
//    // Create the instance if it doesn't exist
//    if (singleton_ == nullptr) {
//        singleton_ = new Inventory(value);//std::make_unique<Inventory>();
//    }
//    return singleton_;
//}
//
//void Inventory:: addItem(Item* item) { items.push_back(item); }
//
//void Inventory:: deleteItem(Item* item) {
//    auto it = std::find(items.begin(), items.end(), item);
//    if (it != items.end()) {
//        items.erase(it);
//        delete item;
//    }
//}
//
//bool Inventory:: hasItem(const Item& itemName) const {
//
//    return std::any_of(items.begin(), items.end(), [&itemName](const Item* item) {
//        return *item == itemName;
//        });
//}
//
//void Inventory:: displayInventory() const {
//    std::cout << "Inventory:\n";
//    for (const auto& item : items) {
//        std::cout << "- " << item->getName() << "\n";
//    }
//}
//
//Inventory::~Inventory() {
//    // Cleanup: Delete all items in the inventory
//    for (auto& item : items) {
//        delete item;
//    }
//}
//
//void Inventory::clearInventory() {
//    for (auto& item : items) {
//        delete item;
//    }
//    items.clear();
//}
//
//
//// Implementation of MessageOutcome class
//MessageOutcome::MessageOutcome(int index, const std::string& result, MessageNode* nextNode)
//    : index(index), result(result), nextNode(nextNode) {}
//
//std::string MessageOutcome::getResult() {
//    return result;
//}
//
//MessageNode* MessageOutcome::getNextNode() {
//    return nextNode;
//}
//
//MessageNode* MessageOutcome::PerformOutcome(int choice, MessageNode* currentMessageNode) {
//    std::cout << getResult() << "\n";
//    currentMessageNode = nextNode;
//    return currentMessageNode;
//}
//
//
//// Implementation of RandomMessageOutcome class
//RandomMessageOutcome::RandomMessageOutcome(int index, const std::string& result, const std::string& randomResult, double probability, MessageNode* nextNode, MessageNode* randomNextNode)
//    : MessageOutcome(index, result, nextNode), randomResult(randomResult), probability(probability), randomNextNode(randomNextNode) {}
//
//std::string RandomMessageOutcome::getRandomResult() {
//    return randomResult;
//}
//
//double RandomMessageOutcome::getProbability() {
//    return probability;
//}
//
//MessageNode* RandomMessageOutcome::getNextRandomNode() {
//    return randomNextNode;
//}
//
//MessageNode* RandomMessageOutcome::PerformOutcome(int choice, MessageNode* currentMessageNode) {
//    if (rand() / static_cast<double>(RAND_MAX) < probability) {
//        std::cout << getRandomResult() << "\n";
//        if (randomNextNode != nullptr) {
//            currentMessageNode = getNextRandomNode();
//        }
//        else {
//            currentMessageNode = getNextNode();
//        }
//    }
//    else {
//        std::cout << getResult() << "\n";
//        currentMessageNode = getNextNode();
//    }
//    return currentMessageNode;
//}
//
//// Implementation of AddItemOutcome class
//AddItemOutcome::AddItemOutcome(int index, const std::string& result, Item* itemToAdd, Inventory* inventory, MessageNode* nextNode)
//    : MessageOutcome(index, result, nextNode), itemToAdd(itemToAdd), inventory(inventory) {}
//
//MessageNode* AddItemOutcome::PerformOutcome(int choice, MessageNode* currentMessageNode) {
//    inventory->addItem(itemToAdd);
//    std::cout << getResult() << "\n" << " You obtained: " << itemToAdd->getName() << "!" << "\n";
//    currentMessageNode = getNextNode();
//    return currentMessageNode;
//}
//
//// Implementation of NeedItemOutcome class
//NeedItemOutcome::NeedItemOutcome(int index, const std::string& result, const Item& requiredItem, Inventory* inventory, MessageNode* nextNode)
//    : MessageOutcome(index, result, nextNode), requiredItem(requiredItem), inventory(inventory) {}
//
//Item& NeedItemOutcome::getReqItem() {
//    return requiredItem;
//}
//
//MessageNode* NeedItemOutcome::PerformOutcome(int choice, MessageNode* currentMessageNode) {
//    if (inventory->hasItem(getReqItem())) {
//        std::cout << getResult() << "\n";
//        currentMessageNode = getNextNode();
//    }
//    else {
//        std::cout << "You need the item '" << requiredItem.getName() << "' to proceed.\n";
//        // Optionally delete the needed item from the inventory
//        // inventory->deleteItem(item);
//        currentMessageNode = currentMessageNode;  // Go back to the same node
//    }
//    return currentMessageNode;
//}
//
//// Implementation of RandomItemOutcome class
//RandomItemOutcome::RandomItemOutcome(int index, const std::string& result, const std::string& randomResult, double probability, MessageNode* nextNode, MessageNode* randomNextNode, Item* newItem)
//    : RandomMessageOutcome(index, result, randomResult, probability, nextNode, randomNextNode), newItem(std::move(newItem)) {}
//
//MessageNode* RandomItemOutcome::PerformOutcome(int choice, MessageNode* currentMessageNode) {
//    if (rand() / static_cast<double>(RAND_MAX) < getProbability()) {
//        std::cout << getRandomResult() << "\n";
//        if (getNextRandomNode() != nullptr) {
//            currentMessageNode = getNextRandomNode();
//
//            // Add the new item to the inventory
//            if (newItem) {
//                Inventory::getInstance("INVENTORY")->addItem(newItem);
//            }
//        }
//    }
//    else {
//        std::cout << getResult() << "\n";
//        currentMessageNode = getNextNode();
//    }
//    return currentMessageNode;
//}
//
//// Implementation of MessageNode class
//MessageNode::MessageNode(int index, const std::string& description, const std::string& optionA, const std::string& optionB)
//    : index(index), description(description), optionA(optionA), optionB(optionB), nextMessageA(nullptr), nextMessageB(nullptr) {}
//
//void MessageNode::displayMessage() const {
//    std::cout << description << "\n";
//    std::cout << "1. " << optionA << "\n";
//    std::cout << "2. " << optionB << "\n";
//}
//
//void MessageNode::setNextNodes(MessageOutcome* node1, MessageOutcome* node2) {
//    nextMessageA = node1;
//    nextMessageB = node2;
//}
//
//std::string MessageNode::getResultA() const {
//    return nextMessageA->getResult();
//}
//
//std::string MessageNode::getResultB() const {
//    return nextMessageB->getResult();
//}
//
//MessageNode* MessageNode::getNextNode1() const {
//    return nextMessageA->PerformOutcome(1, nullptr);
//}
//
//MessageNode* MessageNode::getNextNode2() const {
//    return nextMessageB->PerformOutcome(2, nullptr);
//}
//
//MessageNode* MessageNode::performOutcome(int choice, MessageNode* currentMessageNode) const {
//    if (choice == 1) {
//        return getNextNode1();
//    }
//    else if (choice == 2) {
//        return getNextNode2();
//    }
//    else {
//        std::cout << "Please introduce a valid choice.\n";
//        return currentMessageNode;
//    }
//}