//
//  GameEngine.cpp
//  COMP 345 - Assignment 1 - Team DN02
//  Warzone Game Engine: controls the flow of the game using the user's keyboard inputs as commands
//

#include "GameEngine.h"
#include <string>
#include <iostream>
using namespace std;


//Constructor
GameEngine::GameEngine() : state("start"), command("") {
    
}

//Copy constructor
GameEngine::GameEngine(const GameEngine& g) {
    state = g.state;
    command = g.command;
}

//Assignment operator
GameEngine& GameEngine::operator=(const GameEngine& g) {
    state = g.state;
    command = g.command;
    return *this;
}

//Insertion stream operator
std::ostream& operator<<(std::ostream &strm, const GameEngine &g) {
    return strm << "\nCurrent state: " << g.state << endl;
}


//Transitions of the game

//Transition to load the map
void GameEngine::loadMap() {
    std::cout << "Loading map..." << endl;
    // Code for loading map
    state = "map loaded";
}

void GameEngine::validateMap() {
    std::cout << "Validating map..." << endl;
    // Code for validating map
    state = "map validated";
}

void GameEngine::addPlayer() {
    std::cout << "Adding player..." << endl;
    // Code for adding a player
    state = "players added";
}

void GameEngine::assignCountries() {
    std::cout << "Assigning countries..." <<endl;
    // Code for assigning countries
    state = "assign reinforcement";
}

void GameEngine::issueOrder() {
    std::cout << "Issuing orders... " << endl;
    // Code for issuing orders
    state = "issue orders";
}

void GameEngine::endIssueOrders() {
    std::cout << "Ending issued orders... " <<endl;
    // Code for ending issued orders
    state = "execute orders";
}

void GameEngine::execOrder() {
    std::cout << "Executing orders... " <<endl;
    // Code for executing orders
    state = "execute orders";
}

void GameEngine::endExecOrders() {
    std::cout << "Ending executed orders... " <<endl;
    // Code for ending orders
    state = "assign reinforcement";
}

void GameEngine:: win() {
    std::cout << "END OF GAME: Congratulations to the winner!" << endl;
    // Code relevant to the win state
    state = "win";
}

void GameEngine::play() {
    std::cout << "Starting a new game...\n" <<endl;
}

void GameEngine::end() {
    std::cout << "--END OF PROGRAM: Thank you for playing Warzone--" <<endl;
    state = "end";
}


// States of the game: In all states, if the command is not valid, user will be
//prompted for another command

// Start state: determines if user's command is valid to load a map
// (if valid, game transitions to map loaded state)
void GameEngine::start()  {
    if (command == "loadMap") {
        loadMap();
    }
    else {
        std::cout << "ERROR: Invalid command for " << state << " state" << endl;
    }
    
}

// Map loaded state: determines if user's command is valid to load another map (stays in map loaded state)
// or to validate the map (game transitions to map validated state)
void GameEngine::mapLoaded() {
    
    if (command == "loadMap") {
        loadMap();
        std::cout << "\nCurrent state: " << state << endl;
    }
    else if (command == "validateMap")
        validateMap();
    else
        std::cout << "ERROR: Invalid command for " << state << " state" << endl;
    
}

// Map validated state: determines if user's command is valid to add a player
// (game transitions to player added state)
void GameEngine::mapValidated() {
    
    if (command == "addPlayer")
        addPlayer();
    else
        std::cout << "ERROR: Invalid command for " << state << " state" << endl;
}

// Players added state: determines if user's command is valid to add another player (stays in players added state)
// or to move on to assign countries (game transitions to assign reinforcement state)
void GameEngine::playersAdded() {
    if (command == "addPlayer") {
        addPlayer();
        std::cout << "\nCurrent state: " << state  << endl;
    }
    else if (command == "assignCountries")
        assignCountries();
    else
        std::cout << "ERROR: Invalid command for " << state << " state" << endl;
}

// Assign reinforcement state: determines if user's command is valid to issue an order (game
// transistions to issue order state)
void GameEngine::assignReinforcement() {
    if (command == "issueOrder")
        issueOrder();
    else
        std::cout << "ERROR: Invalid command for " << state << " state" << endl;
}

// Issue orders state: determines if user's command is valid to issue an order (game
// stays in issue order state) or to end issued orders (game transitions to execute orders state)
void GameEngine::issueOrders() {
    if (command == "issueOrder") {
        issueOrder();
        std::cout << "\nCurrent state: " << state << endl;
    }
    else if (command == "endIssueOrders")
        endIssueOrders();
    else
        std::cout << "ERROR: Invalid command for " << state << " state" << endl;
}

// Execute orders state: determines if user's command is valid to execute an order (game
// stays in execute order state), to end executed orders (game transitions to assign reinforcement state)
// or to declare the winner (transition to the win state)
void GameEngine::executeOrders() {
    if (command == "execOrder") {
        execOrder();
        std::cout << "\nCurrent state: " << state << endl;
    }
    else if (command == "endExecOrders")
        endExecOrders();
    else if (command == "win")
        win();
    else
        std::cout << "ERROR: Invalid command for " << state << " state" << endl;
}
