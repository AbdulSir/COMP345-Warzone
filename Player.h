#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"
using namespace std;

class Order;
class OrderList;
class Card;
class Hand;

//Player class declaration
class Player{
public:
    Player(); //default constructor
    Player(string name);
    Player(string name, Hand * hand, vector <Territory*> territories); // constructor
    Player(const Player &p); //copy constructor
    ~Player(); //destructor
    Player& operator =(const Player& p); // assignment operator
    friend ostream& operator << (ostream &out, const Player& p); // stream insertion operator
    vector <Territory*> toDefend();
    vector <Territory*> toAttack();
    void issueOrder();
    vector <Territory*> getTerritories();
    OrderList* getOrders();
    string getName();
    Hand* getHand();
    int getReinforcementPool();
    void addTerritory(Territory* t);
    void removeTerritory(Territory* t);
    void setReinforcementPool(int number);
    void setName(string name);
    vector <int> continents_owned;

private:
    string name;
    Hand * hand;
    vector <Territory*> territories;
    OrderList* orders;
    int reinforcementPool;
};
