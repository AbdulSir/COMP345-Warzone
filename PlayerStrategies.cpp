#include "PlayerStrategies.h"
#include "Orders.h"
#include <iostream>
#include <string>
using namespace std;

extern vector <Player*> players;
extern Map* map;

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
            int numberOfUnits;
            cout << "Which territory would you like to deploy" << endl;
            cin >> territoryName;
            cout << "How many armies would you like to deploy";
            cin >> numberOfUnits;
            for (auto t: p->getTerritories()) {
                if (t->getName() == territoryName) {
                    p->getOrders()->addOrder(new Deploy(p, t, numberOfUnits))
                }
            }
            break;
        case "Advance":
            string territoryNameFrom;
            string territoryNameTo;
            int numberOfUnits;
            cout << "Which territory would you like to advance from" << endl;
            cin >> territoryNameFrom;
            cout << "Which territory would you like to advance to" << endl;
            cin >> territoryNameTo;
            cout << "How many armies would you like to advance";
            cin >> numberOfUnits;
            Territory* from;
            Territory* to;
            for (auto t: p->getTerritories()) {
                if (t->getName() == territoryNameFrom) {
                    from = t;
                }
                if (t->getName() == territoryNameTo) {
                    to = t;
                }
            }
            p->getOrders()->addOrder(new Advance(p, from, to, numberOfUnits, map))
            break;
        case "Airlift":
            string territoryNameFrom;
            string territoryNameTo;
            int numberOfUnits;
            cout << "Which territory would you like to advance from" << endl;
            cin >> territoryNameFrom;
            cout << "Which territory would you like to advance to" << endl;
            cin >> territoryNameTo;
            cout << "How many armies would you like to airlift";
            cin >> numberOfUnits;
            Territory* from;
            Territory* to;
            for (auto t: p->getTerritories()) {
                if (t->getName() == territoryNameFrom) {
                    from = t;
                }
                if (t->getName() == territoryNameTo) {
                    to = t;
                }
            }
            p->getOrders()->addOrder(new Airlift(p, from, to, numberOfUnits))
            break;
        case "Bomb":
            string territoryNameTo;
            cout << "Which territory would you like to bomb to" << endl;
            cin >> territoryNameTo;
            Territory* to;
            for (auto t: p->getTerritories()) {
                if (t->getName() == territoryNameTo) {
                    to = t;
                }
            }
            p->getOrders()->addOrder(new Bomb(p, to, map))
            break;
        case "Blockade":
            string territoryNameTo;
            cout << "Which territory would you like to blockade" << endl;
            cin >> territoryNameTo;
            Territory* to;
            Player* neutral;
            for (auto t: p->getTerritories()) {
                if (t->getName() == territoryNameTo) {
                    to = t;
                }
            }
            for (auto p: players) {
                if (typeid(p->ps).name() == "Neutral") {
                    neutral = p;
                }
            }
            p->getOrders()->addOrder(new Blockade(p, to, neutral))
            break;
        case "Negotiate":
            string targetPlayerName;
            cout << "Which player would you like to negotiate" << endl;
            cin >> targetPlayerName;
            Player* target;
            for (auto p: players) {
                if (p->getName() == targetPlayerName) {
                    target = p;
                }
            }
            p->getOrders()->addOrder(new Negotiate(p, target))
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