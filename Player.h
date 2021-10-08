/**
 Part 2: Player.h
 */

#ifndef Player_h
#define Player_h

#include <vector>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//Territory dummy class declaration
class Territory
{
    public:
        Territory();
        Territory (string terr_name, int contin_ref, int num_of_armies);
        Territory (const Territory &t1); //Copy constructor
        Territory& operator= (const Territory& t1); // overloaded assignment operator
        friend ostream & operator << (ostream &out, const Territory &t1);// stream insertion operator
        friend istream & operator >> (istream &in,  Territory &t1);// stream extraction operator
        string getName();
        string territory_name;
        int continent_ref;
        int army_nb;
};

//Card dummy class declaration
class Card{
    
};

//Order dummy class declaration
class Order{
public:
    Order();
    string description;
    
};

//OrdersList dummy class declaration
class OrdersList{
public:
    vector <Order*> list_orders;
    
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
    OrdersList* getOrders();
    
private:
    string name;
    Hand * hand;
    vector <Territory*> territories;
    OrdersList* orders;
    
};


#endif /* Player_h */
