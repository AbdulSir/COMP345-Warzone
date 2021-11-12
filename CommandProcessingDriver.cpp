//
//  CommandProccessingDriver.cpp
//  Warzone Command Processor
//

#include "CommandProcessing.h"
#include "GameEngine.h"
#include <iostream>
using namespace std;
//DRIVER FOR TESTING
int main() {
    
    string choice;
    
    do {
        cout << "Please enter one of the following:" << endl
        << "\t-console to enter commands in the console" << endl
        << "\t-file <file name> to read commands from a file" << endl;
        getline(cin, choice);
        
        if (choice == "-console") {
            
            //Reading commands from console
            CommandProcessor* cp = new CommandProcessor();
            cp->getCommand("start");
            cp->getCommand("mapLoaded");
            cp->getCommand("mapValidated");
            cp->getCommand("playersAdded");
            cp->getCommand("win");
            cout << *cp;
            
            delete cp;
            cp = NULL;
            
            break;
        }
        
        else if (choice.substr(0,6) == "-file "){
            string file = choice.substr(6);
            cout << endl;
            
            //Reading commands from file
            CommandProcessor* fcpa = new FileCommandProcessorAdapter(file);
            fcpa->getCommand("start");
            fcpa->getCommand("mapLoaded");
            fcpa->getCommand("mapValidated");
            fcpa->getCommand("playersAdded");
            fcpa->getCommand("playersAdded");
            fcpa->getCommand("win");
            cout << *fcpa;
            
            delete fcpa;
            fcpa = NULL;
            
            break;
        }
    } while (true);
    
    cout << "\n\nTESTING IF GAME ENGINE CAN USE COMMAND PROCESSOR" << endl;
    GameEngine* g = new GameEngine();
    
    do {
        cout << "Please enter one of the following:" << endl
        << "\t-console to enter commands in the console" << endl
        << "\t-file <file name> to read commands from a file" << endl;
        getline(cin, choice);
        
        if (choice == "-console") {
            
            //Reading commands from console
            g->cp = new CommandProcessor();
            g->cp->getCommand("start");
            g->cp->getCommand("mapLoaded");
            g->cp->getCommand("mapValidated");
            g->cp->getCommand("playersAdded");
            g->cp->getCommand("win");
            cout << *(g->cp);
            
            delete g->cp;
            g->cp = NULL;
            
            break;
        }
        
        else if (choice.substr(0,6) == "-file "){
            string file = choice.substr(6);
            cout << endl;
            
            //Reading commands from file
            g->cp = new FileCommandProcessorAdapter(file);;
            g->cp->getCommand("start");
            g->cp->getCommand("mapLoaded");
            g->cp->getCommand("mapValidated");
            g->cp->getCommand("playersAdded");
            g->cp->getCommand("playersAdded");
            g->cp->getCommand("win");
            cout << *(g->cp);
            
            delete g->cp;
            g->cp = NULL;
            
            break;
        }
    } while (true);
    
    delete g;
    g = NULL;
    
}
