#ifndef Order_H
#define Order_H
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Order{
private:
   //Only attribute
    string orderID;
    string description;
    string effect;
public:
    //default constructor
    Order();
    //parametrized constructor
    Order(string orderID, string effect);
    //Destructor
    //~Order();
    //asssignment operator
    Order& operator= (const Order& order);
    //copy constructor
    Order(const Order &order);

    string getOrderID();
        //@return string orderID
    string getDescription();
        //@return string description
    string getEffect();
        //@return string effect
    
    void setOrderID(string newID);
        //changes name of order
        
    bool validate(Order order);
    void execute(Order order);
    

    //stream insertion operators
    friend ostream operator <<(ostream &out, const Order &order);
    friend istream& operator >>(istream &in, Order &order);
            
};

class Deploy: public Order{
public:
    Deploy();
    Deploy(string orderID, string effect);
    Deploy(const Deploy&deploy);
    //~Deploy();
    Deploy& operator= (const Deploy& deploy);
    bool validate(Deploy deploy);
    void execute(Deploy deploy);
};


//copy above formatting
class Advance: public Order{
public:
    Advance();
    Advance(string orderID, string effect);
    Advance(const Advance& ad);
    //~Advance();
    Advance& operator= (const Advance& advanced);
    bool validate(Advance advance);
    void execute(Advance advance);
};

class Bomb: public Order
{
public:
    Bomb();
    Bomb(string orderID, string effect);
    Bomb(const Bomb& b);
    //~Bomb();
    Bomb& operator= (const Bomb& b);
    bool validate(Bomb bomb);
    void execute(Bomb bomb);
};

class Blockade: public Order
{
public:
    Blockade();
    Blockade(string orderID, string effect);
    Blockade(const Blockade& bl);
    //~Blockade();
    Blockade& operator= (const Blockade& bl);
    bool validate(Blockade blockade);
    void execute(Blockade blockade);
};

class Airlift: public Order
{
public:
    Airlift();
    Airlift(string orderID, string effect);
    Airlift(const Airlift& a);
    //~Airlift();
    Airlift& operator= (const Airlift& a);
    bool validate(Airlift airlift);
    void execute(Airlift airlift);
};

class Negotiate: public Order
{
public:
    Negotiate();
    Negotiate(string orderID, string effect);
    Negotiate(const Negotiate& n);
    //~Negotiate();
    Negotiate& operator= (const Negotiate& n);
    bool validate(Negotiate negotiate);
    void execute(Negotiate negotiate);
};


class OrderList{
public:
    //vector holding all orders
    vector<Order*> orderList;

    //default constructor
    OrderList();
    //de
    OrderList(const OrderList& obj);
    //assignment operator
    OrderList& operator= (const OrderList& orderList);

    //add order to list
    void addOrder(Order* order);
    //move order with list
    void move(int startPosition, int newPosition);
    //remove order from list
    void remove(Order order);

    // stream insertion operators
    friend ostream& operator<< (ostream& out, const OrderList& orderList);
    friend istream& operator>> (istream& in,  const OrderList& orderList);
};


#endif
