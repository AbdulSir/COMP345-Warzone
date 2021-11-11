#pragma once

#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include "Player.h"

class Player;
class Territory;

bool isTerritoryOwnedByPlayer(Player* p, Territory* t);
class Order {
    private:
       //attributes, identifier of the order
        string orderID;
    public:
        //default constructor
        Order();
        //parametrized constructor
        Order(string orderID, Player* orderIssuer);
        //asssignment operator
        Order& operator= (const Order& order);
        //copy constructor
        Order(const Order &order);
        // virtual ~Order();
        string getOrderID();//@return string orderID    
        bool validate();
        virtual void execute();
        //stream insertion operators
        friend ostream& operator <<(ostream &out, const Order &order);
        Player* orderIssuer;
};

class Deploy: public Order{
    public:
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
        Territory* target;
        int numberOfUnits;
};

class Advance: public Order{
    public:
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
        Territory* from;
        Territory* target;
        int numberOfUnits;
};


class Airlift: public Order
{
    public:
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
        Territory* from;
        Territory* target;
        int numberOfUnits;
};

class Bomb: public Order
{
    public:
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
        Territory* from;
        Territory* target;
};

/*
class Blockade: public Order
{
    public:
        //default constructor
        Blockade();
        //parametrized constructor
        Blockade(string orderID);
        //copy constructor
        Blockade(const Blockade& bl);
        //asssignment operator
        Blockade& operator= (const Blockade& bl);
        bool validate();
        void execute();
};

class Negotiate: public Order
{
    public:
        //default constructor
        Negotiate();
        //parametrized constructor
        Negotiate(string orderID);
        //copy constructor
        Negotiate(const Negotiate& n);
        //asssignment operator
        Negotiate& operator= (const Negotiate& n);
        bool validate();
        void execute();
};
*/

class OrderList {
    public:
        //vector holding all orders
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
