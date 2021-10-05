//
//  GameEngine.cpp
//  Warzone Game Engine
//
//  Created by Vanessa Razon on 2021-09-24.
//  Copyright © 2021 Vanessa Razon. All rights reserved.
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
    std::cout << "END OF PROGRAM: Thank you for playing Warzone" <<endl;
    state = "end";
}



// Start state: includes new game message and determines if user's command is valid to load a map
// (if valid, map is loaded and  game transitions to map loaded state)
void GameEngine::start()  {
    if (command == "loadMap") {
        loadMap();
    }
    else {
            std::cout << "ERROR: Invalid command for " << state << endl;
    }
    
    }

// Map loaded state: determines if user's command is valid to load another map (stays in map loaded state)
// or to validate the map (map is validated and game transitions to map validated state)
void GameEngine::mapLoaded() {
    
    if (command == "loadMap") {
        loadMap();
        std::cout << "\nCurrent state: " << state << endl;
    }
        else if (command == "validateMap")
            validateMap();
    else
        std::cout << "ERROR: Invalid command for " << state << endl;
    
}

// Map validated state: determines if user's command is valid to add a player
// (player is added and game transitions to player added state)
void GameEngine::mapValidated() {
    
    if (command == "addPlayer")
        addPlayer();
    else
        std::cout << "ERROR: Invalid command for " << state << endl;
}

// Players added state: determines if user's command is valid to add another player (stays in players added state)
// or to move on to assign countries (countries are assigned and game transitions to assign reinforcement state)
void GameEngine::playersAdded() {
    if (command == "addPlayer") {
        addPlayer();
        std::cout << "\nCurrent state: " << state << endl;
    }
    else if (command == "assignCountries")
        assignCountries();
    else
        std::cout << "ERROR: Invalid command for " << state << endl;
}

void GameEngine::assignReinforcement() {
    if (command == "issueOrder")
        issueOrder();
    else
        std::cout << "ERROR: Invalid command for " << state << endl;
}

void GameEngine::issueOrders() {
    if (command == "issueOrder") {
        issueOrder();
        std::cout << "\nCurrent state: " << state << endl;
    }
    else if (command == "endIssueOrders")
        endIssueOrders();
    else
        std::cout << "ERROR: Invalid command for " << state << endl;
}

void GameEngine::executeOrders() {
    if (command == "execOrder") {
        execOrder();
        std::cout << "\nCurrent state: " << state << endl;
    }
    else if (command == "endExecOrders")
        endExecOrders();
    else
        std::cout << "ERROR: Invalid command for " << state << endl;
}

/* PUBLIC FCTS TO ADD?
 


// Win state: Ends the game and determines if user's command is valid to start a new game
// (game transitions back to start and a new game begins) or to end the program
void GameEngine:: win() {
    std::cout << "END OF GAME: Congratulations to the winner!" << endl;
    // Code relevant to the win state
    state = "win";
    
    std::cout << "\nCurrent state: " << state << endl;
    std::cout << "Choose one of the following:\n\t1. play\n\t2. end" << endl;
    std::cin >> command;
    
    while (command != "play" && command != "end") {
        std::cout << "ERROR: Invalid command for " << state << endl;
        std::cout << "Choose one of the following:\n\t1. play\n\t2. end" << endl;
        std::cin >> command;
    }
    if (command == "play") {
        play();
    }
    else
        end();
}

*/
