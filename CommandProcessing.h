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
    string command;
    string effect;
    
    //Constructors
    Command();
    Command(string c);
    Command(const Command &c);
    
    //Assignment operator
    Command& operator= (const Command& c);
    
    //Method to save effect of a command
    void saveEffect(string c);
    
    //stream insertion operator
    friend ostream& operator<<(ostream& out, const Command& c);
    
    //overrite ILoggable stringToLog method
    virtual std::string stringToLog();
    
};

//CommandProcessor object
class CommandProcessor : public ILoggable, public Subject {
public:
    
    //list of commands
    list<Command*> lc;
    
    //Constructors + Destructor
    CommandProcessor();
    CommandProcessor(CommandProcessor& cp);
    virtual ~CommandProcessor();
    
    //Assignment operator
    const CommandProcessor& operator= (const CommandProcessor& cp);
    
    //Method to get commands
    void getCommand(string gameState);
    
    //Method to validate commands
    bool validate(string c, string gameState);
    
    //stream insertion operator
    friend ostream& operator<<(ostream& out, const CommandProcessor& cp);
    
    //overrite ILoggable stringToLog method
    virtual std::string stringToLog();
    
protected:
    
    //Method that reads commmand for the console, can be overriden to read commands from a file
    virtual string readCommand();
    
    //Method that saves command into a list of commands
    void saveCommand(Command* c);
};


//FileLineReader
class FileLineReader {
public:
    ifstream input;
    
    //Constructors
    FileLineReader();
    FileLineReader(FileLineReader& f);
    
    //Assignment operator
    const FileLineReader& operator= (const FileLineReader& f);
    
    //Method that reads one line (command) from file
    string readLineFromFile(string fileName);
    
    //stream insertion operator
    friend ostream& operator<<(ostream& out, const FileLineReader& f);
private:
    int currentLine;
};


//FileCommandProcessorAdapter
class FileCommandProcessorAdapter: public CommandProcessor {
public:
    
    //FileLineReader that allows FileCommandProcessorAdapter to read from a file
    FileLineReader* flr;
    string fileName;
    
    //Constructors
    FileCommandProcessorAdapter(string fileName);
    FileCommandProcessorAdapter(FileCommandProcessorAdapter& fcpa);
    ~FileCommandProcessorAdapter();
    
    //Assignment operator
    const FileCommandProcessorAdapter& operator= (const FileCommandProcessorAdapter& fcpa);
    
    //Reads command from file
    string readCommand();
    
    //stream insertion operator
    friend ostream& operator<<(ostream& out, const FileCommandProcessorAdapter& fcpa);
};
