/**
 Part 2: Player.cpp
 */

#include "Player.h"
#include <iostream>
#include <ostream>
#include <string>
using namespace std;

Territory::Territory() {};
//Territorry dummy copy constructor
Territory::Territory (const Territory &t1){
    this->territory_name = t1.territory_name;
    this->continent_ref=t1.continent_ref;
    this->army_nb=t1.army_nb;
}

//Territorry dummy constructor
Territory::Territory(string terr_name, int contin_ref, int num_of_armies){
    this->territory_name=terr_name;
    this->continent_ref=contin_ref;
    this->army_nb=num_of_armies;
}

Territory& Territory::operator=(const Territory& t) {
    territory_name = t.territory_name;
    continent_ref = t.continent_ref;
    army_nb = t.army_nb;
    return *this;
}

void Territory::setArmy(int numberOfArmy) {
    army_nb = numberOfArmy;
}

//Default constructor
Player::Player(){
    this->hand = new Hand();
    this->territories={};
    this->orders= new OrderList();
    this->name = "Anonymous";
}

//Constructor
Player::Player (string name, Hand * hand, vector <Territory*> territories){
    this->name = name;
    this->hand = hand;
    this->territories = territories;
    this->orders= new OrderList();
}

//Copy constructor
Player::Player(const Player& p){
    this->name = p.name;
    this->hand = new Hand;
    *hand= *p.hand;
    this->orders = new OrderList;
    *orders= *p.orders;
    vector<Territory*> temp_t(p.territories.size());
    this->territories= temp_t;
    for (int i=0; i<p.territories.size(); i++)
        territories[i] = new Territory(*p.territories[i]);
}

//Destructor
Player::~Player()
{
    delete orders;
    delete hand;
    for (int i=0; i<territories.size(); i++){
        delete territories[i];
    }
}

//assignment operator
Player& Player::operator=(const Player& p){
    this->name = p.name;
    this->hand = new Hand();
    *hand = *p.hand;
    this->orders = new OrderList();
    *orders = *p.orders;
    vector<Territory*> temp_t(p.territories.size());
    this->territories= temp_t;
    for (int i=0; i<p.territories.size(); i++)
        territories[i] = new Territory(*p.territories[i]);
    return *this;
}

//stream insertion operator
ostream& operator<<(ostream& out, const Player& p)
{
    out << "Player " << p.name<<" details:"<<endl ;
    out << "-----------------------"<<endl;
    out<< "Hand: "<<p.hand<<endl;
    out<< "List of orders: "<<p.orders<<endl;
    out<< "List of territories: ";
    string separator;
    for (auto territory : p.territories) {
        out << separator << territory->territory_name;
        separator = ", ";
    }
    out<<endl;
    return out;
}

// stream extraction operator
istream& operator>>(istream &in, Player& p) {
    cout << "Enter Player Name ";
    in >> p.name;
    return in;
}

vector <Territory*> Player::toDefend(){
    cout << "Inside toDefend of Player" << endl;
    Territory * tt1=new Territory("United Kingdome",0,5);
    Territory * tt2=new Territory("Ireland",0,5);
    vector<Territory*> t={tt1,tt2};
    return t;
}

vector <Territory*> Player::toAttack(){
    cout << "Inside toAttack of Player" << endl;
    Territory * tt=new Territory("France",0,5);
    vector<Territory*> t={tt};
    return t;
}

void Player::issueOrder(){
    cout << "Inside issueOrder of Player" << endl;
    Order * order = new Order();
    this->orders->orderList.push_back(order);
}

vector <Territory*> Player::getTerritories() {
    return this->territories;
}

OrderList* Player::getOrders(){
    return orders;
}

