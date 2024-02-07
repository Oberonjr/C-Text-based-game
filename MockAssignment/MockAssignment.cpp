
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

