#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"
#include "PlayerStrategies.h"
using namespace std;

class Order;
class Card;
class OrderList;
class Hand;
class Territory;
class PlayerStrategy;

//Player class declaration
class Player{
public:
    PlayerStrategy* ps;
    Map* map; //To be able to call adjacent_territory_vector()
    Player(); //default c*onstructor
    Player(string name);
    Player(PlayerStrategy *initStrategy);
    Player(string name, Hand * hand, vector <Territory*> territories, PlayerStrategy* ps); // constructor
    Player(const Player &p); //copy constructor
    ~Player(); //destructor
    Player& operator =(const Player& p); // assignment operator
    friend ostream& operator << (ostream &out, const Player& p); // stream insertion operator
    vector <Territory*> defendList;
    vector <Territory*> attackList;
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
    void setMap(Map* m);

private:
    string name;
    Hand * hand;
    vector <Territory*> territories;
    OrderList* orders;
    int reinforcementPool;
    vector <Territory*> peacefulTerrtories;
    bool willDrawCardAtTheEndOfTurn;
};
