//
//  CommandProcessing.cpp
//  Warzone Command Processor
//

#include "CommandProcessing.h"
#include "GameEngine.h"
#include <iostream>
using namespace std;
#include <string>
using namespace std;

//METHODS IN COMMAND

//Command default constructor
Command::Command(): command(""), effect("") {
}

//Copy constructor
Command::Command(const Command& c) {
    this->command = c.command;
    this->effect = c.effect;
}

//Constructor with string parameter
Command::Command(string c) {
    command = c;
}

//Assignment operator
Command& Command::operator= (const Command& c) {
    this->command = c.command;
    this->effect = c.effect;
    return *this;
}

//Stream insertion operator
ostream& operator<<(ostream& out, const Command& c) {
    out << "COMMAND: " << c.command << "\nEFFECT: " << c.effect << endl;
    return out;
}

//Saves effect of command
void Command::saveEffect(string c) {
    if (c.find("loadmap") != string::npos) {
        string mapName = c.substr(8);
        //map is valid
        effect = mapName + " has been loaded";
        //map is invaid
        effect = mapName + "is an invalid map";
    }
    else if (c.find("validatemap") != string::npos) {
        effect =  "The map has been validated";
    }
    else if (c.find("addplayer") != string::npos) {
        string playerName = c.substr(10);
        effect = "Player " + playerName + " has been added";
    }
    else if (c == "gamestart") {
        effect = "Players have been added and the game will now begin";
    }
    else if (c == "replay") {
        effect = "Startup of a new game";
    }
    else if (c == "quit") {
        effect = "End of program";
    }
}


//METHODS IN CommandProcessor

//CommandProcessor constructor
CommandProcessor::CommandProcessor() {
    this->lc = {};
}

//CommandProcessor copy constructor
CommandProcessor::CommandProcessor(CommandProcessor& cp) {
    this->lc = cp.lc;
}

//CommandProcessor destructor
CommandProcessor::~CommandProcessor() {
    for(auto c: lc) {
        delete c;
        c = NULL;
    }
}

//Assignment operator
CommandProcessor& CommandProcessor::operator= (const CommandProcessor& cp) {
    this->lc = cp.lc;
    return *this;
}

//Stream insertion operator
ostream& operator<<(ostream& out, const CommandProcessor& cp) {
    out << "The CommandProcessor has the following commands:" <<endl;
    for (auto c: cp.lc) {
        out << *c << endl;
    }
    return out;
}


//Method provided to other classes (GameEngine, Player, etc) to get commands
void CommandProcessor::getCommand(string gameState) {
    string commandStr = readCommand();
    if (validate(commandStr, gameState)) {
        cout << commandStr << " is a valid command for the " << gameState << " state\n" <<endl;
        Command* c = new Command(commandStr);
        c->saveEffect(commandStr);
        saveCommand(c);
    }
    else {
        cout << commandStr << " is not a valid command for the " << gameState << " state\n" << endl;
        Command* c = new Command(commandStr);
        c->effect = "No effect (Invalid command for " + gameState + " state)\n";
        saveCommand(c);
    }
}

//Validates if command is valid in current game state
bool CommandProcessor::validate(string c, string gameState) {
    if (c.substr(0,9) == "loadmap " && (gameState == "start" || gameState == "mapLoaded")) {
//        if (c.substr(c.length()-4) == ".txt")
            return true;
//        else
//           return false;
    }
    else if (c == "validatemap" && gameState == "mapLoaded") {
        return true;
    }
    else if (c.substr(0,10) == "addplayer " && (gameState == "mapValidated" || gameState == "playerAdded")) {
        return true;
    }
    else if (c == "gamestart" && gameState == "playersAdded") {
        return true;
    }
    else if (c == "replay" && gameState=="win") {
        return true;
    }
    else if (c == "quit" && gameState=="win") {
        return true;
    }
    else
        return false;
}

//Gets commands from the console as a string
string CommandProcessor::readCommand() {
    string commandStr;
    cout << "Please enter a command" << endl;
    getline(cin,commandStr);
    return commandStr;
}

//Saves command in list of commands
void CommandProcessor::saveCommand(Command* c) {
    lc.push_back(c);
}


//METHODS IN FileCommandAdaptor
void FileCommandProcessorAdapter::readFile(string file) {
    flr.open(file);
}



int main() {
    
    CommandProcessor* cp = new CommandProcessor();
    cp->getCommand("start");
    cp->getCommand("mapLoaded");
    cp->getCommand("mapValidated");
    cp->getCommand("playersAdded");
    cp->getCommand("win");
    cout << *cp;

    delete cp;
    
//    cout << "Please enter one of the following:" << endl
//    << "\t-console to enter commands in the console" << endl
//    << "\t-file <file name> to read commands from a file";
    
    
}

