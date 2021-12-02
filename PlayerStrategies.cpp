#include "PlayerStrategies.h"
#include "Orders.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

extern vector <Player*> players;
extern Map* map_obj;
extern Player* neutralPlayer;
PlayerStrategy::PlayerStrategy() {
}

PlayerStrategy::PlayerStrategy(Player* p) {
    this->p = p;
}
PlayerStrategy::~PlayerStrategy(){
    delete p;
}

void PlayerStrategy::setPlayer(Player* p){
    this->p = p;
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
    //vector <Territory*> adjacent_terr = this->p->map->adjacent_territory_vector(this->p->getTerritories()[0]->getName()); //It takes the territory name and returns a list of territories.
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
                }
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

Aggressive::Aggressive(): PlayerStrategy() {
}

Aggressive::Aggressive(Player* p): PlayerStrategy(p) {}
Aggressive::Aggressive(const Aggressive &a):PlayerStrategy(a) {
}



vector <Territory*> Aggressive::toDefend() {
    vector <Territory*> territories = p->getTerritories();
    //sort the player's territories in descending order
    sort( territories.begin( ), territories.end( ), [ ]( const auto& lhs, const auto& rhs )
    {
       return lhs->army_nb > rhs->army_nb;
    });
    return territories;
}


vector <Territory*> Aggressive::toAttack() {
    vector <Territory*> territories = p->getTerritories();
    //sort the player's territories in descending order
    sort( territories.begin( ), territories.end( ), [ ]( const auto& lhs, const auto& rhs )
    {
       return lhs->army_nb > rhs->army_nb;
    });
    
    vector <Territory*> adjacent_terr = map_obj->adjacent_territory_vector(territories[0]->getName());
    
    //Remove from vector non enemy territories
    for(int i=0; i<adjacent_terr.size();i++){
        if(isTerritoryOwnedByPlayer(p, adjacent_terr[i])){
            adjacent_terr.erase(find(adjacent_terr.begin(), adjacent_terr.end(), adjacent_terr[i]));
        }
    }

    return adjacent_terr;
}

void Aggressive::issueOrder() {
    cout << "Inside issueOrder of Agressive Player" << endl;
    
    //deploy army to strongest contry
    p->getOrders()->addOrder(new Deploy(p,toDefend()[0], p->getReinforcementPool()));
    
    int armies_attack = (toDefend()[0]->army_nb + p->getReinforcementPool())/toAttack().size();
    int armies_attack_remaider = (toDefend()[0]->army_nb + p->getReinforcementPool()) % toAttack().size();
    
    //issue bomb order
    for (auto const& i : p->getHand()->handDeck) {
        if(i->cardType=="bomb"){
            Bomb* bombOrder = dynamic_cast<Bomb*>(p->getHand()->discardFromHand().play());
            bombOrder->setOrderIssuer(p);
            bombOrder->setTarget(toAttack()[0]);
            bombOrder->setMap(map_obj);
            p->getOrders()->addOrder(bombOrder);
            
        }
    }
    
    //advance armies to strongest contry's adjacent territories
    for (int i=0; i<toAttack().size(); i++){
        p->getOrders()->addOrder(new Advance(p,toDefend()[0],toAttack()[i], armies_attack, map_obj));
    }
    
    if(armies_attack_remaider!=0){
        p->getOrders()->addOrder(new Advance(p,toDefend()[0],toAttack()[0], armies_attack_remaider, map_obj));
    }
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

Benevolent::Benevolent(): PlayerStrategy() {
}
Benevolent::Benevolent(Player* p): PlayerStrategy(p) {}
Benevolent::Benevolent(const Benevolent &b):PlayerStrategy(b) {
}

void Benevolent::issueOrder() {
    cout << "Inside issueOrder of Benevolent Player" << endl;
    int armies_defend = p->getReinforcementPool()/toDefend().size();
    int armies_defend_remaider =  p->getReinforcementPool()%toDefend().size();
    
    //deploy armies to weakest contries
    for (int i=0; i<toDefend().size(); i++){
        p->getOrders()->addOrder(new Deploy(p,toDefend()[i], armies_defend));
    }
    
    if(armies_defend_remaider!=0){
        p->getOrders()->addOrder(new Deploy(p,toDefend()[0], armies_defend_remaider));
    }
    
}

vector <Territory*> Benevolent::toDefend() {
    vector <Territory*> territories = p->getTerritories();
    
    //sort the player's territories in ascending order
    sort( territories.begin( ), territories.end( ), [ ]( const auto& lhs, const auto& rhs )
    {
       return lhs->army_nb < rhs->army_nb;
    });
    
    vector <Territory*> defend_territories;
    //push into vector the weakest contries
    for(int i = 0; i<territories.size(); i++){
        if(territories[i]->army_nb==territories[0]->army_nb){
            defend_territories.push_back(territories[i]);
        }
    }
    

    return defend_territories;
}

vector <Territory*> Benevolent::toAttack() {
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
