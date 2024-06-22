#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "GameController.h"
#include "UserAction.h"

using namespace wfrest;
using namespace ctl;
using namespace std;

GameController& controller = GameController::getInstance("default");

// -- DON'T MODIFY ANY CODE ABOVE THIS LINE -- //
// -- YOU ARE ALLOW TO ADD HEADER FILES UNDER THIS LINE -- //

// TODO: Choose your recipe mode
// you may want to have different strategy for different recipe mode

const string RecipeMode = "salad";
// const string RecipeMode = "salad_cheeseburger";
// const string RecipeMode = "all";


// A template GLOBAL VARIABLE vector to store operations
// Feel free to modify this data structure! (or create your own to use)
vector<string> operations;

// A template map to store the position of each counter
// Question: How do you extend this map to store more than one position for a counter?
// Question2: cutting / normal counter have more than one position, how will you handle it?
const map<Counter, pair<int, int>> counterPosition = {
    { BreadCounter, {0, 1} },
    { CabbageCounter, {8, 2} },
    { CheeseBlockCounter, {0, 9} },
    { TomatoCounter, {8, 5} },
    { RawPattyCounter, {0, 20} },
    { StoveCounter, {0, 19} },
    { PlatesCounter, {3, 20} },
    { TrashCounter, {6, 20} },
    { DeliveryCounter, {1, 20} },

    // There are 2 cutting counters, this is only one of it
    { CuttingCounter, {8, 15} },
    // There are so many normal counters, this is only one of it
    { NormalCounter, {8, 20} }
};

const map<Counter, string> counterDirection = {
    { BreadCounter, "w" },
    { CabbageCounter, "s" },
    { CheeseBlockCounter, "w" },
    { TomatoCounter, "s" },
    { RawPattyCounter, "w" },
    { StoveCounter, "w" },
    { PlatesCounter, "d" },
    { TrashCounter, "d" },
    { DeliveryCounter, "d" },

    // There are 2 cutting counters, this is only one of it
    { CuttingCounter, "s" },
    // There are so many normal counters, this is only one of it
    { NormalCounter, "d" }
};

void DefaultInitialize();
void DefaultSendOperation();
void MegaBurgerInitialize();
void MegaBurger~SendOperation();

// Init the game (DO NOT MODIFY THIS FUNCTION)
void UserAction::InitGame() {
    Initialize();
    // Set the response to "ok" when finished initialization
    controller.SetResponse("ok");
}

// Just a cute Initializing function
void UserAction::Initialize() {
    // TODO: You can do some initialization in this function.
    // Feel free to modify this function.
    // DefaultInitialize() will make you a MEGABurger!
    cout << "Initializing the game..." << endl;
    DefaultInitialize();
}

// Main Function of you game logic
void UserAction::SendOperation() {
    // TODO: Implement your gaming logic here
    // DefaultSendOperation() will make you a MEGABurger!
    DefaultSendOperation();
}


// -- Moving series functions Below -- //

void MovePointToPoint(pair<int, int> from, pair<int, int> to, GameController& controller) {
    char xdir = from.first < to.first ? 's' : 'w';
    char ydir = from.second < to.second ? 'd' : 'a';
    
    int xcnt = abs(from.first - to.first);
    int ycnt = abs(from.second - to.second);

    for (i = 0; i < xcnt; i ++) {w
        operations.push(xdir);
    }
    for (i = 0; i < ycnt; i ++) {
        operations.push(ydir);
    }
}

void MovePointToCounter(pair<int, int> fromPoint, Counter toCounter, GameController& controller) {
    pair<int, int> targetPosition = counterPosition.at(toCounter);
    MovePointToPoint(fromPoint, targetPosition);

}

void MoveCounterToCounter(Counter from, Counter to, GameController& controller) {
    pair<int, int> fromposition = counterPosition.at(from);
    MovePointToCounter(fromposition, to);
}

void MoveCounterToCounterAndInteract(Counter from, Counter to, GameController& controller) {
    MoveCounterToCounter(from, to);
    operations.push(counterDirection.at(to));
    operations.push('e');
}

// -- Moving series functions Above -- //

// -- Strategy for different Recipe Mode Below -- //

Recipe SaladModeStrategy() {
    // Only salad will be in order in Salad Mode
    return Salad;
}

Recipe SaladCheeseburgerModeStrategy() {
    // TODO: Implement your salad cheeseburger mode strategy here
    // Below is a simple example, feel free to change it

    vector<Order> orderList = controller.GetOrderList();
    if (orderList.empty()) {
        return Salad;
    }
    return orderList[0].recipe;
}

Recipe AllRecipeModeStrategy() {
    // TODO: Implement your all recipe mode strategy here
    // Below is a simple example, feel free to change it

    return MegaBurger;
}

Recipe GetNextOrder() {
    // Return the next order based on the Recipe Mode
    if (RecipeMode == "salad") {
        return SaladModeStrategy();
    } else if (RecipeMode == "salad_cheeseburger") {
        return SaladCheeseburgerModeStrategy();
    } else {
        return AllRecipeModeStrategy();
    }
}

// -- Strategy for different Recipe Mode Above -- //

// -- Miscallaneous functions Below -- //

void CutIngredient(int times, GameController& controller) {
    // TODO: Cut the Ingredient for times
    for (int i = 0; i < times; i ++) {
        operations.push('f');
    }
}
void Wait(int times, GameController& controller) {
    // TODO: Wait for times
    for (int i = 0; i < times; i ++) {
        continue;
    }
}

// -- Miscallaneous functions Above -- //

// -- Pipeline Funtions Below -- //

// You are welcome to change the function prototype
// Like changing the return type or adding more parameters
void MakeSalad(GameController& controller) {
    // TODO: Salad Making Pipeline
    // Move To Cabbage Counter
    // Grab Cabbage
    // Move To Cutting Counter
    // Cut Cabbage
    // Grab Cabbage Slices
    // Move To A Normal Counter
    // Put Down Cabbage Slices
    // Move To Tomato Counter
    // Grab Tomato
    // Move To A Cutting Counter
    // Cut Tomato
    // Move To Plate Counter
    // Grab Plate
    // Move To A Cutting Counter
    // Grab Tomato Slices
    // Move To A Normal Counter
    // Grab Cabbage Slices
    // Move To Delivery Counter
    // Send Order!
}

void SimpleExample() {
    // The beginning steps of making a salad

    operations.clear();
    // Move to Cabbage Counter
    pair<int, int> playerPosition = controller.GetPlayerPosition();
    MovePointToCounter(playerPosition, CabbageCounter, controller);
    // Grab Cabbage
    operations.push_back("e");
    // Move to Cutting Counter
    MoveCounterToCounter(CabbageCounter, CuttingCounter, controller);
    // Cut Cabbage
    operations.push_back("e");
    // ... Do The Rest By Yourself !
}

void MakeBurger(GameController& controller) {}
void MakeCheeseBurger(GameController& controller) {}
void MakeMegaBurger(GameController& controller) {
    MovePointToCounter(controller.GetPlayerPosition(), SaladBlockCounter);
    operations.push('e');
    MoveCounterToCounter(SaladBlockCounter, Block811);
    operations.push('e');
    MoveCounterToCounter(Block811, TomatoBlockCounter);
    operations.push('e');
    MoveCounterToCounterAndInteract(TomatoBlockCounter, LowerCuttingCounter);
    CutIngredient(3);
    MoveCounterToCounterAndInteract(LowerCuttingCounter, BreadBlockCounter);
    CutIngredient(3);
    MoveCounterToCounter(BreadBlockCounter, Block011);
    operations.push('e');
    MoveCounterToCounter(Block011, CheeseBlockCounter);
    operations.push('e');
    MoveCounterToCounterAndInteract(CheeseBlockCounter, UpperCuttingCounter);
    CutIngredient(3);
    MoveCounterToCounterAndInteract(UpperCuttingCounter, RawPattyCounter);
    operations.push('e');
    MoveCounterToCounterAndInteract(RawPattyCounter, StoveCounter);
    operations.push('e');
    Wait(20);
    MoveCounterToCounterAndInteract(StoveCounter, PlatesCounter);
    operations.push('e');
    MoveCounterToCounterAndInteract(PlatesCounter, StoveCounter);
    Wait(30);
    operations.push('e');
    MoveCounterToCounterAndInteract(StoveCounter, UpperCuttingCounter);
    operations.push('e');
    MoveCounterToCounterAndInteract(UpperCuttingCounter, Block011);
    operations.push('e');
    MoveCounterToCounterAndInteract(Block011, LowerCuttingCounter);
    operations.push('e');
    MoveCounterToCounterAndInteract(LowerCuttingCounter, Block811);
    operations.push('e');
    MoveCounterToCounterAndInteract(Block811, DeliveryCounter);
    operations.push('e');
}

// -- Pipeline Funtions Below -- //

// -- Default Series Function Below -- //

// SendOperation function template, free MEGABurger for you!
void DefaultSendOperation() {
    string s = "";
    if (!operations.empty()) {
        s = operations.back();
        operations.pop_back();
        cout << "Operation: " << s << endl;
    }
    if (s == "w") controller.MoveUp();
    if (s == "s") controller.MoveDown();
    if (s == "a") controller.MoveLeft();
    if (s == "d") controller.MoveRight();
    if (s == "e") controller.Interact();
    if (s == "f") controller.InteractSpecial();
}

void DefaultInitialize() {
    operations = {
        "w", "w", "w", "w", "e", "d", "d", "d", "d", "w", "e", "f", "f", "f", // grab cheese and cut it
        "d", "d", "d", "d", "d", "d", "w", "e", "a", "w", "e", "s", "s", "d", "e", // fry meat and grab plate
        "a", "a", "a", "a", "w", "w", "e", "d", "w", "e", // grab cheese slices and cooked meat
        "e", "e", "e", "e", "e", "e", "e", "e", "e", "e", // wait for the meat to be cooked
        "e", "e", "e", "e", "e", "e", "e", "e", "e", "e", // wait for the meat to be cooked
        "e", "e", "e", "e", "e", "e", "e", "e", "e", "e", // wait for the meat to be cooked
        "e", "e", "e", "e", "e", "e", "e", "e", "e", "e", // wait for the meat to be cooked
        "e", "e", "e", "e", "e", "e", "e", "e", "e", "e", // wait for the meat to be cooked
        "e", "e", "e", "e", "e", "e", "e", "e", "e", "e", // wait for the meat to be cooked
        "e", "e", "e", "e", "e", "e", "e", "e", "e", "e", // wait for the meat to be cooked
        "e", "e", "e", "e", "e", "e", "e", "e", "e", "e", // wait for the meat to be cooked
        "e", "e", "e", "e", "e", "e", "e", "e", "e", "e", // wait for the meat to be cooked
        "e", "e", "e", "e", "e", "e", "e", "e", "e", "e", // wait for the meat to be cooked
        "e", "e", "e", "e", "e", "e", "e", "e", "e", "e", // wait for the meat to be cooked
        "e", "e", "e", "e", "e", "e", "e", "e", "e", "e", // wait for the meat to be cooked
        "e", "e", "e", "e", "e", "e", "e", "e", "e", "e", // wait for the meat to be cooked
        "a", "a", "a", "a", "w", "e", // put the plate down
        "s", "s", "s", "s", "s", "s", "s", "s", // move down
        "a", "a", "a", "a", "a", "a", "s", "e",  // grab tomato
        "d", "d", "d", "d", "d", "d", "d", "s", "e", "f", "f", "f", // cut tomato
        "e", "a", "s", "e", "a", "a", "a", "a", "a", "a", "a", "a", "a", "s", "e", // grab lettuce
        "d", "d", "d", "d", "d", "d", "d", "d", "d", "d", // move to cutting counter
        "s", "e", "f", "f", "f", "f", "f", // cut lettuce
        "e", "a", "w", "w", "w", "w", "w", "w", "w", "w", "e", "e", // grab plate
        "s", "s", "s", "s", "s", "s", "s", "s", // move down
        "e", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", // move to bottom left
        "w", "w", "w", "w", "w", "w", "w", "w", "w", "w", // move to bread counter
        "d", "w", "e", "a", "w", "e", "d", "w", "e", // grab bread
        "e", "d", "d", "d", "d", "d", "d", "d", "d", "d", "d", "d", "d", "d", "d",
        "d", "d", "d", "d", "d", "d", "d", "d", "d", "d", "d", "d", "d", "d", "e" // finish
    };
    reverse(operations.begin(), operations.end());
}
