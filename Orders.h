#pragma once

#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include "Player.h"

class Player;
class Territory;

// free function to determine if a territory is owned by player
bool isTerritoryOwnedByPlayer(Player* p, Territory* t);
class Order {
    public:
        // attributes
        Player* orderIssuer;
        string orderID;
        //default constructor
        Order();
        //parametrized constructor
        Order(string orderID, Player* orderIssuer);
        //asssignment operator
        Order& operator= (const Order& order);
        //copy constructor
        Order(const Order &order);
        virtual ~Order();
        string getOrderID();//@return string orderID    
        bool validate();
        virtual void execute();
        //stream insertion operators
        friend ostream& operator <<(ostream &out, const Order &order);
};

class Deploy: public Order {
    public:
        // attributes
        Territory* target;
        int numberOfUnits;
        //default constructor
        Deploy();
        //parametrized constructor
        Deploy(string orderID, Player* player, Territory* territory, int number);
        //copy constructor
        Deploy(const Deploy &deploy);
        //asssignment operator
        Deploy& operator= (const Deploy& deploy);
        bool validate();
        void execute();
        //stream insertion operators
        friend ostream& operator <<(ostream &out, const Deploy &order);
};

class Advance: public Order {
    public:
        // attributes
        Territory* from;
        Territory* target;
        int numberOfUnits;
        //default constructor
        Advance();
        //parametrized constructor
        Advance(string orderID, Player* player, Territory* t1, Territory* t2, int number);
        //copy constructor
        Advance(const Advance& ad);
        //asssignment operator
        Advance& operator= (const Advance& advanced);
        bool validate();
        void execute();
        //stream insertion operators
        friend ostream& operator <<(ostream &out, const Advance &order);
};


class Airlift: public Order {
    public:
        // attributes
        Territory* from;
        Territory* target;
        int numberOfUnits;
        //default constructor
        Airlift();
        //parametrized constructor
        Airlift(string orderID, Player* player, Territory* t1, Territory* t2, int number);
        //copy constructor
        Airlift(const Airlift& a);
        //asssignment operator
        Airlift& operator= (const Airlift& a);
        bool validate();
        void execute();
        //stream insertion operators
        friend ostream& operator <<(ostream &out, const Airlift &order);
};

class Bomb: public Order {
    public:
        // attributes
        Territory* from;
        Territory* target;
        //default constructor
        Bomb();
        //parametrized constructor
        Bomb(string orderID, Player* player, Territory* t1, Territory* t2);
        //copy constructor
        Bomb(const Bomb& b);
        //asssignment operator
        Bomb& operator= (const Bomb& b);
        bool validate();
        void execute();
        //stream insertion operators
        friend ostream& operator <<(ostream &out, const Bomb &order);
};

class Blockade: public Order {
    public:
        // attributes
        Territory* target;
        //default constructor
        Blockade();
        //parametrized constructor
        Blockade(string orderID, Player* player, Territory* territory);
        //copy constructor
        Blockade(const Blockade& bl);
        //asssignment operator
        Blockade& operator= (const Blockade& bl);
        bool validate();
        void execute();
        //stream insertion operators
        friend ostream& operator <<(ostream &out, const Blockade &order);
};

class Negotiate: public Order {
    public:
        // attributes
        Player* target;
        //default constructor
        Negotiate();
        //parametrized constructor
        Negotiate(string orderID, Player* player, Player* target);
        //copy constructor
        Negotiate(const Negotiate& n);
        //asssignment operator
        Negotiate& operator= (const Negotiate& n);
        bool validate();
        void execute();
        //stream insertion operators
        friend ostream& operator <<(ostream &out, const Negotiate &order);
};

class OrderList {
    public:
        // attributes
        vector<Order*> orderList;
        //default constructor
        OrderList();
        //constructor
        OrderList(const OrderList& obj);
        //desconstructor
        ~OrderList();
        //assignment operator
        OrderList& operator= (const OrderList& orderList);
        //add order to list
        void addOrder(Order* order);
        //move order with list
        void move(Order* order, int newPosition);
        //remove order from list
        void remove(Order* order);
        // stream insertion operators
        friend ostream& operator<< (ostream& out, const OrderList& orderList);
};
