#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "GameController.h"
#include "UserAction.h"
#include "queue"
using namespace wfrest;
using namespace ctl;
using namespace std;

GameController& controller = GameController::getInstance("default");

// -- DON'T MODIFY ANY CODE ABOVE THIS LINE -- //
// -- YOU ARE ALLOW TO ADD HEADER FILES UNDER THIS LINE -- //

// TODO: Choose your recipe mode
// you may want to have different strategy for different recipe mode
/*
const string RecipeMode = "salad";
//string RecipeMode = "salad_cheeseburger";
//const string RecipeMode = "all";
*/

// A template GLOBAL VARIABLE vector to store operations
// Feel free to modify this data structure! (or create your own to use)
#include <queue>
queue<char> operations;

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

    { UpperCuttingCounter, {0, 14} },
    { LowerCuttingCounter, {8, 14} },
    // There are so many normal counters, this is only one of it
    { NormalCounter820, {8, 20} },
    { NormalCounter812, {8, 12} },
    { NormalCounter813, {8, 13} },
    { NormalCounter007, {0, 7} },
    { NormalCounter013, {0, 13} }
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
    { UpperCuttingCounter, "w" },
    { LowerCuttingCounter, "s" },
    // There are so many normal counters, this is only one of it
    { NormalCounter007, "w" },
    { NormalCounter013, "w" },
    { NormalCounter812, "s" },
    { NormalCounter813, "s" },
    { NormalCounter820, "s" }
};

void DefaultInitialize();
void DefaultSendOperation();
void MakeSalad();
void MakeBurger();
void MakeCheeseBurger();
void MakeMegaBurger();
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
    while(!operation.empty()) operations.pop();
}

// Main Function of you game logic
void UserAction::SendOperation() {
    // TODO: Implement your gaming logic here
    // DefaultSendOperation() will make you a MEGABurger!
    //DefaultSendOperation();
    OMGOWOSendOperationcode();
}


// -- Moving series functions Below -- //

void MovePointToPoint(pair<int, int> from, pair<int, int> to, GameController& controller) {
    // TODO: Move from one point to another point
    char xdir = from.first < to.first ? 's' : 'w';
    char ydir = from.second < to.second ? 'd' : 'a';

    int xcnt = abs(from.first - to.first);
    int ycnt = abs(from.second - to.second);

    for(int i=0;i<xcnt; i++){
        operations.push(xdir);
    }
      for(int i=0;i<ycnt; i++){
        operations.push(ydir);
    }
}

void MovePointToCounter(pair<int, int> fromPoint, Counter toCounter, GameController& controller) {
    // TODO: Move from one point to a counter
    pair<int, int> targetPosition = counterPosition.at(toCounter);
    MovePointToPoint(fromPoint,targetPosition,controller);

}

void MoveCounterToCounter(Counter from, Counter to, GameController& controller) {
    // TODO: Move from one counter to another counter
    pair<int, int> fromPosition = counterPosition.at(from);
    pair<int, int> toPosition = counterPosition.at(to);
    MovePointToPoint(fromPosition,toPosition,controller);
    controller.getPlayerPosition();

}
void MoveCounterToCounterAndInteract(Counter from, Counter to){
    MoveCounterToCounter(from,to);
    operations.push(counterDirection.at(to));
    operations.push('e');
}
void MovePointToCounterAndInteract(pair <int,int> from, Counter toCounter){
    MovePointToCounter(from,toCounter);
    operations.push(counterDirection.at(toCounter));
    operations.push('e');
}

void Wait(int times) {
    // TODO: Wait for times
    for (int i = 0; i < times; i ++) {
        continue;
    }
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
    vector<Order> orderList = controller.GetOrderList();
    if (orderList.empty()) {
        return Salad;
    }
    return orderList[0].recipe;
    //return MegaBurger;
}

Recipe GetNextOrder() {
    // Return the next order based on the Recipe Mode
    if (controller.GetRecipeMode() == "Salad") {
        return SaladModeStrategy();
    } else if (controller.GetRecipeMode() == "SaladAndCheeseBurger") {
        return SaladCheeseburgerModeStrategy();
    } else {
        return AllRecipeModeStrategy();
    }
}

// -- Strategy for different Recipe Mode Above -- //

// -- Miscallaneous functions Below -- //

void CutIngredient(int times) {
    // TODO: Cut the Ingredient for times
    for(int i=0;i<times;i++){
        operations.push('f');
    }
}

// -- Miscallaneous functions Above -- //

// -- Pipeline Funtions Below -- //
// You are welcome to change the function prototype
// Like changing the return type or adding more parameters
void MakeSalad(GameController& controller) {
     // TODO: Salad Making Pipeline
    // Move To Cabbage Counter
    MovePointToCounterAndInteract(controller.GetPlayerPosition(),CabbageCounter);
    // Grab Cabbage
    // Move To Cutting Counter
    MoveCounterToCounterAndInteract(CabbageCounter,CuttingCounter);
    // Cut Cabbage
    CutIngredient(5);
    // Grab Cabbage Slices
    operations.push('e');
    // Move To A Normal Counter
    // Put Down Cabbage Slices
    MoveCounterToCounterAndInteract(CuttingCounter,NormalCounter813);
    // Move To Tomato Counter
    // Grab Tomato
    MoveCounterToCounterAndInteract(NormalCounter813,TomatoCounter);
    // Move To A Cutting Counter
    MoveCounterToCounterAndInteract(TomatoCounter,CuttingCounter);
    // Cut Tomato
    CutIngredient(3);
    // Move To Plate Counter
    // Grab Plate
    MoveCounterToCounterAndInteract(CuttingCounter, PlatesCounter);
    // Move To A Cutting Counter
    // Grab Tomato Slices
    MoveCounterToCounterAndInteract(PlatesCounter,CuttingCounter);
    // Move To A Normal Counter
    // Grab Cabbage Slices
    MoveCounterToCounterAndInteract(CuttingCounter,NormalCounter813);
    // Move To Delivery Counter
    MoveCounterToCounterAndInteract(NormalCounter813,DeliveryCounter);
    // Send Order!
}



void MakeBurger(GameController& controller) {
    MovePointToCounterAndInteract(controller.GetPlayerPosition(), BreadBlockCounter);

    MoveCounterToCounterAndInteract(BreadBlockCounter, NormalCounter013);

    MoveCounterToCounterAndInteract(NormalCounter013, RawPattyCounter);

    MoveCounterToCounterAndInteract(RawPattyCounter, StoveCounter);
    Wait(20);
    MoveCounterToCounterAndInteract(StoveCounter, PlatesCounter);

    MoveCounterToCounterAndInteract(PlatesCounter, StoveCounter);
    Wait(30);
    MoveCounterToCounter(StoveCounter, NormalCounter013);

    MoveCounterToCounter(NormalCounter013, DeliveryCounter);
}


void MakeCheeseBurger(GameController& controller) {
    //plate>>bread>>A:normal between cheese and cutting board>>
    //cheese>>cutting board>>A>>meat>>stove>>A>>delivery
    MovePointToCounterAndInteract(controller.GetPlayerPosition(),PlatesCounter);
    MoveCounterToCounterAndInteract(PlatesCounter,BreadCounter);
    MoveCounterToCounterAndInteract(BreadCounter,NormalCounter820);
    MoveCounterToCounterAndInteract(NormalCounter820,CheeseBlockCounter);
    MoveCounterToCounterAndInteract(CheeseBlockCounter,UpperCuttingCounter);
    CutIngredient(3);
    operations.push.back("e");
    MoveCounterToCounterAndInteract(UpperCuttingCounter,NormalCounter820);
    MoveCounterToCounterAndInteract(NormalCounter820,RawPattyCounter);
    MoveCounterToCounterAndInteract(RawPattyCounter,StoveCounter);
    MoveCounterToCounterAndInteract(RawPattyCounter,StoveCounter);
    //wait
    Wait(60);
    MoveCounterToCounterAndInteract(StoveCounter,NormalCounter820);
    operations.push.back("e");
    MoveCounterToCounterAndInteract(NormalCounter820,DeliveryCounter);
}


void MakeMegaBurger(GameController& controller) {
    MovePointToCounterAndInteract(controller.GetPlayerPosition(), CabbageCounter);
    
    MoveCounterToCounterAndInteract(CabbageCounter, LowerCuttingCounter);
    CutIngredient(5);
    operations.push('e');
    MoveCounterToCounterAndInteract(LowerCuttingCounter, NormalCounter813);
    
    MoveCounterToCounterAndInteract(NormalCounter813, TomatoBlockCounter);
    
    MoveCounterToCounterAndInteract(TomatoBlockCounter, LowerCuttingCounter);
    CutIngredient(5);
    
    MoveCounterToCounterAndInteract(LowerCuttingCounter, BreadBlockCounter);
    
    MoveCounterToCounterAndInteract(BreadBlockCounter, NormalCounter007);
    
    MoveCounterToCounterAndInteract(NormalCounter007, CheeseBlockCounter);
    
    MoveCounterToCounterAndInteract(CheeseBlockCounter, UpperCuttingCounter);
    CutIngredient(5);
    
    MoveCounterToCounterAndInteract(UpperCuttingCounter, RawPattyCounter);
    
    MoveCounterToCounterAndInteract(RawPattyCounter, StoveCounter);
    Wait(20);
    MoveCounterToCounterAndInteract(StoveCounter, PlatesCounter);
    
    MoveCounterToCounterAndInteract(PlatesCounter, StoveCounter);
    Wait(30);
    MoveCounterToCounterAndInteract(StoveCounter, UpperCuttingCounter);
    
    MoveCounterToCounterAndInteract(UpperCuttingCounter, NormalCounter007);
    
    MoveCounterToCounterAndInteract(NormalCounter007, LowerCuttingCounter);
    
    MoveCounterToCounterAndInteract(LowerCuttingCounter, NormalCounter813);
    
    MoveCounterToCounterAndInteract(NormalCounter813, DeliveryCounter);

}

void OMGOWOSendOperationcode(){
    char s = '';
        if (operations.empty()) {
            Recipe nextRecipe = GetNextOrder();
            if(nextRecipe == Salad) MakeSalad();
            else if(nextRecipe == Burger) MakeBurger();
            else if(nextRecipe == CheeseBurger) MakeCheeseBurger();
            else MakeMegaBurger();
            return;
        }

        s=operations.front();
        operations.pop();

        if (s == 'w') controller.MoveUp();
        else if (s == 's') controller.MoveDown();
        else if (s == 'a') controller.MoveLeft();
        else if (s == 'd') controller.MoveRight();
        else if (s == 'e') controller.Interact();
        else if (s == 'f') controller.InteractSpecial();
}

// -- Pipeline Funtions Below -- //

