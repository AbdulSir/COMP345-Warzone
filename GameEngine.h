//
//  GameEngine.h
//  Warzone Game Engine
//
//  Created by Vanessa Razon on 2021-09-24.
//  Copyright © 2021 Vanessa Razon. All rights reserved.
//

#include <string>
using namespace std;

#pragma once
class GameEngine {
    
public:
    
    std::string state;
    std::string command;
    
    //Constructors
    GameEngine();
    GameEngine(const GameEngine& g);
    
    //Assignment operator
    GameEngine& operator =(const GameEngine& g);
    
    //Insertion stream operator
    friend std::ostream& operator<<(std::ostream& stream, const GameEngine& g);
    
    
    //Transitions in the play phase
    void issueOrder();
    void endIssueOrders();
    void execOrder();
    void endExecOrders();
    void win();
    
    //Transitions at the end of the game
    void play();
    void end();
    
    //States to add?
    void start();
    void mapLoaded();
    void mapValidated();
    void playersAdded();
    void ordersLoop();
    void assignReinforcement();
    void issueOrders();
    void executeOrders();
    
    //Transitions in the startup phase
private:
    void loadMap();
    void validateMap();
    void addPlayer();
    void assignCountries();

    
    
    
};

