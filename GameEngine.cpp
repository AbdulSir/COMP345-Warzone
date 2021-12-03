//
//  GameEngine.cpp
//  COMP 345 - Assignment 1 - Team DN02
//  Warzone Game Engine: controls the flow of the game using the user's keyboard inputs as commands
//
#include "GameEngine.h"
#include "Player.h"
#include "PlayerStrategies.h"
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;


class Player;

//Constructor
GameEngine::GameEngine() : state("start"), command("") {
    string choice, command;
    do {
        cout << "Please enter one of the following:" << endl
        << "\t-console to enter commands in the console" << endl
        << "\t-file <file name> to read commands from a file" << endl;
        getline(cin, choice);
        
        if (choice == "-console") {
            //Reading commands from console
            cp = new CommandProcessor();
            command = cp->getCommand(state);
            if (command.find("tournament") != command.npos) {
                tournamentMode();
            }
            else if (command != "") {
                startupPhase();
            }
            break;
        }
        else if (choice.substr(0,6) == "-file "){
            string file = choice.substr(6);
            //Reading commands from file
            ofstream output;
            output.open("tournamentOutput.txt", ofstream::out | ofstream::trunc);
            output.close();
            cp = new FileCommandProcessorAdapter(file);
            do {
                command = cp->getCommand(state);
                if (command.find("tournament") != command.npos) {
                    tournamentMode();
                }
                else if (command.find("load") != command.npos ){
                    map_loader = new MapLoader(command.substr(8));
                    map_obj = map_loader->map_object;
                    state = "map loaded";
                    Notify(this);
                    startupPhase();
                }
            } while (command != "");
            break;
        }
    } while (true);
    
    //Start state of game
    //    string s;
    //    while (true) {
    //        s = cp->getCommand("start");
    //        if (s.find("tournament") != s.npos) {
    //            tournamentMode();
    //            break;
    //        }
    //        else if (s != "") {
    //            map_loader = new MapLoader(s.substr(8));
    //            map_obj = map_loader->map_object;
    //            state = "map loaded";
    //            Notify(this);
    //            startupPhase();
    //            break;
    //        }
    //        else {
    //            cout << "Invalid command for " << state << " state" << endl;
    //            continue;
    //        }
    //    }
}

//Copy constructor
GameEngine::GameEngine(const GameEngine& g) {
    state = g.state;
    command = g.command;
}

//Destructor
GameEngine::~GameEngine() {
    delete cp;
    delete map_loader;
    cp = NULL;
    map_loader = NULL;
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
    map_loader = new MapLoader();
    //Code for loading map
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
        cout << "Player " << i+1 << ": Please choose your strategy [Human, Aggressive, Benevolent, Neutral, Cheater]" << endl;
        string ps;
        cin >> ps;
        switch (ps.at(0)) {
            case 'A': {
                Player* aggressivePlayer = new Player("Aggressive");
                aggressivePlayer->ps = new Aggressive(aggressivePlayer);
                players.emplace(players.begin(), aggressivePlayer);
                break;
            }
            case 'B': {
                Player* benevolentPlayer = new Player("Benevolent");
                benevolentPlayer->ps = new Benevolent(benevolentPlayer);
                players.emplace(players.begin(), benevolentPlayer);
                break;
            }
            case 'N': {
                Player* neutralPlayer = new Player("Neutral");
                neutralPlayer->ps = new Neutral(neutralPlayer);
                players.emplace(players.begin(), neutralPlayer);
                break;
            }
            case 'H': {
                Player* humanPlayer = new Player("Human");
                humanPlayer->ps = new Human(humanPlayer);
                players.emplace(players.begin(), humanPlayer);
                break;
            }
            default: {
                Player* cheaterPlayer = new Player("Cheater");
                cheaterPlayer->ps = new Cheater(cheaterPlayer);
                players.emplace(players.begin(), cheaterPlayer);
            }
        }
        players_obj = players;
    }
    state = "players added";
    Notify(this);
}

void GameEngine::gameStart() {
    std::cout << "Assigning countries...\n" <<endl;
    vector <Territory*> territories_instance = map_loader->map_object->territories;
    int territory_size = territories_instance.size();
    int numCperP = 1;
    int count = 0;
    int randNum;
    while (territory_size != 0)
    {
        randNum = random(players.size()-1);
        if (players[randNum]->getTerritories().size() != numCperP && count != players.size()) {
            //players[randNum]->addTerritory(territories_instance[territory_size - 1]);
            territories_instance[territory_size - 1]->setOwner(players[randNum]);
            count++;
            territory_size--;
        }
        else if (count == players.size()) {
            count = 0;
            numCperP++;
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
    
    for (int i=0; i<50; i++) {
        if (gameWon==false){
            
            //execute 3 main phases sequentially
            reinforcementPhase();
            issueOrdersPhase();
            executeOrdersPhase();
            
            //check for players to remove
            for (int i = 0; i < players.size(); i++){
                
                if (players[i]->getTerritories().size() == 0){
                    cout << players[i]->getName() << " has been eliminated." << endl;
                    players.erase(find(players.begin(), players.end(), players[i]));
                }
            }
            
            //check if there is a winner
            if (players.size() == 1){
                cout << "The winner is " << players[0]->getName();
                gameWon = true;
                break;
            } else if (gameWon == false && i == 49) {
                cout << "THE GAME ENDS IN A DRAW" << endl;
            }
        }
    }
}

void GameEngine::reinforcementSetup(){
    map_loader = new MapLoader();
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
    
}

void GameEngine::reinforcementPhase(){
    cout << "\nBeginning Reinforcement Phase"<<endl;
    
    for (auto player : players){
        //minimum added is 3 or minimum required in pool is 3??
        if (player->getTerritories().size() < 12 && player->getTerritories().size() > 0){
            player->setReinforcementPool(player->getReinforcementPool()+3);
            cout << player->getName() << " has " << player->getTerritories().size() << " territories" << endl;
            cout << "3 armies added to reinforcement pool" << endl;
        }
        else {
            //add # of territories/3 rounded down to nearest int
            player->setReinforcementPool(player->getReinforcementPool()+player->getTerritories().size()/3);
            cout << player->getName() << " has " << player->getTerritories().size() << " territories" << endl;
            cout << player->getTerritories().size()/3 << " armies were added to their reinforcement pool" << endl;
        }
        
        //Apply Continent bonus to each player where applicable
        vector<int> playerContinents =  player_owns_all_territories(player);
        
        //if player owns any continents, add bonus(es)
        if (playerContinents.size() > 0) {
            for (int i = 0; i < playerContinents.size(); i++){
                vector<Territory*> player_territories = player->getTerritories();
                for (int j=0; j<player_territories.size(); j++){
                    if (player_territories[j]->continent_ref == playerContinents[i]){
                        player->setReinforcementPool(player->getReinforcementPool() + player_territories[j]->army_bonus);
                        break;
                    }
                    
                }
            }
        }
        
    }
    cout << "End of Reinforcement Phase" << endl;
}

void GameEngine::issueOrdersPhase(){
    
    cout << "\nBeginning issue orders phase.";
    
    //each player adds their orders until all players are done
    for (int i=0; i < players.size(); i++){
        cout << "Player "<< i <<"\'s turn" <<endl;
        //use a while loop?
        players[i]->ps->issueOrder();
    }
    cout << "End of issue orders phase\n" << endl;
}

void GameEngine::executeOrdersPhase(){
    // execute orders one player at a time until all orders have been executed
    // need to determine which player(s) have the most # of orders, skip the indices of those who have less
    
    //loop through players and execute all their orders
    for (auto player: players){
        for (auto order: player->getOrders()->orderList) {
            order->execute();
            cout<<endl<<*order<<endl;
        }
        player->getOrders()->orderList.clear();
    }
}
void GameEngine::startupPhase()
{
    
    while (state != "end") {
        
        std::cout << "--NEW GAME OF WARZONE--\n";
        
        //Start state
        if (map_loader->text_contents != "") {
            state = "map loaded";
        }
        else {
            cout << "The map could not be loaded" << endl;
            goto endGame;
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
        
        mainGameLoop();
        state = "win";
        if (players.size() == 1) {
            cout << "Winner: " << players[0]->getName() << endl;
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
        else if (command == "end")
            end();
        else {
        endGame:
            cout << "NO GAME" << endl;
            state = "end";
        }
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

void GameEngine::tournamentMode() {
    ofstream output("tournamentOutput.txt",fstream::in | fstream::out | fstream::app);
    output << "\nTournament mode:\nM: ";
    for (auto map : cp->mapFiles)
        output << map << ", ";
    output << "\nP: ";
    for (auto player : cp->playersStrat)
        output << player << ", ";
    output << "\nG: " << cp->numGames << "\nD: " << cp->numMaxTurns << endl << "\nResults:\n\t";
    for (int i=1; i <= cp->numGames; i++) {
        output << "\tGame " << i << "\t\t";
    }
    
    cout << "--NEW TOURNAMENT OF WARZONE--\n" << endl;
    
    for (auto currentMap : cp->mapFiles) {
        
        //Start state
        while (state == "start") {
            cout << "\nCurrent State: " << state << endl;
            cout << "Loading " << currentMap << "..."<< endl;
            map_loader = new MapLoader(currentMap);
            map_obj = map_loader->map_object;
            if (map_loader->text_contents != "") {
                state = "map loaded";
            }
            else
                goto restart;
        }
        
        //Map loaded state
        while(state == "map loaded") {
            cout << "\nCurrent State: " << state << endl;
            if (map_loader->map_object->validate())
                state = "map validated";
            else
                goto restart;
        }
        
        output << "\n" << currentMap;
        
        for (int currentGame=1; currentGame<=cp->numGames; currentGame++) {
            //Map validated state
            while(state == "map validated") {
                cout << "\nCurrent State: " << state << endl;
                for (auto player : cp->playersStrat) {
                    switch (player.at(0)) {
                        case 'A': {
                            Player* aggressivePlayer = new Player("Aggressive");
                            aggressivePlayer->ps = new Aggressive(aggressivePlayer);
                            if (random(100)%2 == 0) {
                                players.push_back(aggressivePlayer);
                            }
                            else {
                                players.emplace(players.begin(), aggressivePlayer);
                            }
                            break;
                        }
                        case 'B': {
                            Player* benevolentPlayer = new Player("Benevolent");
                            benevolentPlayer->ps = new Benevolent(benevolentPlayer);
                            if (random(100)%2 == 0)
                                players.push_back(benevolentPlayer);
                            else
                                players.emplace(players.begin(), benevolentPlayer);
                            break;
                        }
                        case 'N': {
                            Player* neutralPlayer = new Player("Neutral");
                            neutralPlayer->ps = new Neutral(neutralPlayer);
                            if (random(100)%2 == 0)
                                players.push_back(neutralPlayer);
                            else
                                players.emplace(players.begin(), neutralPlayer);
                            break;
                        }
                        case 'H': {
                            Player* humanPlayer = new Player("Human");
                            humanPlayer->ps = new Human(humanPlayer);
                            if (random(100)%2 == 0)
                                players.push_back(humanPlayer);
                            else
                                players.emplace(players.begin(), humanPlayer);
                            break;
                        }
                        default: {
                            Player* cheaterPlayer = new Player("Cheater");
                            cheaterPlayer->ps = new Cheater(cheaterPlayer);
                            if (random(100)%2 == 0)
                                players.push_back(cheaterPlayer);
                            else
                                players.emplace(players.begin(), cheaterPlayer);
                        }
                    }
                    players_obj = players;
                    
                }
                state = "players added";
                cout << "The following players have been added: " << endl;
                for (auto p : players) {
                    cout << p->getName() << endl;
                }
            }
            
            //Players added state
            while(state == "players added") {
                cout << "\nCurrent State: " << state << endl;
                gameStart();
            }
            
            //Main game loop
            cout << "Game " << currentGame << ":" << endl;
            mainGameLoop();
            if (players.size() == 1) {
                output << "\t" << players[0]->getName() << "\t";
            } else {
                output << "\tDRAW: No winner\t";
            }
            for (auto p : players)
                p->getTerritories().clear();
            players.erase(players.begin(),players.end());
            state = "map validated";
        }
        
    restart:
        state = "start";
    }
    cp->mapFiles.clear();
    cp->playersStrat.clear();
    output << "\n\n";
    output.close();
}

default_random_engine dre (chrono::steady_clock::now().time_since_epoch().count());
int GameEngine::random (int lim) {
    uniform_int_distribution<int> uid {0,lim};
    return uid(dre);
}
