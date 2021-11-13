//
//  GameEngine.cpp
//  COMP 345 - Assignment 1 - Team DN02
//  Warzone Game Engine: controls the flow of the game using the user's keyboard inputs as commands
//
#include "GameEngine.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>
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
    cout << "Testing" << endl;
    map_loader = new MapLoader();
    // Code for loading map
    state = "map loaded";
    Notify(this);
}

void GameEngine::validateMap() {
    std::cout << "Validating map..." << endl;
    if(map_loader->map_object->validate())
    {
        cout << "\nThe Map is a valid map" << endl;
        state = "map validated";
    }
    else
        cout << "\nThe Map is NOT a valid map" << endl;

    // Code for validating map;
    // Code for validating map
    state = "map validated";
    Notify(this);
}

void GameEngine::addPlayer() {
    int num_of_players = 0;
    std::cout << "Adding player..." << endl;
    cout << "Please enter the number of players (2-6): " << endl;;
    cin >> num_of_players;
    while( num_of_players < 2 || num_of_players > 6)
    {
        cout << "Invalid number. Please enter a number between 2 and 6" << endl;
        cin >> num_of_players;
    }

    for (int i=0; i < num_of_players; i++)
    {
        string player_name = "Player " + to_string(i+1);
        players.push_back(new Player(player_name));
    }
    state = "players added";
    Notify(this);
}

void GameEngine::gameStart() {
    std::cout << "Assigning countries...\n" <<endl;
    vector <Territory*> territories_instance = map_loader->map_object->territories;
    int territory_size = territories_instance.size();
    while (territory_size != 0)
    {
        for (int i=0; i<players.size(); i++)
        {
            if (territory_size >= 1)
            {
                players[i]->addTerritory(territories_instance[territory_size - 1]);
                territory_size--;
            }
        }
    }
    for (int i=0; i<players.size(); i++)
    {
        vector <Territory*> territories_instance_1 = players[i]->getTerritories();
        cout << players[i]->getName() << endl;
        for (int j=0; j< territories_instance_1.size(); j++)
        {
            cout << territories_instance_1[j]->getName() << endl;
        }
        cout << endl;
    }
    Deck* deck = new Deck(10);
    Card* card;
    Hand* hand;
    for (int i=0; i<players.size(); i++)
    {
        int j=0;
        while (j<2)
        {
            card = deck->draw();
            hand = players[i]->getHand();
            hand->addToHand(card);
            j++;
        }
    }

    /*
    vector<int> valid_continents = player_owns_all_territories(players[0]);
    cout << "Continents Size " << valid_continents.size() << endl;
    for (int i=0; i<valid_continents.size(); i++)
    {
        cout << "test " << valid_continents[i] << endl;
    }
    */

    // Code for assigning countries
    state = "assign reinforcement";
    Notify(this);
}

void GameEngine::issueOrder() {
    std::cout << "Issuing orders... " << endl;
    // Code for issuing orders
    state = "issue orders";
    Notify(this);
}

void GameEngine::endIssueOrders() {
    std::cout << "Ending issued orders... " <<endl;
    // Code for ending issued orders
    state = "execute orders";
    Notify(this);
}

void GameEngine::execOrder() {
    std::cout << "Executing orders... " <<endl;
    // Code for executing orders
    state = "execute orders";
    Notify(this);
}

void GameEngine::endExecOrders() {
    std::cout << "Ending executed orders... " <<endl;
    // Code for ending orders
    state = "assign reinforcement";
    Notify(this);
}

void GameEngine:: win() {
    std::cout << "END OF GAME: Congratulations to the winner!" << endl;
    // Code relevant to the win state
    state = "win";
    Notify(this);
}

void GameEngine::play() {
    std::cout << "Starting a new game...\n" <<endl;
    state = "start";
    Notify(this);
}

void GameEngine::end() {
    std::cout << "--END OF PROGRAM: Thank you for playing Warzone--" <<endl;
    state = "end";
    Notify(this);
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
    else if (command == "gameStart")
        gameStart();
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
    bool gameWon = false;

    while(gameWon==false){

        //execute 3 main phases sequentially
        reinforcementPhase();
        issueOrdersPhase();
        executeOrdersPhase();

        //check for players to remove
        for (int i = 0; i < playerList.size(); i++){
            if (playerList[i].getTerritories().size() == 0){
                cout << playerList[i].getName << " has been eliminated." << endl;
                playerList.erase(i);
            }
        }
        //check if there is a winner
        if (playerList->size() == 1){
            cout << "The winner is " << playerList[0]->getName();
            break;
        }
    }

}

void GameEngine::reinforcementPhase(){
    cout << "Beginning Reinforcement Phase"<<endl;

    for (Player player : playerList){
        //minimum added is 3 or minimum required in pool is 3??
        if (player>getTerritories()>size() < 12 && player>getTerritories>size() > 0){
            player>setReinforcementPool(player>getReinforcementPool()+3);
            cout << player>getName << " has " << player>getTerritories()>size() << " territories" << endl;
            cout << "3 armies added to reinforcement pool" << endl;
        } 
        else {
            //add # of territories/3 rounded down to nearest int
            player.setReinforcementPool(player.getReinforcementPool()+player.getTerritories().size()/3);
            cout << player->getName << " has " << player->getTerritories.size() << " territories" << endl;
            cout << player->getTerritories()->size()/3 << " armies were added to their reinforcement pool" << endl;
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

    cout << "Beginning issue orders phase.";

        //each player adds their orders until all players are done
        for (int i=0; i < playerList->size(); i++){
            cout << "Player "<< i <<"\'s turn" <<endl;
            //use a while loop?
                playerList[i]->issueOrder();
        }
        cout << "End of issue orders phase" < <endl;
    }

void GameEngine::executeOrdersPhase(){
    // execute orders one player at a time until all orders have been executed
    // need to determine which player(s) have the most # of orders, skip the indices of those who have less

    //loop through players and execute all their orders
    for (int i= 0; i < playerList->size(); i++){
        OrderList orderList = playerList[i]->getOrders();

        for (int j = 0; j < orderList->size(); j++){
            orderList[j]->execute();
        }
     
    }

}
void GameEngine::startupPhase()
{

    while (state != "end") {

        std::cout << "--NEW GAME OF WARZONE--\n";

        //Start state
        while (state != "map loaded") {
            cout << "Current State: " << state << endl;
            cout << endl;
            std::cout << "Type \"loadMap\" to load a map\n";
            std::cin >> command;
            start();
        }

        //Map loaded state
        while(state != "map validated") {
            cout << "Current State: " << state << endl;
            std::cout << "Choose one of the following:\n\t1. loadMap\n\t2. validateMap" << endl;
            std::cin >> command;
            mapLoaded();
        }

        //Map validated state
        while(state != "players added") {
            cout << "Current State: " << state << endl;
            std::cout << "Type \"addPlayer\" to add a player" << endl;
            std::cin >> command;
            mapValidated();
        }

        //Players added state
        while(state != "assign reinforcement") {
            cout << "Current State: " << state << endl;
            std::cout << "Choose one of the following:\n\t1. addPlayer\n\t2. gameStart" << endl;
            std::cin >> command;
            playersAdded();
        }


        while (state != "win") {

            //Assign reinforcement state
            while(state !="issue orders") {
                cout << "Current State: " << state << endl;
                std::cout << "Type \"issueOrder\" to issue an order" << endl;
                std::cin >> command;
                assignReinforcement();
            }

            //Issue orders state
            while(state !="execute orders") {
                std::cout << "Choose one of the following:\n\t1. issueOrder\n\t2. endIssueOrders" << endl;
                std::cin >> command;
                issueOrders();
            }

            //Execute orders state
            while(state !="assign reinforcement" && state != "win") {
                std::cout << "Choose one of the following:\n\t1. execOrder\n\t2. endExecOrders\n\t3. win" << endl;
                std::cin >> command;
                executeOrders();
            }

        }

        //Win state: "play" command triggers the start of a new game, "end" command ends the program
        std::cout << "Choose one of the following:\n\t1. play\n\t2. end" << endl;
        std::cin >> command;

        while (command != "play" && command != "end") {
            std::cout << "ERROR: Invalid command for " << state << " state" << endl;
            std::cout << "Choose one of the following:\n\t1. play\n\t2. end" << endl;
            std::cin >> command;
        }

        if (command == "play")
            play();
        else
            end();
    }

}

vector<int> GameEngine::player_owns_all_territories(Player* p1)
{
    vector <Territory*> player_territories_instance = p1->getTerritories();
    int num_of_continents = map_loader->map_object->num_of_continents;

    for (int i=0; i< num_of_continents; i++)
    {
        bool vis[map_loader->map_object->continent_graph[i].size()];
        //set the array to false. i.e. no node has been visited yet
        memset(vis, false, sizeof(vis));
        int j=0;
        for (Territory* terr:map_loader->map_object->continent_graph[i])
        {
            for (int k=0; k<player_territories_instance.size(); k++)
            {
                if (terr->getName() == player_territories_instance[k]->getName())
                {
                    vis[j] = true;
                }
            }
            j++;
        }
        int total_unvisited = sizeof(vis);
        for (int z=0; z < sizeof(vis); z++)
        {
            if (vis[z])
                total_unvisited--;
        }
        if (total_unvisited==0)
            p1->continents_owned.push_back(i);
    }
    return p1->continents_owned;
}

//overrite ILoggable stringToLog method
string GameEngine::stringToLog() {
    cout<<"\nWriting Game Engine new state to gamelog.txt file ..."<<endl;
    std::ofstream myfile;
    myfile.open ("gamelog.txt", std::ios_base::app);
    myfile <<"Game Engine new state: ";
    myfile <<this->state<<"\n";
    myfile <<"-------------------------------------\n";
    myfile.close();
    return this->state;
}
