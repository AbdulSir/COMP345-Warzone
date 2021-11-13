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
class Card;
class OrderList;
class Hand;
class Territory;

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
    Hand* getHand();
    void setName(string name);
    vector <int> continents_owned;
    vector <Territory*> getPeacefulTerritories();
    OrderList* getOrders();
    string getName();
    int getReinforcementPool();
    void addTerritory(Territory* t);
    void removeTerritory(Territory* t);
    void setTerritories(vector <Territory*> v);
    void setReinforcementPool(int number);
    void setPeacefulTerritories(vector<Territory*> v);
    void setWillDrawCard(bool value);

private:
    string name;
    Hand * hand;
    vector <Territory*> territories;
    OrderList* orders;
    int reinforcementPool;
    vector <Territory*> peacefulTerrtories;
    bool willDrawCardAtTheEndOfTurn;
};
