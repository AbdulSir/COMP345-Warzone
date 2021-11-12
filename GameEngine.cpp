//
//  GameEngine.cpp
//  COMP 345 - Assignment 1 - Team DN02
//  Warzone Game Engine: controls the flow of the game using the user's keyboard inputs as commands
//

#include "GameEngine.h"
#include "Player.h"
#include <string>
#include <iostream>
using namespace std;


class Player;

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
    state = "start";
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

void GameEngine::mainGameLoop(){
    cout << "Starting Game"<<endl;
    int numberOfTerritories; //will territories vector be created in part 2?
    vector<Player*> playerList; //will this be created in Part 2??

    bool gameWon = false;
    while(gameWon==false){
        //execute 3 main phases sequentially
        reinforcementPhase();
        issueOrdersPhase();
        executeOrdersPhase();

        //check for winner
        for (Player player : playerList){
            if (player.getTerritories().size() == numberOfTerritories){
                cout << "The Winner Is: " << player.getName << endl;
                gameWon = true;
                break;
            }
        }
        //check for players to remove
        for (int i = 0; i < playerList.size(); i++){
            if (playerList[i].getTerritories().size() == 0){
                cout << playerList[i].getName << " has been eliminated." << endl;
                playerList.erase(i);
            }
        }

    }

    //FINSIH THIS METHOD WITH LOGGING, OUTPUT MESSSAGE, ETC
}

void GameEngine::reinforcementPhase(){
    cout << "Beginning Reinforcement Phase"<<endl;
    vector<Player*> playerList; 

    for (Player player : playerList){
        //minimum added is 3 or minimum required in pool is 3??
        if (player.getTerritories().size() < 12 && player.getTerritories.size() > 0){
            player.setReinforcementPool(player.getReinforcementPool()+3);
            cout << player.getName << " has " << player.getTerritories().size() << " territories" << endl;
            cout << "3 armies added to reinforcement pool" << endl;
        } 
        else {
            //add # of territories/3 rounded down to nearest int
            player.setReinforcementPool(player.getReinforcementPool()+player.getTerritories().size()/3);
            cout << player.getName << " has " << player.getTerritories.size() << " territories" << endl;
            cout << player.getTerritories().size()/3 << " armies were added to their reinforcement pool" << endl;
        }

        //add continent control bonus if applicable
        // -- **logic for ownership of continent*
        /*
        for (Player player : Playerlist)       {
            for(int j=0; j < continents.size(); j++){
                for(Territory territory: territories){
                    if (isTerritoryOwnedByPlayer(player, territory)){
                        player.setReinforcementPool(player.getReinforcementPool + continent.getControlBonus()); // continent not a class but this is the logic
                    }
                }

            }
        } 
        */
    }
    cout << "Emd of Reinforcement Phase" << endl;
}

void GameEngine::issueOrdersPhase(){
    vector<Player*> playerList;
    bool readyToExecute = false;
    int playersReady = 0;

    cout << "Beginning issue orders phase.";

    //each player adds an order until all players ready
    while(!readyToExecute){

        for (int i=0; i < playerList.size(); i++){
            cout << "Player "<< i <<"\'s turn" <<endl;
            char decision;

            //Check if they would like to issue order or not
            cout << "Would you like to issue an order? [y/n]"
            cin >> decision;

            //if they choose yes, send them to issueOrder dialogue
            if (decision == 'y'){
                playerList[i]->issueOrder();
            }
            else {
                playersReady+=1; //if not, increment ready
            }
        }
        //if all players decide not to issue order, set readyToExecute to true to break loop
        if(playersReady == playersList.size()){
                readyToExecute = true;
            }
    }

    cout << End of issue orders phase" < <endl;
}

void GameEngine::executeOrdersPhase(){
    vector<Player*> playerList;

    // execute orders one player at a time until all orders have been executed
    // need to determine which player(s) have the most # of orders, skip the indices of those who have less
    for (int i=0; i < orders.size(); i++){
        for (int j=0; j<playerList.size(); j++){
            playerList[j]->getOrders[i]Order1->execute();
        }

    }



}