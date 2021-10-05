//
//  GameEngineDriver.cpp
//  Warzone Game Engine
//
//  Created by Vanessa Razon on 2021-09-24.
//  Copyright © 2021 Vanessa Razon. All rights reserved.
//

#include "GameEngine.h"

#include <iostream>
using namespace std;

#include <string>

void GameEngineDriverTest() {

    GameEngine g;
    
    while (g.state != "end") {
        
        std::cout << "--NEW GAME OF WARZONE--\n";

        std::cout << g;
        while (g.state != "map loaded") {
         std::cout << "Type \"loadMap\" to load a map\n";
         std::cin >> g.command;
         g.start();
    }
        
        std::cout << g;
        while(g.state != "map validated") {
            std::cout << "Choose one of the following:\n\t1. loadMap\n\t2. validateMap" << endl;
            std::cin >> g.command;
            g.mapLoaded();
        }
        
        
        std::cout << g;
        while(g.state != "players added") {
            std::cout << "Type \"addPlayer\" to add a player" << endl;
            std::cin >> g.command;
            g.mapValidated();
        }
        
        std::cout << g;
        while(g.state != "assign reinforcement") {
            std::cout << "Choose one of the following:\n\t1. addPlayer\n\t2. assignCountries" << endl;
            std::cin >> g.command;
            g.playersAdded();
        }
        
        
        // LOOP
        
        while (g.state != "win") {
            
            std::cout << g;
            while(g.state !="issue orders") {
            std::cout << "Type \"issueOrder\" to issue an order" << endl;
            std::cin >> g.command;
                g.assignReinforcement();
            }
            
            std::cout << g;
            while(g.state != "execute orders") {
                        std::cout << "Choose one of the following:\n\t1. issueOrder\n\t2. endIssueOrders" << endl;
                        std::cin >> g.command;
                        g.issueOrder();
                    }
            
            std::cout << g;
            while(g.state != "endIssueOrders") {
                if (g.command == "issueOrder") {
                    g.issueOrder();
                    std::cout << "\nCurrent state: " << g.state << endl;
                }
                else if(g.command == "endIssueOrders") {
                    g.endIssueOrders();
                    break;
                }
                else
                    std::cout << "ERROR: Invalid command for " << g.state << endl;
                std::cout << "Choose one of the following:\n\t1. issueOrder\n\t2. endIssueOrders" << endl;
                std::cin >> g.command;
            }
            
            std::cout << g;
            std::cout << "Choose one of the following:\n\t1. execOrder\n\t2. endExecOrders\n\t3. win" << endl;
            std::cin >> g.command;
            
            while(cin) {
                
                if (g.command == "execOrder") {
                    g.execOrder();
                    std::cout << "\nCurrent state: " << g.state << endl;
                }
                else if (g.command == "endExecOrders") {
                    g.endExecOrders();
                    break;
                }
                else if (g.command == "win") {
                    g.win();
                    break;
                }
                else
                    std::cout << "ERROR: Invalid command for " << g.state << endl;
                std::cout << "Choose one of the following:\n\t1. execOrder\n\t2. endExecOrders\n\t3. win" << endl;
                std::cin >> g.command;
            }
            
        } //END OF LOOP
        
        std::cout << g;
        std::cout << "Choose one of the following:\n\t1. play\n\t2. end" << endl;
        std::cin >> g.command;
        
        while (g.command != "play" && g.command != "end") {
                std::cout << "ERROR: Invalid command for " << g.state << endl;
                std::cout << "Choose one of the following:\n\t1. play\n\t2. end" << endl;
                std::cin >> g.command;
        }
        
        if (g.command == "play")  {
            g.play();
        }
        else
            g.end();
    }
    
};

int main() {
    
    GameEngineDriverTest();
    
    return(0);
};
