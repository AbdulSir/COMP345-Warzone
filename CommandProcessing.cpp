//
//  CommandProcessing.cpp
//  Warzone Command Processor
//

#include "CommandProcessing.h"
#include "GameEngine.h"
#include "LoggingObserver.h"
#include <iostream>
using namespace std;
#include <string>
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
    
    if (c.find("tournament") != string::npos) {
        effect = "Tournament Mode activated";
    }
    
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
    Notify(this);
}

//overrite ILoggable stringToLog method
std::string Command::stringToLog(){
    cout<<"\nWriting Command's Effect to gamelog.txt file ...\n"<<endl;
    std::ofstream myfile;
    myfile.open ("gamelog.txt", std::ios_base::app);
    myfile <<"Command's Effect: "<<this->effect<<"\n";
    myfile <<"-------------------------------------\n";
    myfile.close();
    return this->effect;
}


//METHODS IN COMMANDPROCESSOR

//CommandProcessor constructor
CommandProcessor::CommandProcessor() {
    this->lc = {};
    this->numMaxTurns = 10;
}

//CommandProcessor copy constructor
CommandProcessor::CommandProcessor(CommandProcessor& cp) {
    this->lc = cp.lc;
    this->numMaxTurns = cp.numMaxTurns;
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
    this->numMaxTurns = cp.numMaxTurns;
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
string CommandProcessor::getCommand(string gameState) {
    string commandStr = readCommand();
    if (validate(commandStr, gameState)) {
        cout << commandStr << " is a valid command for the " << gameState << " state\n" <<endl;
        Command* c = new Command(commandStr);
        LogObserver *observer = new LogObserver(c) ;
        saveCommand(c);
        c->saveEffect(commandStr);
        return commandStr;
    }
    else {
        cout << commandStr << " is not a valid command for the " << gameState << " state\n" << endl;
        Command* c = new Command(commandStr);
        LogObserver *observer = new LogObserver(c) ;
        saveCommand(c);
        c->effect = "No effect (Invalid command for " + gameState + " state)";
        return "";
    }
}

//Validates if command is valid in current game state
bool CommandProcessor::validate(string c, string gameState) {
    
    //Validating tournament command
    if (c.substr(0,14) == "tournament -M " && c.find(" -M ") < c.find(" -P ") && c.find(" -P ") < c.find(" -G ") && c.find(" -G ") < c.find(" -D ") && c.length() == c.find("-D")+5 && gameState == "start") {
        
        //Validating the map input
        string m = c.substr(c.find("-M")+3);
        m = m.substr(0, m.find(" "));
        while (m.find(",") != m.npos) {
            string subsM = m.substr(0, m.find(","));
            if (subsM.find(".map") == subsM.npos)
                return false;
            mapFiles.push_back(m.substr(0, m.find(",")));
            m = m.substr(m.find(",")+1);
        }
        mapFiles.push_back(m);
        if (mapFiles.size() < 1 || mapFiles.size() > 5 || m == "-P")
            return false;
        
        //Validating the player input
        string p = c.substr(c.find("-P")+3);
        p = p.substr(0, p.find(" "));
        while (p.find(",") != p.npos) {
            playersStrat.push_back(p.substr(0, p.find(",")));
            p = p.substr(p.find(",")+1);
        }
        playersStrat.push_back(p);
        if (playersStrat.size() < 2 || playersStrat.size() > 4 || p == "-G")
            return false;
        for (auto i:playersStrat) {
            if (i != "Human" && i != "Aggressive" && i != "Benevolent" && i != "Neutral" && i != "Cheater")
                return false;
        }
        
        //Validating the number of games input
        string g = c.substr(c.find("-G")+3);
        g = g.substr(0, g.find(" "));
        if (g.length() != 1 || g.at(0) < 48 || g.at(0) > 57)
            return false;
        numGames = stoi(g);
        if (numGames < 1 || numGames > 5)
            return false;
        
        //Validating the number of turns input
        string d = c.substr(c.find("-D")+3);
        if (d.length() != 2 || d.at(0) < 48 || d.at(0) > 57 || d.at(1) < 48 || d.at(1) > 57)
            return false;
        numMaxTurns = stoi(d);
        if (numMaxTurns < 10 || numMaxTurns > 50)
            return false;
        
        return true;
    }
    
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
    Notify(this);
}

//overrite ILoggable stringToLog method
std::string CommandProcessor::stringToLog(){
    cout<<"\nWriting Command to gamelog.txt file ..."<<endl;
    std::ofstream myfile;
    myfile.open ("gamelog.txt", std::ios_base::app);
    std::string gamelog;
    for (auto it = this->lc.begin(); it != this->lc.end(); it++)
    {
        if(it != this->lc.begin()){
            gamelog+= ", ";
        }
        gamelog+=(*it)->command;
    }
    myfile <<"Command: " << gamelog << "\n";
    myfile <<"-------------------------------------\n";
    myfile.close();
    return gamelog;
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
