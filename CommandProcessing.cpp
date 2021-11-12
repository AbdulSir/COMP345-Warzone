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
#include <fstream>

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
        effect = mapName + " has been loaded";
    }
    else if (c.find("validatemap") != string::npos) {
        effect =  "The map has been validated";
    }
    else if (c.find("addplayer") != string::npos) {
        string playerName = c.substr(10);
        effect = "Player " + playerName + " has been added to the game";
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


//METHODS IN COMMANDPROCESSOR

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
const CommandProcessor& CommandProcessor::operator= (const CommandProcessor& cp) {
    this->lc = cp.lc;
    return *this;
}

//Stream insertion operator
ostream& operator<<(ostream& out, const CommandProcessor& cp) {
    out << "\nThe List of Commands:\n" <<endl;
    for (auto c: cp.lc) {
        out << *c << endl;
    }
    return out;
}

//Method provided to other objects (like the GameEngine) to get commands
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
        c->effect = "No effect (Invalid command for " + gameState + " state)";
        saveCommand(c);
    }
}

//Validates if command is valid in current game state
bool CommandProcessor::validate(string c, string gameState) {
    if (c.substr(0,8) == "loadmap " && (gameState == "start" || gameState == "mapLoaded")) {
        if (c.substr(c.length()-4) == ".map" && c.rfind(" ") == 7 && c.find(" .map") == c.npos)
            return true;
        else
            return false;
    }
    else if (c == "validatemap" && gameState == "mapLoaded") {
        return true;
    }
    else if (c.substr(0,10) == "addplayer " && c.rfind(" ") == 9 && c.size() > 10 && (gameState == "mapValidated" || gameState == "playersAdded")) {
        return true;
    }
    else if (c == "gamestart" && gameState == "playersAdded") {
        return true;
    }
    else if ((c == "replay" || c == "quit") && gameState=="win") {
        return true;
    }
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


//METHODS IN FILECOMMANDPROCESSORADAPTER

//FileCommandProcessorAdapter constructor with file-to-be-read as parameter
FileCommandProcessorAdapter::FileCommandProcessorAdapter(string f): CommandProcessor(), fileName(f), flr(new FileLineReader()) {
}

//FileCommandProcessorAdapter copy constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileCommandProcessorAdapter& fcpa): CommandProcessor(fcpa), fileName(fcpa.fileName), flr(fcpa.flr) {
}

//FileCommandProcessorAdapter destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete flr;
    flr = NULL;
}

//Assignment operator
const FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator= (const FileCommandProcessorAdapter& fcpa) {
    this->fileName = fcpa.fileName;
    if (&fcpa != this) {
        delete flr;
    }
    return *this;
}

//Stream insertion operator
ostream& operator<<(ostream& out, const FileCommandProcessorAdapter& fcpa) {
    out << "Using FileCommandProcessorAdapter: " << endl;
    return out;
}

//Method that reads the command from a file (overrides readCommand of CommandProcessor)
string FileCommandProcessorAdapter::readCommand() {
    string command = flr->readLineFromFile(fileName);
    cout << "Command read from " << fileName <<  ": " << command << endl;
    return command;
}


//METHODS IN FILELINEREADER

//FileLineReader constructor
FileLineReader::FileLineReader() {
    currentLine = 0;
}

//FileLineReader copy constructor
FileLineReader::FileLineReader(FileLineReader& f) {
    this->currentLine = f.currentLine;
}

//Assignment operator
const FileLineReader& FileLineReader::operator= (const FileLineReader& f) {
    this->currentLine = f.currentLine;
    return *this;
}

//Stream insertion operator
ostream& operator<<(ostream& out, const FileLineReader& f) {
    out << "Using FileLineReader: " << endl;
    return out;
}

//Reads a line from a file
string FileLineReader::readLineFromFile(string fileName){
    string command;
    int count = 0;
    input.open(fileName);
    while (true) {
        if (count == currentLine) {
            getline (input, command);
            currentLine++;
            break;
        }
        else {
            getline (input, command);
            count++;
        }
    }
    input.close();
    return command;
}


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
    
}

