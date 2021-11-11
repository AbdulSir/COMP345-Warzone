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
class Territory;

//Player class declaration
class Player{
public:
    Player(); //default constructor
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
    int getReinforcementPool();
    void setReinforcementPool(int number);

private:
    string name;
    Hand * hand;
    vector <Territory*> territories;
    OrderList* orders;
    int reinforcementPool;
};
