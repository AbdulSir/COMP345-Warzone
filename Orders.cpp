#include "Orders.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Player.h"

using namespace std;

bool isTerritoryOwnedByPlayer(Player* p, Territory* t) {
    vector <Territory*> territories = p->getTerritories();
    bool returnValue = false;
    for (auto t: territories) {
        if (t->territory_name == t->territory_name) {
            returnValue = true;
        }
    }
    return returnValue;
};

// Order Class
// default constructor
Order::Order() {
    cout << "Empty order" << endl;
};

// parametrized constructor
Order::Order(string orderID, Player* player){
    this->orderID = orderID;
    this->orderIssuer = player;
};

Order::Order(const Order &o) {
    orderID = o.orderID;
    this->orderIssuer = new Player;
    *orderIssuer = *o.orderIssuer;
}

// assignment operator
Order& Order::operator= (const Order& order){
    this->orderID = order.orderID;
    this->orderIssuer = new Player;
    *orderIssuer = *order.orderIssuer;
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
Deploy::Deploy(string orderID, Player* player, Territory* territory, int number) : Order(orderID, player) {
    this->target = new Territory;
    *target = *territory;
    numberOfUnits = number;
}

//copy constructor
Deploy::Deploy(const Deploy& d) : Order(d) {
    this->target = new Territory;
    *target = *d.target;
    numberOfUnits = d.numberOfUnits;
}

//assignment operator
Deploy& Deploy::operator=(const Deploy& d) {
    Order::operator= (d);
    this->target = new Territory;
    *target = *d.target;
    numberOfUnits = d.numberOfUnits;
    return *this;
}

bool Deploy::validate() {
    return isTerritoryOwnedByPlayer(orderIssuer, target);
};

void Deploy::execute() {
    if (validate()) {
        vector <Territory*> territories = orderIssuer->getTerritories();
        for (auto t: territories) {
            if (t->territory_name == target->territory_name) {
                t->setArmy(target->army_nb + numberOfUnits);
            }
        }
        cout << "Deploy order executed" << endl;
    } else {
        cout << "Deploy order invalid" << endl;
    }
}

//Advance Class
//default constructor
Advance::Advance() : Order() {};

//constructor
Advance::Advance(string orderID, Player* player, Territory* t1, Territory* t2, int number) : Order(orderID, player) {
    this->from = new Territory;
    *from = *t1;
    this->target = new Territory;
    *target = *t2;
    numberOfUnits = number;
}

//copy constructor
Advance::Advance(const Advance& a) : Order(a){
    this->from = new Territory;
    *target = *a.from;
    this->target = new Territory;
    *target = *a.target;
    numberOfUnits = a.numberOfUnits;
}

//assignment operator
Advance& Advance::operator=(const Advance& a){
    Order::operator= (a);
    this->from = new Territory;
    *from = *a.from;
    this->target = new Territory;
    *target = *a.target;
    numberOfUnits = a.numberOfUnits;
    return *this;
}

bool Advance::validate() {
    bool isSourceOwnedByIssuer = isTerritoryOwnedByPlayer(orderIssuer, from);
    // hard code true for now
    bool areTerritoriesAdjacent = true;

    return isSourceOwnedByIssuer && areTerritoriesAdjacent;
};

void Advance::execute() {
    if (validate()) {
        // Incomplete, need to write order execution
        cout << "Advance order executed" << endl;
    } else {
        cout << "Advance order invalid" << endl;
    }
};

//Airlift Class
//default constructor
Airlift::Airlift():Order(){};

//constructor
Airlift::Airlift(string orderID, Player* player, Territory* t1, Territory* t2, int number) : Order(orderID, player){
    this->from = new Territory;
    *from = *t1;
    this->target = new Territory;
    *target = *t2;
    numberOfUnits = number;
}

//copy constructor
Airlift::Airlift(const Airlift& a) : Order(a) {
    this->from = new Territory;
    *target = *a.from;
    this->target = new Territory;
    *target = *a.target;
    numberOfUnits = a.numberOfUnits;
}

//assignment operator
Airlift& Airlift::operator=(const Airlift& a) {
    Order::operator= (a);
    this->from = new Territory;
    *from = *a.from;
    this->target = new Territory;
    *target = *a.target;
    numberOfUnits = a.numberOfUnits;
    return *this;
}

bool Airlift::validate() {
    return isTerritoryOwnedByPlayer(orderIssuer, from) && isTerritoryOwnedByPlayer(orderIssuer, target);
};

void Airlift::execute(){
    if (validate()) {
        from->setArmy(from->army_nb - numberOfUnits);
        target->setArmy(target->army_nb + numberOfUnits);
        cout << "Airlife order executed" << endl;
    } else {
        cout << "Airlife order invalid" << endl;
    }
}

//Bomb Class
//default constructor
Bomb::Bomb():Order() {};

//constructor
Bomb::Bomb(string orderID, Player* player, Territory* t1, Territory* t2) : Order(orderID, player){
    this->from = new Territory;
    *from = *t1;
    this->target = new Territory;
    *target = *t2;
}

//copy constructor
Bomb::Bomb(const Bomb& b) : Order(b){
    this->from = new Territory;
    *target = *b.from;
    this->target = new Territory;
    *target = *b.target;
}

//assignment operator
Bomb& Bomb::operator=(const Bomb& b){
    Order::operator= (b);
    this->from = new Territory;
    *from = *b.from;
    this->target = new Territory;
    *target = *b.target;
    return *this;
}

bool Bomb::validate(){
    // hard code to true for now
    bool areTerritoriesAdjacent = true;
    return !isTerritoryOwnedByPlayer(orderIssuer, target) && areTerritoriesAdjacent;
};

void Bomb::execute(){
    if (validate()) {
        target->setArmy(target->army_nb / 2);
        cout << "Bomb order executed" << endl;
    } else {
        cout << "Bomb order invalid" << endl;
    }
}

//Blockade Class
//default constructor
Blockade::Blockade():Order() {};

//constructor
Blockade::Blockade(string orderID, Player* player, Territory* territory) : Order(orderID, player) {
    this->target = territory;
}

//copy constructor
Blockade::Blockade(const Blockade& bl) : Order(bl){
    this->target = new Territory;
    *target = *bl.target;
}

//assignment operator
Blockade& Blockade::operator=(const Blockade& b){
    Order::operator= (b);
    this->target = new Territory;
    *target = *b.target;
    return *this;
}

bool Blockade::validate(){
    return !isTerritoryOwnedByPlayer(orderIssuer, target);
};

void Blockade::execute(){
    if (validate()) {
        target->setArmy(target->army_nb *2);
        // transfer ownership to neutral
        cout << "Blockade order executed" << endl;
    } else {
        cout << "Blockade order invalid" << endl;
    }
}


//Negotiate Class
//default constructor
Negotiate::Negotiate():Order() {};

//constructor
Negotiate::Negotiate(string orderID, Player* player, Player* target) : Order(orderID, player) {
    this->target = target;
}

//copy constructor
Negotiate::Negotiate(const Negotiate& n) : Order(n){
    this->target = new Player;
    *target = *n.target;
}

//assignment operator
Negotiate& Negotiate::operator=(const Negotiate& n){
    Order::operator= (n);
    this->target = new Player;
    *target = *n.target;
    return *this;
}

bool Negotiate::validate(){
    if (target->getName() == orderIssuer->getName) {
        return false;
    }
    return true;
};

void Negotiate::execute(){
    if (validate()) {
        // any attack that may be declared between territories of the player issuing the negotiate order and the target player will result in invalid order
        cout << "Negotiate order executed" << endl;
    } else {
        cout << "Negotiate order invalid" << endl;
    }
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
