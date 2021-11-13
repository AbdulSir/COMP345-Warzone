//
//  GameEngine.h
//  COMP 345 - Assignment 1 - Team DN02
//  Warzone Game Engine: controls the flow of the game using the user's keyboard inputs as commands
//

#pragma once
#include "CommandProcessing.h"
#include <string>
#include "LoggingObserver.h"
using namespace std;

class ILoggable;
class Subject;
class GameEngine : public ILoggable, public Subject {
    
public:
    
    std::string state;
    std::string command;
    CommandProcessor* cp;
    
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
    void assignCountries();
    
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
    
    //overrite ILoggable stringToLog method
    virtual std::string stringToLog();
};

