#include "Orders.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Player.h"

using namespace std;

// Order Class
// default constructor
Order::Order() {
    cout << "Empty order" << endl;
};

// parametrized constructor
Order::Order(string orderID){
    this->orderID = orderID;
};

Order::Order(const Order &o) {
    orderID = o.orderID;
}

// assignment operator
Order& Order::operator= (const Order& order){
    this->orderID = order.orderID;
    return *this;
};

// @return string orderID
string Order::getOrderID(){
    return orderID;
};

bool Order::validate() {
    return true;
};

void Order::execute(){
    if (validate()){
        cout <<"Order " << orderID << " executed"<< endl;
    } else {
        cout << "Order "<< orderID <<" invalid! Execution failed."<<endl;
    }
}

//stream insertion operator
ostream& operator<<(ostream& out, const Order& o)
{
    out << "Order:"<<endl ;
    out << "-------------------------------"<<endl;
    out << "Order "<< endl;
    out << "ID: "<< o.orderID << endl;
    out << endl;
    return out;
}


//Deploy Class
Deploy::Deploy() : Order() {}

//constructor
Deploy::Deploy(string orderID, Player* player, Territory* territory, int number_of_army) : Order(orderID) {
    this->orderPlayer = new Player;
    *orderPlayer = *player;
    this->targetTerritory = new Territory;
    *targetTerritory = *territory;
    number_of_deployed_army = number_of_army;
}

//copy constructor
Deploy::Deploy(const Deploy& d) : Order(d) {
    this->orderPlayer = new Player;
    *orderPlayer = *d.orderPlayer;
    this->targetTerritory = new Territory;
    *targetTerritory = *d.targetTerritory;
    number_of_deployed_army = d.number_of_deployed_army;
}

//assignment operator
Deploy& Deploy::operator=(const Deploy& d) {
    Order::operator= (d);
    this->orderPlayer = new Player;
    *orderPlayer = *d.orderPlayer;
    this->targetTerritory = new Territory;
    *targetTerritory = *d.targetTerritory;
    number_of_deployed_army = d.number_of_deployed_army;
    return *this;
}

bool Deploy::validate() {
    vector <Territory*> territories = orderPlayer->getTerritories();
    bool isValidateOrder = false;
    for (auto t: territories) {
        cout << t->territory_name << endl;
        if (t->territory_name == targetTerritory->territory_name) {
            isValidateOrder = true;
        }
    }
    return isValidateOrder;
};

void Deploy::execute() {
    if (validate()) {
        vector <Territory*> territories = orderPlayer->getTerritories();
        for (auto t: territories) {
            if (t->territory_name == targetTerritory->territory_name) {
                t->addArmy(number_of_deployed_army);
            }
        }
        cout << "Deploy order executed" << endl;
    } else {
        cout << "Deploy order invalid" << endl;
    }
}

/*
//Advance Class
//default constructor
Advance::Advance() : Order() {};

//constructor
Advance::Advance(string orderID) : Order(orderID) {

}

//copy constructor
Advance::Advance(const Advance& a) : Order(a){

}

//assignment operator
Advance& Advance::operator=(const Advance& ad){
  Order::operator= (ad);
  return *this;
}

bool Advance::validate() {

};

void Advance::execute() {

};


//Bomb Class
//default constructor
Bomb::Bomb():Order() {};

//constructor
Bomb::Bomb(string orderID) : Order(orderID){

}

//copy constructor
Bomb::Bomb(const Bomb& b) : Order(b){

}

//assignment operator
Bomb& Bomb::operator=(const Bomb& b){
  Order::operator= (b);
  return *this;
}

bool Bomb::validate(){

};

void Bomb::execute(){

}


//Blockade Class
//default constructor
Blockade::Blockade():Order(){

};

//constructor
Blockade::Blockade(string orderID) : Order(orderID) {

}

//copy constructor
Blockade::Blockade(const Blockade& bl) : Order(bl){

}

//assignment operator
Blockade& Blockade::operator=(const Blockade& bl){
  Order::operator= (bl);
  return *this;
}

bool Blockade::validate(){

};

void Blockade::execute(){

}


//Airlift Class
//default constructor
Airlift::Airlift():Order(){

}

//constructor
Airlift::Airlift(string orderID) : Order(orderID){

}

//copy constructor
Airlift::Airlift(const Airlift& a) : Order(a) {

}

//assignment operator
Airlift& Airlift::operator=(const Airlift& a) {
  Order::operator= (a);
  return *this;
}

bool Airlift::validate() {

};

void Airlift::execute(){

}


//Negotiate Class
//default constructor
Negotiate::Negotiate():Order(){

};

//constructor
Negotiate::Negotiate(string orderID) : Order(orderID){

}

//copy constructor
Negotiate::Negotiate(const Negotiate& n) : Order(n){

}

//assignment operator
Negotiate& Negotiate::operator=(const Negotiate& n){

  Order::operator= (n);
  return *this;
}

bool Negotiate::validate(){

};

void Negotiate::execute(){

}

*/

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
        out<<endl;
    }
    return out;
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
