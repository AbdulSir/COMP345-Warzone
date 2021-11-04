//
//  LoggingObserver.cpp
//  Warzone
//
//

#include "LoggingObserver.h"
#include <fstream>

ILoggable::ILoggable(){
    
}
ILoggable::~ILoggable(){
    
}

Observer::Observer(){
    
}

Observer::~Observer(){
}

Subject::Subject(){
    _observers=new std::list<Observer*>;
    
}

Subject::~Subject(){
    delete _observers;
}

void Subject::Notify(ILoggable& il){
    std::list<Observer *>::iterator i=_observers->begin();
    for (; i!= _observers->end();i++)
        (*i)->Update(il);
}

LogObserver::LogObserver():Observer(){
    
}

void LogObserver::Update(ILoggable& il){
    
}

std::string LogObserver::stringToLog(){
    std::ofstream myfile;
    myfile.open ("gamelog.txt");
    myfile.close();
    return "";
}
