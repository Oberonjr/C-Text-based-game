
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

    MessageNode animalNoisesNode(2, "Going into the path, you hear the noises of some animals. You can see quadrupedal shapes on the road.",
        "Go down the road sneakily.", "Go back to where you came from.");

    MessageNode amuletAltarNode(3, "As you continue, you stumble upon an ancient altar. On it, you can see an amulet. To your right, you see a path going down.",
        "Pick up the amulet.", "Continue down the path.");

    MessageNode sidePathNode(4, "At the end of the path, you see what seems to be an abandoned campsite further ahead. To your right, you spot a glade.",
        "Go to the glade.", "Go to the camp.");

    MessageNode rockyRoadNode(5, "The dusty path leads you to a road bifurcated by some rocks.\n You can see a path going down to a glade to your left, and another going to a clifface to your right.",
        "Go to the glade.", "Go towards the rock face.");

    MessageNode gladeNode(6, "The area around the glade is filled with beautiful greenery. You can hear birds singing and bugs buzzing.\n You spot a man-made path that seems to go to some old tents. Alternatively, you spot a place where you could climb up towards the direction you first woke up in. ",
        "Go to the camp.", "Climb back up to the forest where you started in.");

    MessageNode rockDoorsNode(7, "Getting to the clifface, you see an ancient set of doors. In the middle, there is a slot looking like an amulet.",
        "Try to slot something in the doors.", "Go back.");

    MessageNode rustyKeyPickupNode(8, "A cramped stone chamber is revealed. Ancient dried torches are hanging off the wall. You walk further, your eyes adjusting to the dark.\n Inside, you find a rusty key on a pedestal. After picking it up, you can go back on the path you came from, or try to go through a side-tunnel that you just spotted.",
        "Go back on the path.", "Try the side tunnel.");

    MessageNode abandonedCampNode(9, "Looking around the abandoned camp, nothing catches your eye immediately, but you hear some strange noises that are making you extremly scared.\n You can try to continue investigating, or you can go hide behind a rock further away.",
        "Persist and continue to look for goodies.", "Run for your life!");

    MessageNode secretStashNode(10, "Your persistance payed off! You found what looks like a jewel encrusted Easter Egg.\n As you pick it up, angry spirits apparate around you.",
        "Run back to the side path.", "Run towards that rock you saw moments ago.");

    MessageNode rustyDoorNode(11, "You hide behind the rock and catch your breath. You feel safe after a couple of minutes.\n Looking around, you see a rusty door with an old lock.",
        "Try to open the door.", "Go back to the camp.");

    MessageNode endingNode(12, "You walk into a small cove. You see a sturdy row-boat with paddles on the beach.\n In the wall you see weird adorned shapes, with an empty slot in the shape of an egg.",
        "Get into the boat and get outta here.", "Try slotting something into the wall.");

    //Item list
    Item* AncientAmulet = new Item("Ancient Amulet");
    Item* RustyKey = new Item("Rusty Key");
    Item* EasterEgg = new Item("Easter Egg");

    // Nodes with Outcomes

    //Node 1
    MessageOutcome LeftPathOutcome(101, "You head towards the left path.", &animalNoisesNode);
    MessageOutcome RightPathOutcome(102, "You head towards the right path.", &rockyRoadNode);

    //Node 2
    RandomMessageOutcome randomAnimalNoisesOutcome(201, "You succesfully manage to sneak past the animals and go on.",
        "You accidentaly hit a rock as you go.\n The animals startle and run away. The path is clear for now, but they'll be back", 0.5f, &amuletAltarNode, &amuletAltarNode);
    MessageOutcome goBackFromAnimals(202, "You go back to the forest.", &startNode);

    //Node 3
    AddItemOutcome addItemAmuletOutcome(301, "You pick up the old amulet and head down the side-path.", AncientAmulet, inventory, &sidePathNode);
    MessageOutcome ignoreAmuletGoDownSidepath(302, "You ignore the amulet and go down the side-path.", &sidePathNode);

    //Node 4
    MessageOutcome sidepathToGlade(401, "You head towards the glade.", &gladeNode);
    MessageOutcome gotoAbandonedCamp(402, "You decide to look through the camp. \nA cold shiver runs down your spine", &abandonedCampNode);

    //Node 5
    MessageOutcome rockyRoadToGlade(501, "You turn left and descend towards the glade.", &gladeNode);
    MessageOutcome rockyRoadToROckDoors(502, "You continue forward and approach the clifface.", &rockDoorsNode);

    //Node 6
    RandomMessageOutcome gladeClimbBacktrackOutcome(601, "You start climbing, grabbing roots and rocks, pulling yourself up.\n You eventually get back to the rocky road.",
        "As you climb through the greenery, you lose the path that you were following.\n After stumbling for a bit, you see another path opening in front of you.", 0.3f, &rockyRoadNode, &animalNoisesNode);
    MessageOutcome gladeToCampOutcome(602, "You turn towards the camp and head there.", &abandonedCampNode);

    //Node 7
    MessageOutcome backtrackFromRockDoors(701, "You turn away from the doors and go back towards the bifurcated path.\n Perhaps you should check out the glade.", &rockyRoadNode);
    NeedItemOutcome needAmuletOutcome(702, "You go to the massive stone doors and slot in the amulet.\n A small door snaps shut and takes the amulet.\n The ground rumbles as the doors open, revealing what's inside.", *AncientAmulet, inventory, &rustyKeyPickupNode);

    //Node 8
    AddItemOutcome addKeyAndGoPathOutcome(801, "You head back the way you came and walk back on the path towards the bifurcation.\n Perhaps you should go to the glade.", RustyKey, inventory, &rockyRoadNode);
    AddItemOutcome addKeyAndGoTunnel(801, "You take your chances and go in the side tunnel.\n You exit from a concealed hole in the ground, having to push away a lot of greenery to make a path.\n You end up next to an abandoned camp.", RustyKey, inventory, &abandonedCampNode);


    //Node 9
    RandomItemOutcome campInvestigationOutcome(901, "You try to push through the bad feeling and keep looking, but you could swear you felt hands touching and pulling on you.\n You freak out and run back to the side path.",
        "Despite the weird feelings, you push through and look for something of value.", 0.3f, &sidePathNode, &secretStashNode, EasterEgg);
    MessageOutcome campToDoorOutcome(902, "You don't trust this.\n You run for the nearby boulder as you could swear you heard faint breathing right behind you.", &rustyDoorNode);

    //Node 10
    MessageOutcome stashToSidePathOutcome(1001, "You run to the side-path.", &sidePathNode);
    MessageOutcome stashToDoorOutcome(1002, "You run to the boulder.", &rustyDoorNode);

    //Node 11
    RandomMessageOutcome randomBacktrackFromDoor(1101, "You decide to turn back and go to camp.",
        "You turn around, but feel too uneasy to go into the camp. You go around and make your way back to the glade", 0.4f, &abandonedCampNode, &gladeNode);
    NeedItemOutcome needKeyOutcome(1102, "You take out the rusty key and try the lock. After a nudge it opens, and you quickly flee inside.", *RustyKey, inventory, &endingNode);

    //Node 12
    MessageOutcome normalEndingOutcome(1201, "You go in the boat and row away from this place, swearing to never come back again \n Thank you for playing my game :).", nullptr);
    NeedItemOutcome secretEndingOutcome(1202, "You take out the egg and slot it in. The ground rumbles, and the world around you fades away. Suddenly, you understand everything. \n You do not exist. \n You are merely a simulation in some student's makeshift game. \n All your efforts, all your struggles were for nothing. \n You exist as nothing more than pixels on a screen, text in a console. \n\n And you will dissappear as soon as they click that X, as the program will unload you from it's memory. \n\n Congratulations on finding the secret ending! Thank you for playing my game :)", *EasterEgg, inventory, nullptr);


    // Tying Nodes Together 
    startNode.setNextNodes(&LeftPathOutcome, &RightPathOutcome);
    animalNoisesNode.setNextNodes(&randomAnimalNoisesOutcome, &goBackFromAnimals);
    amuletAltarNode.setNextNodes(&addItemAmuletOutcome, &ignoreAmuletGoDownSidepath);
    sidePathNode.setNextNodes(&sidepathToGlade, &gotoAbandonedCamp);
    rockyRoadNode.setNextNodes(&rockyRoadToGlade, &rockyRoadToROckDoors);
    gladeNode.setNextNodes(&gladeToCampOutcome, &gladeClimbBacktrackOutcome);
    rockDoorsNode.setNextNodes(&needAmuletOutcome, &backtrackFromRockDoors);
    rustyKeyPickupNode.setNextNodes(&addKeyAndGoPathOutcome, &addKeyAndGoTunnel);
    abandonedCampNode.setNextNodes(&campInvestigationOutcome, &campToDoorOutcome);
    secretStashNode.setNextNodes(&stashToSidePathOutcome, &stashToDoorOutcome);
    rustyDoorNode.setNextNodes(&needKeyOutcome, &randomBacktrackFromDoor);
    endingNode.setNextNodes(&normalEndingOutcome, &secretEndingOutcome);


    // Display the initial message
    MessageNode& currentMessageNode = startNode;

    //Keep going until current node is null
    while (true) {
        currentMessageNode.displayMessage();

        // Get user input (1 or 2)
        std::cout << "Enter your choice (1 or 2): ";
        int userChoice;
        std::cin >> userChoice;

        // Update current node based on user choice
        const MessageNode* pNextMessageNode = currentMessageNode.performOutcome(userChoice, &currentMessageNode);
        if (pNextMessageNode == nullptr) break;
        currentMessageNode = *pNextMessageNode;
    }

    return 0;
}

