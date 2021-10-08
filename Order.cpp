#include "Order.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

        
//default constructor
Order::Order(){
    this->orderID = "";
    this->description = "";
    this->effect = "";
    cout << "Default Order: " << "-" << " Created in Base Class" <<endl;
};

//parametrized constructor
Order::Order(string orderID, string effect){
    this->orderID = orderID;
    this->effect = effect;
    this->description = "order";
    cout << "Order:  " << orderID << " Created in Base Class" <<endl;
};

//Copy constructor
Order::Order(const Order& obj){
    this->orderID = obj.orderID;
    this->description = obj.description;
    this->effect = obj.effect;
}

//assignment operator
Order& Order::operator= (const Order& order){
    this->orderID = order.orderID;
    this->description = order.description;
    this->effect = order.effect;
    return *this;
};

string Order::getOrderID(){
    return orderID;
}

string Order::getDescription(){
    return description;
};
    //@return string description
string Order::getEffect(){
    return effect;
};
bool Order::validate(Order order){
    return (order.getDescription() == "deploy" || order.getDescription() == "advance" || order.getDescription() == "bomb" || order.getDescription() == "blockade" || order.getDescription() == "airlift" || order.getDescription() == "negotiate");
};

//execute order - for each Order subclass
void Order::execute(Order order){
        if (validate(order))
            cout << order.orderID + " order executed";
        else
            cout << "Invalid Order";
}



Deploy::Deploy(): Order(){
    cout << "Default Deploy: " << "-" << " Created in Subclass" <<endl;
};

Deploy::Deploy(string orderID, string effect) : Order(orderID,effect){
    cout << "Deploy: " << orderID << " Created in Subclass" <<endl;
}

//copy constructor
Deploy::Deploy(const Deploy& d) : Order(d){
  cout << "Inside copy constructor of Deploy" << endl;
}

Deploy& Deploy::operator=(const Deploy& d){
  cout << "Inside operator = of Deploy" << endl;
  Order::operator= (d);
  return *this;
}



bool Deploy::validate(Deploy deploy){
    return (deploy.getDescription() == "deploy");
};


void Deploy::execute(Deploy deploy){
    if (validate(deploy))
        cout << "Deploy order executed";
};



//default constructor
Advance::Advance():Order(){
    cout << "Default Advance: " << "-" << " Created in Subclass" <<endl;
};

//constructor
Advance::Advance(string orderID, string effect) : Order(orderID,effect){
    cout << "Advance: " << orderID << " Created in Subclass" <<endl;
}

//copy constructor
Advance::Advance(const Advance& a) : Order(a){
  cout << "Inside copy constructor of Advance" << endl;
}

Advance& Advance::operator=(const Advance& ad){
  cout << "Inside operator = of Advance" << endl;
  Order::operator= (ad);
  return *this;
}

bool Advance::validate(Advance advance){
    return (advance.getDescription() == "advance");
};

void Advance::execute(Advance advance){
    if (validate(advance))
        cout << "Advance order executed";
};



Bomb::Bomb():Order(){
    cout << "Default Bomb: " << "-" << " Created in Subclass" <<endl;
};

Bomb::Bomb(string orderID, string effect) : Order(orderID,effect){
    cout << "Bomb: " << orderID << " Created in Subclass" <<endl;
}

//copy constructor
Bomb::Bomb(const Bomb& b) : Order(b){
  cout << "Inside copy constructor of Bomb" << endl;
}

Bomb& Bomb::operator=(const Bomb& b){
  cout << "Inside operator = of Bomb" << endl;
  Order::operator= (b);
  return *this;
}

bool Bomb::validate(Bomb bomb){
    return (bomb.getDescription() == "bomb");
};
void Bomb::execute(Bomb bomb){
    if (validate(bomb))
        cout << "Bomb order executed";
};


Blockade::Blockade():Order(){
    cout << "Default Blockade: " << "-" << " Created in Subclass" <<endl;
};

Blockade::Blockade(string orderID, string effect) : Order(orderID,effect){
    cout << "Blockade: " << orderID << " Created in Subclass" <<endl;
}

//copy constructor
Blockade::Blockade(const Blockade& bl) : Order(bl){
  cout << "Inside copy constructor of Blockade" << endl;
}

Blockade& Blockade::operator=(const Blockade& bl){
  cout << "Inside operator = of Blockade" << endl;
  Order::operator= (bl);
  return *this;
}

bool Blockade::validate(Blockade blockade){
    return (blockade.getDescription() == "blockade");
};
void Blockade::execute(Blockade blockade){
    if (validate(blockade))
        cout << "Blockade order executed";
};


Airlift::Airlift():Order(){
    cout << "Default Airlift: " << "-" << " Created in Subclass" <<endl;
}
Airlift::Airlift(string orderID, string effect) : Order(orderID,effect){
    cout << "Airlift: " << orderID << " Created in Subclass" <<endl;
}

//copy constructor
Airlift::Airlift(const Airlift& a) : Order(a){
  cout << "Inside copy constructor of Airlift" << endl;
}

Airlift& Airlift::operator=(const Airlift& a){
  cout << "Inside operator = of Airlift" << endl;
  Order::operator= (a);
  return *this;
}

bool Airlift::validate(Airlift airlift){
    return (airlift.getDescription() == "airlift");
};
void Airlift::execute(Airlift airlift){
    if (validate(airlift))
        cout << "Airlift order executed";
};


Negotiate::Negotiate():Order(){
    cout << "Default Negotiate: " << "-" << " Created in Subclass" <<endl;
};

Negotiate::Negotiate(string orderID, string effect) : Order(orderID,effect){
    cout << "Negotiate: " << orderID << " Created in Subclass" <<endl;
}

//copy constructor
Negotiate::Negotiate(const Negotiate& n) : Order(n){
  cout << "Inside copy constructor of Negotiate" << endl;
}

Negotiate& Negotiate::operator=(const Negotiate& n){
  cout << "Inside operator = of Negotiate" << endl;
  Order::operator= (n);
  return *this;
}

bool Negotiate::validate(Negotiate negotiate){
    return (negotiate.getDescription() == "negotiate");
};
void Negotiate::execute(Negotiate negotiate){
    if (validate(negotiate))
        cout << "Negotiate order executed";
};




//OrderList Class

//default constructor
OrderList::OrderList(){
    this->orderList={};
};

OrderList::OrderList(const OrderList& obj){
    vector<Order*> temp_o(obj.orderList.size());
    this->orderList= temp_o;
    for (int i=0; i<obj.orderList.size(); i++)
        orderList[i] = new Order(*obj.orderList[i]);
};

//assignment operator
OrderList& OrderList::operator= (const OrderList& o){
    vector<Order*> temp_o(o.orderList.size());
    this->orderList= temp_o;
    for (int i=0; i<o.orderList.size(); i++)
        orderList[i] = new Order(*o.orderList[i]);
    return *this;
};


void OrderList::addOrder(Order* order){
    Order* newOrder = new Order(order->getOrderID(),order->getEffect());
   orderList.push_back(newOrder);
}

//stream insertion operator
ostream& operator<<(ostream& out, const OrderList& o)
{
    out << "OrderList has the following orders:"<<endl ;
    out << "-------------------------------"<<endl;
    for(int i =0; i<o.orderList.size();i++){
        out<<o.orderList[i]->getOrderID()<<endl;
    }
    return out;
}

// stream extraction operator
istream& operator>>(istream &in, OrderList& o) {
    return in;
}

//move order elsewhere in list
void OrderList::move(int startPosition, int newPosition){
    if (startPosition < orderList.size() && newPosition < orderList.size()){
        cout << "Order Moved to Position: " << newPosition <<endl;
    }
    else
    cout << "Invalid Order Movement in List" <<endl;
}

 //remove order from list
void OrderList::remove(Order order){
    cout <<order.getOrderID() << " order removed from list" << endl;
}

        
  
