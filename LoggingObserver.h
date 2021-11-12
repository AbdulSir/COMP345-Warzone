//
//  LoggingObserver.h
//  Warzone
//
//

#ifndef LoggingObserver_h
#define LoggingObserver_h
#include <string>
#include <list>
#include <iostream>

//ILoggable class declaration
class ILoggable{
public:
    ILoggable(); //default constructor
    ~ILoggable(); //destructor
    virtual std::string stringToLog()=0; //pure virtual stringToLog function
    
};

//Observer class declaration
class Observer{
public:
    ~Observer(); //destructor
    virtual void Update(ILoggable* il)=0; //pure virtual Update function
    
protected:
    Observer(); //default constructor
    
};

//Subject class declaration
class Subject{
public:
    Subject(); //default constructor
    ~Subject(); //destructor
    virtual void Notify(ILoggable* il);
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);

private:
    std::list<Observer*> *_observers;
    
};

//LogObserver class declaration
class LogObserver: public Observer{
public:
    LogObserver(); //default constructor
    LogObserver(Subject* s); //constructor
    ~LogObserver(); //destructor
    void Update(ILoggable* il);
    
    Subject *_subject;
};
#endif /* LoggingObserver_h */
