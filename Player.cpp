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
}

Player::Player(string name){
    this->hand = new Hand();
    this->territories={};
    this->orders= new OrderList();
    this->name = name;
    this->reinforcementPool = 50;
    this->willDrawCardAtTheEndOfTurn = false;
}

//Constructor
Player::Player (string name, Hand * hand, vector <Territory*> territories){
    this->name = name;
    this->hand = hand;
    this->territories = territories;
    this->defendList = territories;
    this->attackList = {};
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
    Territory * tt1=new Territory("United Kingdom",0,5);
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

    cout << "Inside issue order of Player" << endl;
   int currentReinforcements = this.getReinforcementPool();
    if (this.getReinforcementPool() > 0){

        cout << "Reinforcements found, creating deploy order" << endl;
        Deploy deployOrder = new Deploy(5);
        currentReinforcements -= 5;
        this->orders->orderList.push_back(deployOrder);

    } 
    //choose to advance or play card
        if (this.toAttack.size()>0){
            Advance advanceOrder = new Advance();
            this->orders->orderList.push_back(deployOrder);
        }
        if (this.hand->handDeck->size()>0){
            
            this->orders->orderList.push_back();
        }
   


/*
    switch(currentOrder) {
        case "deploy":
           // Deploy deployOrder = new Deploy();
            Deploy order = new Deploy();

    break;
         case "advance":
           // Advance advanceOrder = new Advance();
           Advance order = new Advance();
    break;
        case "airlift":
           //Airlift airliftOrder = new Airlift();
           Airlift order = new Airlift();
    break;
         case "bomb":
           // Bomb bombOrder = new Bomb();
           Bomb order = new Bomb();
    break;
        case "blockade":
           // Blockade blockadeOrder = new Blockade();
           Blockade order = new Blockade();
    break;
         case "negotiate":
          //  Negotiate negotiateOrder = name Negotiate();
          Negotiate order = name Negotiate();
    break;
        default:
            break;
}
*/
    
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

Hand* Player::getHand()
{
    return hand;
}

void Player::setReinforcementPool(int number) {
    reinforcementPool = number;
};

void Player::setName(string name)
{
    this->name = name;
}
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

void Player::setTerritories(vector <Territory*> v) {
    territories = v;
};

vector <Territory*> Player::getPeacefulTerritories() {
    return peacefulTerrtories;
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
