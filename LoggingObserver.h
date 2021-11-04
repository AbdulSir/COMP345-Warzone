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
    virtual std::string stringToLog()=0; //pure virtual function
    
private:
    
};

//Observer class declaration
class Observer{
public:
    ~Observer(); //destructor
    virtual void Update(ILoggable& il)=0; //pure virtual function
    
protected:
    Observer(); //default constructor
    
};

//Subject class declaration
class Subject{
public:
    Subject(); //default constructor
    ~Subject(); //destructor
    virtual void Notify(ILoggable& il);
    
private:
    std::list<Observer*> *_observers;
    
};

//LogObserver class declaration
class LogObserver: public Observer{
public:
    LogObserver(); //default constructor
    ~LogObserver(); //destructor
    void Update(ILoggable& il);
    std::string stringToLog();
    
    
};
#endif /* LoggingObserver_h */
