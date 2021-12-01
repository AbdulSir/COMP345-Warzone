#include "PlayerStrategies.h"
#include "Orders.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

extern vector <Player*> players;
//extern Map* map;
extern Player* neutralPlayer;

PlayerStrategy::PlayerStrategy(Player* p) {
    this->p = p;
}
PlayerStrategy::~PlayerStrategy(){
    delete p;
}

PlayerStrategy::PlayerStrategy(const PlayerStrategy &p){
    this->p = new Player(*p.p);
}

Neutral::Neutral(Player* p): PlayerStrategy(p) {
    isAttacked = false;
}

Neutral::Neutral(const Neutral &n):PlayerStrategy(n) {
}


Cheater::Cheater(Player* p): PlayerStrategy(p) {}

Cheater::Cheater(const Cheater &c):PlayerStrategy(c) {
}

void Cheater::issueOrder() {

}

vector <Territory*> Cheater::toDefend() {
    vector <Territory*> attack;
    //An Example of how you would call adjacent_territory_vector()
    vector <Territory*> adjacent_terr = this->p->map->adjacent_territory_vector(this->p->getTerritories()[0]->getName()) //It takes the territory name and returns a list of territories.
    return attack;
}

vector <Territory*> Cheater::toAttack() {
    vector <Territory*> attack;
    return attack;
}

Human::Human(Player* p): PlayerStrategy(p) {}
Human::Human(const Human &h):PlayerStrategy(h) {
}

void Human::issueOrder() {
    cout << "Which order would you like to execute" << endl;
    string command;
    cin >> command;
    /*
    switch(command) {
        case "Deploy":
            string territoryName;
            int numberOfUnits;
            cout << "Which territory would you like to deploy" << endl;
            cin >> territoryName;
            cout << "How many armies would you like to deploy";
            cin >> numberOfUnits;
            for (auto t: map->territories) {
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
            for (auto t: map->territories) {
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
            for (auto t: map->territories) {
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
            for (auto t: map->territories) {
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
            for (auto t: map->territories) {
                if (t->getName() == territoryNameTo) {
                    to = t;
                }X
            }
            p->getOrders()->addOrder(new Blockade(p, to, neutralPlayer))
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
    }*/
}

vector <Territory*> Human::toDefend() {
    vector <Territory*> attack;
    return attack;
}

vector <Territory*> Human::toAttack() {
    vector <Territory*> attack;
    return attack;

}

Aggressive::Aggressive(Player* p): PlayerStrategy(p) {}
Aggressive::Aggressive(const Aggressive &a):PlayerStrategy(a) {
}

vector <Territory*> Aggressive::toDefend() {
    cout<<"Aggressive player defends"<<endl;
    vector <Territory*> attack;
    /*sort(p->getTerritories().begin(), p->getTerritories().end(), [](const Territory& lhs, const Territory& rhs) {
          return lhs.army_nb > rhs.army_nb;
       });*/
    return p->getTerritories();
}


vector <Territory*> Aggressive::toAttack() {
    cout<<"Aggressive player attacks"<<endl;
    vector <Territory*> attack;

    return attack;
}

void Aggressive::issueOrder() {
    cout << "Inside issueOrder of Agressive Player" << endl;
    this->p->getOrders()->addOrder(new Deploy(p,toDefend()[0],5));

}



void Neutral::issueOrder() {
    if (isAttacked) {
        //Aggressive::issueOrder();
    }
}

vector <Territory*> Neutral::toDefend() {
    vector <Territory*> attack;
    return attack;
}

vector <Territory*> Neutral::toAttack() {
    vector <Territory*> attack;
    return attack;
}

Benevolent::Benevolent(Player* p): PlayerStrategy(p) {}
Benevolent::Benevolent(const Benevolent &b):PlayerStrategy(b) {
}

void Benevolent::issueOrder() {
    this->p->getOrders()->addOrder(new Deploy(p,toDefend()[0],5));
}

vector <Territory*> Benevolent::toDefend() {
    cout<<"Benevolent player defends"<<endl;
    vector <Territory*> attack;
    /*sort(p->getTerritories().begin(), p->getTerritories().end(), [](const Territory& lhs, const Territory& rhs) {
          return lhs.army_nb < rhs.army_nb;
       });*/
    return p->getTerritories();

}

vector <Territory*> Benevolent::toAttack() {
    cout<<"Benevolent player refuses to attack"<<endl;
    vector <Territory*> attack;
    return attack;
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
