
#include "CommandProcessing.h"
#include "GameEngine.h"
#include "LoggingObserver.h"
#include "Orders.h"
#include <iostream>
#include <string>
#include <fstream>

int main() {
    
    // Command & CommandProcessing test cases:
    string choice;
    cout << "Please enter one of the following:" << endl
    << "\t-console to enter commands in the console" << endl
    << "\t-file <file name> to read commands from a file" << endl;
    getline(cin, choice);
    
    if (choice == "-console") {
        
        //Reading commands from console
        CommandProcessor* cp = new CommandProcessor();
        LogObserver *cpObserver = new LogObserver(cp);
        cp->getCommand("start");
        cp->getCommand("mapLoaded");
        cp->getCommand("mapValidated");
        cp->getCommand("playersAdded");
        cp->getCommand("win");
        cout << *cp;
        
        delete cpObserver;
        delete cp;
        cpObserver = NULL;
    }
    
    else if (choice.substr(0,6) == "-file "){
        string file = choice.substr(6);
        //Reading commands from file
        CommandProcessor* fcpa = new FileCommandProcessorAdapter(file);
        fcpa->getCommand("start");
        delete fcpa;
        fcpa = NULL;
    }
    
    GameEngine *g = new GameEngine();
    LogObserver *gameObserver = new LogObserver(g);
    
    while (g->state != "end") {
        
        std::cout << "--NEW GAME OF WARZONE--\n";
        
        //Start state
        std::cout << *g;
        while (g->state != "map loaded") {
            std::cout << "Type \"loadMap\" to load a map\n";
            std::cin >> g->command;
            g->start();
        }
        
        //Map loaded state
        std::cout << *g;
        while(g->state != "map validated") {
            std::cout << "Choose one of the following:\n\t1. loadMap\n\t2. validateMap" << endl;
            std::cin >> g->command;
            g->mapLoaded();
        }
        
        //Map validated state
        std::cout << *g;
        while(g->state != "players added") {
            std::cout << "Type \"addPlayer\" to add a player" << endl;
            std::cin >> g->command;
            g->mapValidated();
        }
        
        //Players added state
        std::cout << *g;
        while(g->state != "assign reinforcement") {
            std::cout << "Choose one of the following:\n\t1. addPlayer\n\t2. assignCountries" << endl;
            std::cin >> g->command;
            g->playersAdded();
        }
        
        
        while (g->state != "win") {
            
            //Assign reinforcement state
            std::cout << *g;
            while(g->state !="issue orders") {
                std::cout << "Type \"issueOrder\" to issue an order" << endl;
                std::cin >> g->command;
                g->assignReinforcement();
            }
            
            //Issue orders state
            std::cout << *g;
            while(g->state !="execute orders") {
                std::cout << "Choose one of the following:\n\t1. issueOrder\n\t2. endIssueOrders" << endl;
                std::cin >> g->command;
                g->issueOrders();
            }
            
            //Execute orders state
            std::cout << *g;
            while(g->state !="assign reinforcement" && g->state != "win") {
                std::cout << "Choose one of the following:\n\t1. execOrder\n\t2. endExecOrders\n\t3. win" << endl;
                std::cin >> g->command;
                g->executeOrders();
            }
            
        }
        
        //Win state: "play" command triggers the start of a new game, "end" command ends the program
        std::cout << *g;
        std::cout << "Choose one of the following:\n\t1. play\n\t2. end" << endl;
        std::cin >> g->command;
        
        while (g->command != "play" && g->command != "end") {
            std::cout << "ERROR: Invalid command for " << g->state << " state" << endl;
            std::cout << "Choose one of the following:\n\t1. play\n\t2. end" << endl;
            std::cin >> g->command;
        }
        
        if (g->command == "play")
            g->play();
        else
            g->end();
    }
    
    //Create orders
    Hand* h = new Hand;
    Territory* firstTerritory = new Territory("A", 0, 10);
    Territory* secondTerritory = new Territory("B", 0, 10);
    Territory* thirdTerritory = new Territory("C", 0, 10);

    vector <Territory*> v;
    v.push_back(firstTerritory);
    v.push_back(secondTerritory);
    // Player only owns A and B
    Player* player1 = new Player("testName", h, v);
    
    Deploy* deployOrder = new Deploy(player1, thirdTerritory, 3);
    
    h->addToHand(new Card("airlift"));
    Airlift* airliftOrder = dynamic_cast<Airlift*>(h->discardFromHand().play());
    airliftOrder->setOrderIssuer(player1);
    airliftOrder->setFrom(firstTerritory);
    airliftOrder->setTarget(secondTerritory);
    airliftOrder->setNumberOfUnits(5);
    
    h->addToHand(new Card("bomb"));
    Bomb* bombOrder = dynamic_cast<Bomb*>(h->discardFromHand().play());
    bombOrder->setOrderIssuer(player1);
    bombOrder->setTarget(thirdTerritory);
    
    
    h->addToHand(new Card("blockade"));
    Blockade* blockadeOrder = dynamic_cast<Blockade*>(h->discardFromHand().play());
    blockadeOrder->setOrderIssuer(player1);
    blockadeOrder->setTarget(firstTerritory);
    
    
    //Create LogObservers
    LogObserver *deployOrderObserver = new LogObserver(deployOrder);
    LogObserver *airliftOrderObserver = new LogObserver(airliftOrder);
    LogObserver *bombOrderObserver = new LogObserver(bombOrder);
    LogObserver *blockadeOrderObserver = new LogObserver(blockadeOrder);
    

    OrderList* orderList = new OrderList();
    LogObserver *orderListObserver = new LogObserver(orderList);
    
    //Add orders to orderList
    orderList->addOrder(deployOrder);
    orderList->addOrder(airliftOrder);
    orderList->addOrder(bombOrder);
    orderList->addOrder(blockadeOrder);
    
    //Display orderList
    cout << *orderList << endl;
    
    //Execute orders
    cout << *deployOrder << endl;
    deployOrder->execute();
    cout << endl;
    
    cout << *airliftOrder << endl;
    airliftOrder->execute();
    cout << endl;
    
    cout << *bombOrder << endl;
    bombOrder->execute();
    cout << endl;
    
    cout << *blockadeOrder << endl;
    blockadeOrder->execute();
    cout << endl;



    //delete all pointers
    delete gameObserver;
    delete deployOrderObserver;
    delete airliftOrderObserver;
    delete bombOrderObserver;
    delete blockadeOrderObserver;
    delete orderListObserver;
    delete g;
    
}
