#include "PlayerStrategies.h"
#include "Orders.h"
#include <iostream>
#include <string>
using namespace std;

PlayerStrategy::PlayerStrategy(Player* p) {
    this->p = p;
}
PlayerStrategy::~PlayerStrategy(){
    delete p;
}

PlayerStrategy::PlayerStrategy(const PlayerStrategy &p){
    this->p = new Player(p);
}

Neutral::Neutral(Player* p): PlayerStrategy(p) {
    isAttacked = false;
}

Neutral::Neutral(const Neutral &n):PlayerStrategy(n) {
}

void Neutral::issueOrder() {
    if (isAttacked) {
        Aggressive::issueOrder();
    }
}

void Neutral::toDefend() {
    this->isAttacked = true;
    if (isAttacked) {
        Aggressive::toDefend();
    }
}

void Neutral::toAttack() {
    if (isAttacked) {
        Aggressive::toAttack();
    }
}

Cheater::Cheater(Player* p): PlayerStrategy(p) {}

Cheater::Cheater(const Cheater &c):PlayerStrategy(c) {
}

void Cheater::issueOrder() {

}

void Cheater::toDefend() {

}

void Cheater::toAttack() {

}

Human::Human(Player* p): PlayerStrategy(p) {}
Human::Human(const Human &h):PlayerStrategy(h) {
}

void Human::issueOrder() {
    cout << "Which order would you like to execute" << endl;
    string command;
    cin >> command;
    switch(command) {
        case "Deploy":
            string territoryName;
            int armyNumber;
            cout << "Which territory would you like to deploy" << endl;
            cin >> territoryName;
            cout << "How many armies would you like to deploy";
            cin >> armyNumber;
            for (auto t: p->getTerritories()) {
                if (t->getName() == territoryName) {
                    p->getOrders()->addOrder(new Deploy(p, t, armyNumber))
                }
            }
            break;
        case "Advance":
            break;
        case "Airlift":
            break;
        case "Bomb":
            break;
        case "Blockade":
            break;
        case "Negotiate":
            break;
    }
}

void Human::toDefend() {

}

void Human::toAttack() {

}

Aggressive::Aggressive(Player* p): PlayerStrategy(p) {}
Aggressive::Aggressive(const Aggressive &a):PlayerStrategy(a) {
}

Benevolent::Benevolent(Player* p): PlayerStrategy(p) {}
Benevolent::Benevolent(const Benevolent &b):PlayerStrategy(b) {
}

ostream& operator<< (ostream &out, const PlayerStrategy& p) {
    out << "Player strategy: default" << endl;
    out << "Player: " << p.p->getName() << endl;
    return out;
}

ostream& operator<< (ostream &out, const Neutral& p) {
    out << "Player strategy: Neutral" << endl;
    out << "Player: " << p.p->getName() << endl;
    return out;
}

ostream& operator<< (ostream &out, const Cheater& p) {
    out << "Player strategy: Cheater" << endl;
    out << "Player: " << p.p->getName() << endl;
    return out;
}

ostream& operator<< (ostream &out, const Human& p) {
    out << "Player strategy: Human" << endl;
    out << "Player: " << p.p->getName() << endl;
    return out;
}

ostream& operator<< (ostream &out, const Aggressive& p) {
    out << "Player strategy: Aggressive" << endl;
    out << "Player: " << p.p->getName() << endl;
    return out;
}

ostream& operator<< (ostream &out, const Benevolent& p) {
    out << "Player strategy: Benevolent" << endl;
    out << "Player: " << p.p->getName() << endl;
    return out;
}