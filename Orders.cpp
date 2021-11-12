#include "Orders.h"
#include "Player.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

bool isTerritoryOwnedByPlayer(Player* p, Territory* territory) {
    vector <Territory*> territories = p->getTerritories();
    bool returnValue = false;
    for (auto t: territories) {
        if (t->territory_name == territory->territory_name) {
            returnValue = true;
        }
    }
    return returnValue;
};

// Order Class

int Order::currentId = 0;
// default constructor
Order::Order(): orderId(currentId++) {};

// parametrized constructor
Order::Order(Player* player) : orderId(currentId++) {
    this->orderIssuer = player;
};

Order::Order(const Order &o) {
    orderId = o.orderId;
    this->orderIssuer = new Player;
    *orderIssuer = *o.orderIssuer;
}

// assignment operator
Order& Order::operator= (const Order& order){
    this->orderId = order.orderId;
    this->orderIssuer = new Player;
    *orderIssuer = *order.orderIssuer;
    return *this;
};

void Order::setOrderIssuer(Player* player) {
    orderIssuer = player;
};

bool Order::validate() {
    return true;
};

void Order::execute(){
    if (validate()){
        cout <<"Order " << orderId << " executed"<< endl;
    } else {
        cout << "Order "<< orderId <<" invalid! Execution failed."<<endl;
    }
    Notify(this);
}

std::string Order::stringToLog(){
    cout<<"\nWriting executed Order to gamelog.txt file ..."<<endl;
    std::ofstream myfile;
    myfile.open ("gamelog.txt", std::ios_base::app);
    myfile <<"Order executed: ";
    myfile <<to_string(this->orderId)<<"\n";
    myfile <<"-------------------------------------\n";
    myfile.close();
    return to_string(this->orderId);
}

//Deploy Class
Deploy::Deploy() : Order() {}

//constructor
Deploy::Deploy(Player* player, Territory* territory, int number) : Order(player) {
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
    return isTerritoryOwnedByPlayer(orderIssuer, target) && orderIssuer->getReinforcementPool() > numberOfUnits;
};

void Deploy::execute() {
    Order::execute();
    if (validate()) {
        vector <Territory*> territories = orderIssuer->getTerritories();
        for (auto t: territories) {
            if (t->territory_name == target->territory_name) {
                orderIssuer->setReinforcementPool(orderIssuer->getReinforcementPool() - numberOfUnits);
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
Advance::Advance(Player* player, Territory* t1, Territory* t2, int number) : Order(player) {
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
    // TODO: modify territory class
    // hard code to true for now
    bool areTerritoriesAdjacent = true;

    return isSourceOwnedByIssuer && areTerritoriesAdjacent;
};

void Advance::execute() {
    Order::execute();
    if (validate()) {
        // TODO: complete this code
        cout << "Advance order executed" << endl;
    } else {
        cout << "Advance order invalid" << endl;
    }
};

//Airlift Class
//default constructor
Airlift::Airlift():Order(){};

//constructor
Airlift::Airlift(Player* player, Territory* t1, Territory* t2, int number) : Order(player){
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

void Airlift::setFrom(Territory* t) {
    from = t;
};

void Airlift::setTarget(Territory* t) {
    target = t;
};

void Airlift::setNumberOfUnits(int n) {
    numberOfUnits = n;
};

bool Airlift::validate() {
    return isTerritoryOwnedByPlayer(orderIssuer, from) && isTerritoryOwnedByPlayer(orderIssuer, target);
};

void Airlift::execute(){
    Order::execute();
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
Bomb::Bomb(Player* player, Territory* t1, Territory* t2) : Order(player){
    this->target = new Territory;
    *target = *t2;
}

//copy constructor
Bomb::Bomb(const Bomb& b) : Order(b){
    this->target = new Territory;
    *target = *b.target;
}

//assignment operator
Bomb& Bomb::operator=(const Bomb& b){
    Order::operator= (b);
    this->target = new Territory;
    *target = *b.target;
    return *this;
}

void Bomb::setTarget(Territory* t) {
    target = t;
};

bool Bomb::validate(){
    // TODO: modify territory class
    // hard code to true for now
    bool areTerritoriesAdjacent = true;
    return !isTerritoryOwnedByPlayer(orderIssuer, target) && areTerritoriesAdjacent;
};

void Bomb::execute(){
    Order::execute();
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
Blockade::Blockade(Player* player, Territory* territory) : Order(player) {
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

void Blockade::setTarget(Territory* t) {
    target = t;
};

bool Blockade::validate(){
    return isTerritoryOwnedByPlayer(orderIssuer, target);
};

void Blockade::execute(){
    Order::execute();
    if (validate()) {
        target->setArmy(target->army_nb *2);
        // TODO: transfer ownership to neutral
        cout << "Blockade order executed" << endl;
    } else {
        cout << "Blockade order invalid" << endl;
    }
}

//Negotiate Class
//default constructor
Negotiate::Negotiate():Order() {};

//constructor
Negotiate::Negotiate(Player* player, Player* target) : Order(player) {
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
    if (target->getName() == orderIssuer->getName()) {
        return false;
    }
    return true;
};

void Negotiate::execute(){
    Order::execute();
    if (validate()) {
        // TODO: complete this code
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
    Notify(this);
}

//move order inside orderList
void OrderList::move(Order* order, int newPosition){
    cout<<"Move order "<<order->orderId<<" to index "<<newPosition<<endl;
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
    cout <<"Order "<< order->orderId <<" removed from list" << endl;
}

std::string OrderList::stringToLog(){
    cout<<"\nWriting issued Order to gamelog.txt file ..."<<endl;
    std::ofstream myfile;
    myfile.open ("gamelog.txt", std::ios_base::app);
    myfile <<"Order issued: ";
    std::string orderIssued;
    for(int i=0; i<orderList.size();i++){
        orderIssued=+orderList[i]->orderId;
        myfile <<orderList[i]->orderId<<"\n";
    }
    myfile <<"-------------------------------------\n";
    myfile.close();
    return orderIssued;
}

//stream insertion operators
ostream& operator<<(ostream& out, const OrderList& o)
{
    out << "OrderList has the following orders:"<<endl ;
    for(int i =0; i<o.orderList.size();i++){
        out << endl ;
        out<< *o.orderList[i] <<endl;
    }
    return out;
}

ostream& operator<<(ostream& out, const Order& o)
{
    out << "Order:"<<endl ;
    out << "-------------------------------"<<endl;
    out << "ID: "<< o.orderId << endl;
    out<<"Order Issuer: "<< o.orderIssuer->getName();
    return out;
}

ostream& operator <<(ostream &out, const Deploy &order) {
    out << static_cast<const Order&>(order) << endl;
    out << "Target: " << order.target->territory_name << endl;
    out << "Number of armies: " << order.numberOfUnits << endl;
    return out;
}

ostream& operator <<(ostream &out, const Advance &order) {
    out << static_cast<const Order&>(order) << endl;
    out << "From: " << order.from->territory_name << endl;
    out << "Target: " << order.target->territory_name << endl;
    out << "Number of armies: " << order.numberOfUnits << endl;
    return out;
}

ostream& operator <<(ostream &out, const Airlift &order) {
    out << static_cast<const Order&>(order) << endl;
    out << "From: " << order.from->territory_name << endl;
    out << "Target: " << order.target->territory_name << endl;
    out << "Number of armies: " << order.numberOfUnits << endl;
    return out;
}

ostream& operator <<(ostream &out, const Bomb &order) {
    out << static_cast<const Order&>(order) << endl;
    out << "Target: " << order.target->territory_name << endl;
    return out;
}

ostream& operator <<(ostream &out, const Blockade &order) {
    out << static_cast<const Order&>(order) << endl;
    out << "Target: " << order.target->territory_name << endl;
    return out;
}

ostream& operator <<(ostream &out, const Negotiate &order) {
    out << static_cast<const Order&>(order) << endl;
    out << "Targetted player: " << order.target->getName() << endl;
    return out;
}
