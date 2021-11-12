//
//  CommandProcessing.h
//  Warzone Command Processor
//

#include <string>
using namespace std;
#include <fstream>
using namespace std;
#include <list>
#include "LoggingObserver.h"

#pragma once

//Command object
class Command : public ILoggable, public Subject {
public:
    Command();
    Command(string c);
    Command(const Command &c);
    Command& operator= (const Command& c);
    string command;
    string effect;
    void saveEffect(string c);
    friend ostream& operator<<(ostream& out, const Command& c);
    
    //overrite ILoggable stringToLog method
    virtual std::string stringToLog();
    
};

//CommandProcessor object
class CommandProcessor : public ILoggable, public Subject {
public:
    list<Command*> lc;
    CommandProcessor();
    CommandProcessor(CommandProcessor& cp);
    virtual ~CommandProcessor();
    CommandProcessor& operator= (const CommandProcessor& cp);
    void getCommand(string gameState);
    bool validate(string c, string gameState);
    friend ostream& operator<<(ostream& out, const CommandProcessor& cp);
    
    //overrite ILoggable stringToLog method
    virtual std::string stringToLog();
    
protected:
    virtual string readCommand();
    void saveCommand(Command* c);
};


//FileLineReader
class FileLineReader {
public:
    ifstream input;
    int currentLine;
    FileLineReader();
    FileLineReader(FileLineReader& f);
    FileLineReader& operator= (const FileLineReader& f);
    string readLineFromFile(string fileName);
    friend ostream& operator<<(ostream& out, const FileLineReader& f);
};


//FileCommandProcessorAdapter
class FileCommandProcessorAdapter: public CommandProcessor {
public:
    FileLineReader* flr;
    string fileName;
    FileCommandProcessorAdapter(string fileName);
    FileCommandProcessorAdapter(FileCommandProcessorAdapter& fcpa);
    ~FileCommandProcessorAdapter();
    FileCommandProcessorAdapter& operator= (const FileCommandProcessorAdapter& fcpa);
    string readCommand();
    friend ostream& operator<<(ostream& out, const FileCommandProcessorAdapter& fcpa);
};
