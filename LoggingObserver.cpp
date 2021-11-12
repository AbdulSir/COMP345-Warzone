//
//  LoggingObserver.cpp
//  Warzone
//
//

#include "LoggingObserver.h"
#include <fstream>

//METHODS IN ILoggable

//default constructor
ILoggable::ILoggable(){
    
}

//destructor
ILoggable::~ILoggable(){
    
}

//METHODS IN Observer

//default constructor
Observer::Observer(){
    
}

//destructor
Observer::~Observer(){
}

//METHODS IN Subject

//default constructor
Subject::Subject(){
    _observers=new std::list<Observer*>;
    
}

//destructor
Subject::~Subject(){
    delete _observers;
}

void Subject::Attach(Observer* o){
  _observers->push_back(o);
};

void Subject::Detach(Observer* o){
  _observers->remove(o);
};

void Subject::Notify(ILoggable* il){
    std::list<Observer *>::iterator i=_observers->begin();
    for (; i!= _observers->end();i++){
        (*i)->Update(il);
    }
}


//METHODS IN LogObserver

//default constructor
LogObserver::LogObserver():Observer(){
    
}

//constructor
LogObserver::LogObserver(Subject* s){
  //Upon instantiation, attaches itself
  //to a LogObserver
  _subject = s;
  _subject->Attach(this);
};

//destructor
LogObserver::~LogObserver(){
  //Upon destruction, detaches itself
  //from its LogObserver
  _subject->Detach(this);
};


void LogObserver::Update(ILoggable* il){
    il->stringToLog();
}
