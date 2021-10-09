#ifndef Order_H
#define Order_H
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Order{
private:
   //attributes
    string orderID;
    string description;
    string effect;
public:
    //default constructor
    Order();
    //parametrized constructor
    Order(string orderID,string description, string effect);
    //asssignment operator
    Order& operator= (const Order& order);
    //copy constructor
    Order(const Order &order);
    
    string getOrderID();//@return string orderID
    string getDescription();//@return string description
    string getEffect();//@return string effect
    void setEffect(string e);//@return string effect
    
    void setOrderID(string newID);//changes name of order
        
    bool validate();
    void execute();
    

    //stream insertion operators
    friend ostream& operator <<(ostream &out, const Order &order);
    friend istream& operator >>(istream &in, Order &order);
            
};

class Deploy: public Order{
public:
    Deploy();//default constructor
    Deploy(string orderID, string description, string effect);//parametrized constructor
    Deploy(const Deploy&deploy);//copy constructor
    Deploy& operator= (const Deploy& deploy);//asssignment operator
    bool validate();
    void execute();
};


//copy above formatting
class Advance: public Order{
public:
    Advance();//default constructor
    Advance(string orderID,string description, string effect);//parametrized constructor
    Advance(const Advance& ad);//copy constructor
    Advance& operator= (const Advance& advanced);//asssignment operator
    bool validate();
    void execute();
};

class Bomb: public Order
{
public:
    Bomb();//default constructor
    Bomb(string orderID,string description, string effect);//parametrized constructor
    Bomb(const Bomb& b);//copy constructor
    Bomb& operator= (const Bomb& b);//asssignment operator
    bool validate();
    void execute();
};

class Blockade: public Order
{
public:
    Blockade();//default constructor
    Blockade(string orderID,string description, string effect);//parametrized constructor
    Blockade(const Blockade& bl);//copy constructor
    Blockade& operator= (const Blockade& bl);//asssignment operator
    bool validate();
    void execute();
};

class Airlift: public Order
{
public:
    Airlift();//default constructor
    Airlift(string orderID,string description, string effect);//parametrized constructor
    Airlift(const Airlift& a);//copy constructor
    Airlift& operator= (const Airlift& a);//asssignment operator
    bool validate();
    void execute();
};

class Negotiate: public Order
{
public:
    Negotiate();//default constructor
    Negotiate(string orderID,string description, string effect);//parametrized constructor
    Negotiate(const Negotiate& n);//copy constructor
    Negotiate& operator= (const Negotiate& n);//asssignment operator
    bool validate();
    void execute();
};


class OrderList{
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
    friend istream& operator>> (istream& in,  const OrderList& orderList);
};


#endif

