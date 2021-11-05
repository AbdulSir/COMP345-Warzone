//
//  CommandProcessing.h
//  Warzone Command Processor
//
#include <string>
using namespace std;
#include <fstream>
#include <list>

#pragma once

//Command object
class Command {
public:
    Command();
    Command(string c);
    Command(const Command &c);
    Command& operator= (const Command& c);
    string command;
    string effect;
    void saveEffect(string c);
    friend ostream& operator<<(ostream& out, const Command& c);
};

//CommandProcessor object
class CommandProcessor {
public:
    list<Command*> lc;
    CommandProcessor();
    CommandProcessor(CommandProcessor& cp);
    ~CommandProcessor();
    CommandProcessor& operator= (const CommandProcessor& cp);
    void getCommand(string gameState);
    bool validate(string c, string gameState);
    friend ostream& operator<<(ostream& out, const CommandProcessor& cp);
private:
    string readCommand();
    void saveCommand(Command* c);
};


//FileCommandProcessorAdapter
class FileCommandProcessorAdapter: CommandProcessor {
public:
    std::ifstream flr;
    void readFile(string file);
};




