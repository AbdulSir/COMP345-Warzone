#include "Orders.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//Order Class

//default constructor
Order::Order(){
    this->orderID = "";
    this->description = "";
    this->effect = "";
    cout << "Default Order: " << "-" << " Created in Base Class" <<endl;
};

//parametrized constructor
Order::Order(string orderID, string description, string effect){
    this->orderID = orderID;
    this->effect = effect;
    this->description=description;
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

//@return string orderID
string Order::getOrderID(){
    return orderID;
}

//@return string description
string Order::getDescription(){
    return description;
};

//@return string description
string Order::getEffect(){
    return effect;
};

//set effect
void Order::setEffect(string e){
    effect=e;
};

bool Order::validate(){
    return (description == "" || description == "deploy" || description == "advance" || description == "bomb" || description == "blockade" || description == "airlift" || description == "negotiate");
};

//execute order - for each Order subclass
void Order::execute(){
        if (validate()){
            cout <<"Order "<< orderID <<" executed"<<endl;
            effect="*default effect*";
            
        }
        else
            cout << "Order "<< orderID <<" invalid! Execution failed."<<endl;
}

//stream insertion operator
ostream& operator<<(ostream& out, const Order& o)
{
    out << "Order:"<<endl ;
    out << "-------------------------------"<<endl;
    out<<"Order "<<endl;
    out<<"ID: "<<o.orderID<<endl;
    out<<"Description: "<<o.description<<endl;
    out<<"Effect: "<<o.effect<<endl;
    out<<endl;
    return out;
}


//Deploy Class

//default constructor
Deploy::Deploy(): Order(){
    cout << "Default Deploy: " << "-" << " Created in Subclass" <<endl;
};

//constructor
Deploy::Deploy(string orderID,string description,  string effect) : Order(orderID,description,effect){
    cout << "Deploy: " << orderID << " Created in Subclass" <<endl;
}

//copy constructor
Deploy::Deploy(const Deploy& d) : Order(d){
  cout << "Inside copy constructor of Deploy" << endl;
}

//assignment operator
Deploy& Deploy::operator=(const Deploy& d){
  cout << "Inside operator = of Deploy" << endl;
  Order::operator= (d);
  return *this;
}

//return true if Deploy is valid else false
bool Deploy::validate(){
    return (getDescription() == "deploy");
};

//check if Deploy is valid and if valid set effect
void Deploy::execute(){
        if (validate()){
            cout << "Deploy order "<< getOrderID() <<" executed"<<endl;
            setEffect("Place some armies on one of the current player’s territories. ");
            
        }
        else
            cout << "Deploy order "<< getOrderID() <<" invalid! Execution failed."<<endl;
}



//Advance Class

//default constructor
Advance::Advance():Order(){
    cout << "Default Advance: " << "-" << " Created in Subclass" <<endl;
};

//constructor
Advance::Advance(string orderID,string description, string effect) : Order(orderID,description,effect){
    cout << "Advance: " << orderID << " Created in Subclass" <<endl;
}

//copy constructor
Advance::Advance(const Advance& a) : Order(a){
  cout << "Inside copy constructor of Advance" << endl;
}

//assignment operator
Advance& Advance::operator=(const Advance& ad){
  cout << "Inside operator = of Advance" << endl;
  Order::operator= (ad);
  return *this;
}

//return true if Advance is valid else false
bool Advance::validate(){
    return (getDescription() == "advance");
};

//check if Advance is valid and if valid set effect
void Advance::execute(){
    if (validate()){
        cout << "Advance order "<< getOrderID() <<" executed"<<endl;
        setEffect("Move some armies from one of the current player’s territories (source) to an adjacent  territory(target).");
    }
    else
        cout << "Not executed because advance order"<<endl;
};


//Bomb Class

//default constructor
Bomb::Bomb():Order(){
    cout << "Default Bomb: " << "-" << " Created in Subclass" <<endl;
};

//constructor
Bomb::Bomb(string orderID,string description,string effect) : Order(orderID,description,effect){
    cout << "Bomb: " << orderID << " Created in Subclass" <<endl;
}

//copy constructor
Bomb::Bomb(const Bomb& b) : Order(b){
  cout << "Inside copy constructor of Bomb" << endl;
}

//assignment operator
Bomb& Bomb::operator=(const Bomb& b){
  cout << "Inside operator = of Bomb" << endl;
  Order::operator= (b);
  return *this;
}

//return true if Bomb is valid else false
bool Bomb::validate(){
    return (getDescription() == "bomb");
};

//check if Bomb is valid and if valid set effect
void Bomb::execute(){
        if (validate()){
            cout << "Bomb order "<< getOrderID() <<" executed"<<endl;
            setEffect("Target country loses half of their army units.");
            
        }
        else
            cout << "Bomb order "<< getOrderID() <<" invalid! Execution failed."<<endl;
}


//Blockade Class

//default constructor
Blockade::Blockade():Order(){
    cout << "Default Blockade: " << "-" << " Created in Subclass" <<endl;
};

//constructor
Blockade::Blockade(string orderID,string description, string effect) : Order(orderID,description,effect){
    cout << "Blockade: " << orderID << " Created in Subclass" <<endl;
}

//copy constructor
Blockade::Blockade(const Blockade& bl) : Order(bl){
  cout << "Inside copy constructor of Blockade" << endl;
}

//assignment operator
Blockade& Blockade::operator=(const Blockade& bl){
  cout << "Inside operator = of Blockade" << endl;
  Order::operator= (bl);
  return *this;
}

//return true if Blockade is valid else false
bool Blockade::validate(){
    return (getDescription() == "blockade");
};

//check if Blockade is valid and if valid set effect
void Blockade::execute(){
        if (validate()){
            cout << "Blockade order executed"<<endl;
            setEffect("Target territory’s army units count is tripled, and the territory becomes neutral.");
            
        }
        else
            cout << "Blockade order "<< getOrderID() <<" invalid! Execution failed."<<endl;
}


//Airlift Class

//default constructor
Airlift::Airlift():Order(){
    cout << "Default Airlift: " << "-" << " Created in Subclass" <<endl;
}

//constructor
Airlift::Airlift(string orderID,string description, string effect) : Order(orderID,description,effect){
    cout << "Airlift: " << orderID << " Created in Subclass" <<endl;
}

//copy constructor
Airlift::Airlift(const Airlift& a) : Order(a){
  cout << "Inside copy constructor of Airlift" << endl;
}

//assignment operator
Airlift& Airlift::operator=(const Airlift& a){
  cout << "Inside operator = of Airlift" << endl;
  Order::operator= (a);
  return *this;
}

//return true if Airlift is valid else false
bool Airlift::validate(){
    return (getDescription() == "airlift");
};

//check if Airlift is valid and if valid set effect
void Airlift::execute(){
        if (validate()){
            cout << "Airlift order executed"<<endl;
            setEffect("Move any number of army units from one of your territories to another territory, even if they are not adjacent.");
            
        }
        else
            cout << "Airlift order "<< getOrderID() <<" invalid! Execution failed."<<endl;
}


//Negotiate Class

//default constructor
Negotiate::Negotiate():Order(){
    cout << "Default Negotiate: " << "-" << " Created in Subclass" <<endl;
};

//constructor
Negotiate::Negotiate(string orderID,string description, string effect) : Order(orderID,description,effect){
    cout << "Negotiate: " << orderID << " Created in Subclass" <<endl;
}

//copy constructor
Negotiate::Negotiate(const Negotiate& n) : Order(n){
  cout << "Inside copy constructor of Negotiate" << endl;
}

//assignment operator
Negotiate& Negotiate::operator=(const Negotiate& n){
  cout << "Inside operator = of Negotiate" << endl;
  Order::operator= (n);
  return *this;
}

//return true if negotiate is valid else false
bool Negotiate::validate(){
    return (getDescription() == "negotiate");
};

//check if negotiate is valid and if valid set effect
void Negotiate::execute(){
        if (validate()){
            cout << "Negotiate order "<< getOrderID() <<" executed"<<endl;
            setEffect("Prevent attacks between the current player and another player until the end of the turn.");
            
        }
        else
            cout << "Negotiate order "<< getOrderID() <<" invalid! Execution failed."<<endl;
}


//OrderList Class

//default constructor
OrderList::OrderList(){
    this->orderList={};
};

//copy constructor
OrderList::OrderList(const OrderList& obj){
    vector<Order*> temp_o(obj.orderList.size());
    this->orderList= temp_o;
    for (int i=0; i<obj.orderList.size(); i++)
        orderList[i] = new Order(*obj.orderList[i]);
};

//destructor
OrderList::~OrderList()
{
    for (int i=0; i<orderList.size(); i++){
        delete orderList[i];
    }
}

//assignment operator
OrderList& OrderList::operator= (const OrderList& o){
    vector<Order*> temp_o(o.orderList.size());
    this->orderList= temp_o;
    for (int i=0; i<o.orderList.size(); i++)
        orderList[i] = new Order(*o.orderList[i]);
    return *this;
};

//add order to orderList
void OrderList::addOrder(Order* order){
   orderList.push_back(order);
}

//stream insertion operator
ostream& operator<<(ostream& out, const OrderList& o)
{
    out << "OrderList has the following orders:"<<endl ;
    out << "-------------------------------"<<endl;
    for(int i =0; i<o.orderList.size();i++){
        out<<"Order "<<endl;
        out<<"ID: "<<o.orderList[i]->getOrderID()<<endl;
        out<<"Description: "<<o.orderList[i]->getDescription()<<endl;
        out<<"Effect: "<<o.orderList[i]->getEffect()<<endl;
        out<<endl;
    }
    return out;
}

// stream extraction operator
istream& operator>>(istream &in, OrderList& o) {
    return in;
}

//move order inside orderList
void OrderList::move(Order* order, int newPosition){
    cout<<"Move order "<<order->getOrderID()<<" to index "<<newPosition<<endl;
    //remove order from list
    for(int i=0; i<orderList.size();i++){
        if(orderList[i]==order){
            orderList.erase(find(orderList.begin(),orderList.end(),order));
        }
    }
    orderList.emplace(orderList.begin()+newPosition, order); //insert object to the desired position
}

//remove order from orderList
void OrderList::remove(Order* order){
    for(int i=0; i<orderList.size();i++){
        if(orderList[i]==order){
            orderList.erase(find(orderList.begin(),orderList.end(),order));
        }
    }
    cout <<"Order "<< order->getOrderID()<<" removed from list" << endl;
}


        
  

