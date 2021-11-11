#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include "Orders.h"
using namespace std;

class Order;
class OrderList;
//Territory dummy class declaration
class Territory
{
    public:
        Territory();
        Territory (string terr_name, int contin_ref, int num_of_armies);
        Territory (const Territory &t1); //Copy constructor
        Territory& operator= (const Territory& t1); // overloaded assignment operator
        friend ostream & operator << (ostream &out, const Territory &t1);// stream insertion operator
        string getName();
        void setArmy(int numberOfArmy);
        string territory_name;
        int continent_ref;
        int army_nb;
};

//Card dummy class declaration
class Card{
    
};

//Hand dummy class declaration
class Hand{
    
};

//Player class declaration
class Player{
public:
    Player(); //default constructor
    Player(string name, Hand * hand, vector <Territory*> territories); // constructor
    Player(const Player &p); //copy constructor
    ~Player(); //destructor
    Player& operator =(const Player& p); // assignment operator
    friend ostream& operator << (ostream &out, const Player& p); // stream insertion operator
    friend istream& operator >> (istream &in , Player& p); // stream extraction operator
    vector <Territory*> toDefend();
    vector <Territory*> toAttack();
    void issueOrder();
    vector <Territory*> getTerritories();
    OrderList* getOrders();
    string getName();

private:
    string name;
    Hand * hand;
    vector <Territory*> territories;
    OrderList* orders;
};
