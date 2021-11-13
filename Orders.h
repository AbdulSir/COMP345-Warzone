#pragma once

#include "Player.h"
#include "Map.h"
#include <string>
#include <vector>
#include <iostream>
#include "LoggingObserver.h"
using namespace std;

class Player;
class Territory;
class Map;
class ILoggable;
class Subject;

// free function to determine if a territory is owned by player
bool isTerritoryOwnedByPlayer(Player* p, Territory* t);
class Order : public ILoggable, public Subject {
    public:
        int orderId;
        static int currentId;
        string effect;
        // attributes
        Player* orderIssuer;
        //default constructor
        Order();
        //parametrized constructor
        Order(Player* orderIssuer);
        //asssignment operator
        Order& operator= (const Order& order);
        //copy constructor
        Order(const Order &order);
        // virtual ~Order();
        void setOrderIssuer(Player* orderIssuer);
        void setEffect(string effect);
        bool validate();
        virtual void execute();
        //stream insertion operators
        friend ostream& operator <<(ostream &out, const Order &order);
        virtual std::string stringToLog();
};

class Deploy: public Order {
    public:
        // attributes
        Territory* target;
        int numberOfUnits;
        //default constructor
        Deploy();
        //parametrized constructor
        Deploy(Player* player, Territory* territory, int number);
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
        Map* map;
        //default constructor
        Advance();
        //parametrized constructor
        Advance(Player* player, Territory* t1, Territory* t2, int number, Map* m);
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
        Airlift(Player* player, Territory* t1, Territory* t2, int number);
        //copy constructor
        Airlift(const Airlift& a);
        //asssignment operator
        Airlift& operator= (const Airlift& a);
        //setters
        void setFrom(Territory* from);
        void setTarget(Territory* target);
        void setNumberOfUnits(int number);
        bool validate();
        void execute();
        //stream insertion operators
        friend ostream& operator <<(ostream &out, const Airlift &order);
};

class Bomb: public Order {
    public:
        // attributes
        Territory* target;
        Map* map;
        //default constructor
        Bomb();
        //parametrized constructor
        Bomb(Player* player, Territory* t1, Territory* t2, Map* m);
        //copy constructor
        Bomb(const Bomb& b);
        //asssignment operator
        Bomb& operator= (const Bomb& b);
        //setters
        void setTarget(Territory* target);
        void setMap(Map* m);
        bool validate();
        void execute();
        //stream insertion operators
        friend ostream& operator <<(ostream &out, const Bomb &order);
};

class Blockade: public Order {
    public:
        // attributes
        Territory* target;
        Player* neutral;
        //default constructor
        Blockade();
        //parametrized constructor
        Blockade(Player* player, Territory* territory, Player* neutral);
        //copy constructor
        Blockade(const Blockade& bl);
        //asssignment operator
        Blockade& operator= (const Blockade& bl);
        bool validate();
        void execute();
        //setters
        void setTarget(Territory* target);
        void setNeutralPlayer(Player* player);
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
        Negotiate(Player* player, Player* target);
        //copy constructor
        Negotiate(const Negotiate& n);
        //asssignment operator
        Negotiate& operator= (const Negotiate& n);
        //setters
        void setTarget(Player* target);
        bool validate();
        void execute();
        //stream insertion operators
        friend ostream& operator <<(ostream &out, const Negotiate &order);
};

class OrderList : public ILoggable, public Subject {
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
        virtual std::string stringToLog();
};

