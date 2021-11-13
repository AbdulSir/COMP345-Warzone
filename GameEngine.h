//
//  GameEngine.h
//  COMP 345 - Assignment 1 - Team DN02
//  Warzone Game Engine: controls the flow of the game using the user's keyboard inputs as commands
//
#include "Map.h"
#include "Player.h"
#include <string>
#include "CommandProcessing.h"
#include "LoggingObserver.h"
using namespace std;

#pragma once
class GameEngine {

public:

    std::string state;
    std::string command;
    MapLoader* map_loader;
    vector <Player*> players;
    //Constructors
    GameEngine();
    GameEngine(const GameEngine& g);

    //Assignment operator
    GameEngine& operator =(const GameEngine& g);

    //Insertion stream operator
    friend std::ostream& operator<<(std::ostream& stream, const GameEngine& g);

    //Transitions in the startup phase
    void loadMap();
    void validateMap();
    void addPlayer();
    void gameStart();

    //Transitions in the play phase
    void issueOrder();
    void endIssueOrders();
    void execOrder();
    void endExecOrders();
    void win();

    //Transitions at the end of the game
    void play();
    void end();

    //States of the game
    void start();
    void mapLoaded();
    void mapValidated();
    void playersAdded();
    void assignReinforcement();
    void issueOrders();
    void executeOrders();

    void startupPhase();
    vector<int> player_owns_all_territories(Player* p1);

};

