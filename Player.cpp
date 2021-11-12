/**
 Part 2: Player.cpp
 */

#include "Player.h"
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

//Default constructor
Player::Player(){
    this->hand = new Hand();
    this->territories={};
    this->orders= new OrderList();
    this->name = "Anonymous";
    this->reinforcementPool = 50;
    this->willDrawCardAtTheEndOfTurn = false;
}

//Constructor
Player::Player (string name, Hand * hand, vector <Territory*> territories){
    this->name = name;
    this->hand = hand;
    this->territories = territories;
    this->orders= new OrderList();
    this->reinforcementPool = 50;
    this->willDrawCardAtTheEndOfTurn = false;
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
    this->willDrawCardAtTheEndOfTurn = p.willDrawCardAtTheEndOfTurn;
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
    this->willDrawCardAtTheEndOfTurn = p.willDrawCardAtTheEndOfTurn;
    return *this;
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

string Player::getName() {
    return name;
}

void Player::setReinforcementPool(int number) {
    reinforcementPool = number;
};

void Player::setWillDrawCard(bool value) {
    willDrawCardAtTheEndOfTurn = value;
};

void Player::addTerritory(Territory* t) {
    territories.push_back(t);
};

void Player::removeTerritory(Territory* t) {
    for (int i=0; i<territories.size(); i++) {
        if (territories[i] == t) {
            territories.erase(find(territories.begin(), territories.end(), t));
        }
    }
};

int Player::getReinforcementPool() {
    return reinforcementPool;
}

void Player::setPeacefulTerritories(vector<Territory*> v) {
    peacefulTerrtories = v;
};

//stream insertion operator
ostream& operator<<(ostream& out, const Player& p)
{
    out << "Player " << p.name<<" details:"<<endl ;
    out<< "Hand: "<< *p.hand <<endl;
    out<< "List of orders: "<< *p.orders <<endl;
    out<< "List of territories: ";
    for (auto territory : p.territories) {
        out << *territory << endl;
    }
    out<<endl;
    out << "Number of reinforcement armies: " << p.reinforcementPool << endl;
    return out;
}
