//
//  GameEngineDriver.cpp
//  COMP 345 - Assignment 1 - Team DN02
//  Warzone Game Engine: controls the flow of the game using the user's keyboard inputs as commands
//

#include "GameEngine.h"

#include <iostream>
using namespace std;

#include <string>

void GameEngineDriverTest() {
    
    GameEngine g;
    
    while (g.state != "end") {
        
        std::cout << "--NEW GAME OF WARZONE--\n";
        
        //Start state
        std::cout << g;
        while (g.state != "map loaded") {
            std::cout << "Type \"loadMap\" to load a map\n";
            std::cin >> g.command;
            g.start();
        }
        
        //Map loaded state
        std::cout << g;
        while(g.state != "map validated") {
            std::cout << "Choose one of the following:\n\t1. loadMap\n\t2. validateMap" << endl;
            std::cin >> g.command;
            g.mapLoaded();
        }
        
        //Map validated state
        std::cout << g;
        while(g.state != "players added") {
            std::cout << "Type \"addPlayer\" to add a player" << endl;
            std::cin >> g.command;
            g.mapValidated();
        }
        
        //Players added state
        std::cout << g;
        while(g.state != "assign reinforcement") {
            std::cout << "Choose one of the following:\n\t1. addPlayer\n\t2. assignCountries" << endl;
            std::cin >> g.command;
            g.playersAdded();
        }
        
        
        while (g.state != "win") {
            
            //Assign reinforcement state
            std::cout << g;
            while(g.state !="issue orders") {
                std::cout << "Type \"issueOrder\" to issue an order" << endl;
                std::cin >> g.command;
                g.assignReinforcement();
            }
            
            //Issue orders state
            std::cout << g;
            while(g.state !="execute orders") {
                std::cout << "Choose one of the following:\n\t1. issueOrder\n\t2. endIssueOrders" << endl;
                std::cin >> g.command;
                g.issueOrders();
            }
            
            //Execute orders state
            std::cout << g;
            while(g.state !="assign reinforcement" && g.state != "win") {
                std::cout << "Choose one of the following:\n\t1. execOrder\n\t2. endExecOrders\n\t3. win" << endl;
                std::cin >> g.command;
                g.executeOrders();
            }
            
        }
        
        //Win state: "play" command triggers the start of a new game, "end" command ends the program
        std::cout << g;
        std::cout << "Choose one of the following:\n\t1. play\n\t2. end" << endl;
        std::cin >> g.command;
        
        while (g.command != "play" && g.command != "end") {
            std::cout << "ERROR: Invalid command for " << g.state << " state" << endl;
            std::cout << "Choose one of the following:\n\t1. play\n\t2. end" << endl;
            std::cin >> g.command;
        }
        
        if (g.command == "play")
            g.play();
        else
            g.end();
    }
    
};

int main() {
    
    GameEngineDriverTest();
    
    return(0);
};
