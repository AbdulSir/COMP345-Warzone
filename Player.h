//
//  Player.hpp
//  Comp 345 a1
//
//  Created by Beatrice Cobo on 2021-09-28.
//

#ifndef Player_h
#define Player_h

#include <list>
#include <string>
#include <iostream>
using namespace std;

class Territory{
public:
    Territory();
    
};

class Card{
    
};

class Order{
public:
    Order();
    
};
class Hand{
    
};

/**
 
 */
class Player{
public:
    Player(); //default constructor
    Player(string name, Hand * hand, list <Territory*> territories); // constructor
    Player(const Player &p); //copy constructor
    Player& operator =(const Player& p); // assignment operator
    friend ostream& operator<<(ostream& ostmr, const Player& p); // stream insertion operator
    //friend istream& operator<<(istream& istmr, const Player& p);
    list <Territory*> toDefend();
    list <Territory*> toAttack();
    list <Order*> issueOrder();
    
private:
    string name;
    Hand * hand;
    list <Territory*> territories;
    list <Order*> orders;
    
};


#endif /* Player_h */
