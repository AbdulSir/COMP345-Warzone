//
//  Player.cpp
//  Comp 345 a1
//
//  Created by Beatrice Cobo on 2021-09-28.
//

#include "Player.h"
#include <iostream>
#include <string>

Order::Order(){
    
}

//Default constructor
Player::Player(){
    this->hand = new Hand();
    //this->territories;
    //this->orders;
    this->name = "";
    cout << "Player created inside default constructor" << endl;
}

//Constructor
Player::Player (string name, Hand * hand, list <Territory*> territories){
    this->name = name;
    this->hand = hand;
    this->territories = territories;
    cout << "Player " << name << " created inside constructor" << endl;
}

//Copy constructor
Player::Player(const Player& p){
  cout << "Inside copy constructor of Player" << endl;
    this->name = p.name;
    this->hand = p.hand;
    this->territories = p.territories;
    this->orders = p.orders;
}

list <Territory*> Player::toDefend(){
    cout << "Inside toDefend of Player" << endl;
    list<Territory*> t;
    return t;
}

list <Territory*> Player::toAttack(){
    cout << "Inside toAttack of Player" << endl;
    list<Territory*> t;
    cout << "sizeof "<< sizeof(t)<<endl;
    return t;
}

list <Order*> Player::issueOrder(){
    cout << "Inside issueOrder of Player" << endl;
    Order * order = new Order();
    this->orders.push_back(order);
    delete order;
    order = NULL;
    return orders;
}

//assignment operator
Player& Player::operator=(const Player& p){
  cout << "Inside operator = of Player" << endl;
  name = p.name;
  return *this;
}

//stream insertion operator
ostream& operator<<(ostream& ostmr, const Player& p)
{
    return ostmr << "Player " << p.name;
}

/*istream& operator>>(istream& istmr, const Player& p)
{
    return istmr  >> p.name;
}*/

