#include "PlayerStrategies.h"
#include "Orders.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool hasCard(string type, Player* p) {
    bool returnValue = false;
    for (auto c: p->getHand()->handDeck) {
        if (c->cardType == type) {
            returnValue = true;
        }
    }
    return returnValue;
}

void printTerritories(vector<Territory*> territories) {
    for (auto t: territories) {
        cout << t->getName() << endl;
    }
}

//PlayerStrategy

//Default constructor
PlayerStrategy::PlayerStrategy() {
}

//Constructor
PlayerStrategy::PlayerStrategy(Player* p) {
    this->p = p;
}

//Destructor
PlayerStrategy::~PlayerStrategy(){
    delete p;
}

//Copy constructor
PlayerStrategy::PlayerStrategy(const PlayerStrategy &p){
    this->p = new Player(*p.p);
}

//assignment operator
PlayerStrategy& PlayerStrategy::operator= (const PlayerStrategy& ps) {
    this->p = new Player;
    *p = *ps.p;
    return *this;
}

void PlayerStrategy::setPlayer(Player* p){
    this->p = p;
}

//Neutral

//Default Constructor
Neutral::Neutral(): PlayerStrategy() {
}

//Constructor
Neutral::Neutral(Player* p): PlayerStrategy(p) {}

//Copy constructor
Neutral::Neutral(const Neutral &n):PlayerStrategy(n) {
}

//assignment operator
Neutral& operator =(const Neutral& n){
    PlayerStrategy::operator=(n);
    return *this;
}

void Neutral::issueOrder() {}

vector <Territory*> Neutral::toDefend() {
    vector <Territory*> attack;
    return attack;
}

vector <Territory*>  Neutral::toAttack() {
    vector <Territory*> attack;
    return attack;
}

//Cheater

//Default Constructor
Cheater::Cheater(): PlayerStrategy() {
}

//Constructor
Cheater::Cheater(Player* p): PlayerStrategy(p) {}

//Copy constructor
Cheater::Cheater(const Cheater &c):PlayerStrategy(c) {
}

//assignment operator
Cheater& operator =(const Cheater& c){
    PlayerStrategy::operator=(c);
    return *this;
}

void Cheater::issueOrder() {
    vector<Territory*> to_attack = toAttack();
    for(int i=0; i<to_attack.size(); i++){
        to_attack[i]->setOwner(this->p);
    }
}

vector <Territory*> Cheater::toDefend() {
    vector <Territory*> attack;
    return attack;
}

vector <Territory*> Cheater::toAttack() {
    vector <Territory*> attack;

    for(int i=0; i<this->p->getTerritories().size(); i++){
        vector <Territory*> adjacent_ter = map_obj->adjacent_territory_vector(this->p->getTerritories()[i]->getName());
        for (int j=0; j<adjacent_ter.size();j++){
            bool matchTerr=false;
            for(auto t: attack){
                if( adjacent_ter[j]->getName()==t->getName()){
                    matchTerr=true;
                    break;
                }
            }
            if(!matchTerr && !isTerritoryOwnedByPlayer(p, adjacent_ter[j])){
                attack.push_back(adjacent_ter[j]);
            }
        }
    }
    return attack;
}

//Human

//Default Constructor
Human::Human(): PlayerStrategy() {
}

//Constructor
Human::Human(Player* p): PlayerStrategy(p) {}

//Copy constructor
Human::Human(const Human &h):PlayerStrategy(h) {}

//assignment operator
Human& operator =(const Human& h){
    PlayerStrategy::operator=(h);
    return *this;
}

void Human::issueOrder() {
    string command;
    while (true) {
        cout << "Which order would you like to execute, type exit to end order issuing" << endl;
        cin >> command;
        if (command == "exit") {
            break;
        }
        if (command ==  "Deploy") {
            string territoryName;
            int numberOfUnits;
            cout << "Which territory would you like to deploy" << endl;
            cout << "List of territories to deploy:" << endl;
            printTerritories(toDefend());
            cin >> territoryName;
            cout << "How many armies would you like to deploy" << endl;
            cin >> numberOfUnits;
            for (auto t: map_obj->territories) {
                if (t->getName() == territoryName) {
                    p->getOrders()->addOrder(new Deploy(p, t, numberOfUnits));
                }
            }
        }
        if (command == "Advance") {
            string territoryNameFrom;
            string territoryNameTo;
            int numberOfUnits;
            cout << "Which territory would you like to advance from" << endl;
            printTerritories(toDefend());
            cin >> territoryNameFrom;
            cout << "Which territory would you like to advance to" << endl;
            cout << "List of territories to attack:" << endl;
            printTerritories(toAttack());
            cout << "List of territories to advance:" << endl;
            printTerritories(toDefend());
            cin >> territoryNameTo;
            cout << "How many armies would you like to advance" << endl;
            cin >> numberOfUnits;
            Territory* from;
            Territory* to;
            for (auto t: map_obj->territories) {
                if (t->getName() == territoryNameFrom) {
                    from = t;
                }
                if (t->getName() == territoryNameTo) {
                    to = t;
                }
            }
            p->getOrders()->addOrder(new Advance(p, from, to, numberOfUnits, map_obj));
        }
        if (command == "Airlift") {
            if (hasCard("airlift", p)) {
                string territoryNameFrom;
                string territoryNameTo;
                int numberOfUnits;
                cout << "Which territory would you like to advance from" << endl;
                printTerritories(toDefend());
                cin >> territoryNameFrom;
                cout << "Which territory would you like to advance to" << endl;
                printTerritories(toDefend());
                cin >> territoryNameTo;
                cout << "How many armies would you like to airlift";
                cin >> numberOfUnits;
                Territory* from;
                Territory* to;
                for (auto t: map_obj->territories) {
                    if (t->getName() == territoryNameFrom) {
                        from = t;
                    }
                    if (t->getName() == territoryNameTo) {
                        to = t;
                    }
                }
                p->getOrders()->addOrder(new Airlift(p, from, to, numberOfUnits));
            } else {
                cout << "You do not have a airlift card :(" << endl;
            }

        }
        if (command == "Bomb") {
            if (hasCard("bomb", p)) {
                string territoryNameTo;
                cout << "Which territory would you like to bomb to" << endl;
                printTerritories(toAttack());
                cin >> territoryNameTo;
                Territory* to;
                for (auto t: map_obj->territories) {
                    if (t->getName() == territoryNameTo) {
                        to = t;
                    }
                }
                p->getOrders()->addOrder(new Bomb(p, to, map_obj));
            } else {
                cout << "You do not have a bomb card :(" << endl;
            }
        }
        if (command == "Blockade") {
            if (hasCard("blockade", p)) {
                string territoryNameTo;
                cout << "Which territory would you like to blockade" << endl;
                printTerritories(toDefend());
                cin >> territoryNameTo;
                Territory* to;
                for (auto t: map_obj->territories) {
                    if (t->getName() == territoryNameTo) {
                        to = t;
                    }
                }
                p->getOrders()->addOrder(new Blockade(p, to, neutralPlayer));
            } else {
                cout << "You do not have a blockade card :(" << endl;
            }
        } 
        if (command == "Negotiate") {
            if (hasCard("diplomacy", p)) {
                string targetPlayerName;
                cout << "Which player would you like to negotiate" << endl;
                cout << "Player list:" << endl;
                for (auto p: players) {
                    cout << p->getName() << endl;
                }
                cin >> targetPlayerName;
                Player* target;
                for (auto p: players) {
                    if (p->getName() == targetPlayerName) {
                        target = p;
                    }
                }
                p->getOrders()->addOrder(new Negotiate(p, target));
            } else {
                cout << "You do not have a diplomacy card :(" << endl;
            }
        }
    }
}

vector <Territory*> Human::toDefend() {
    return p->getTerritories();
}

vector <Territory*> Human::toAttack() {
    vector <Territory*> attack;
    for(int i=0; i<this->p->getTerritories().size(); i++){
        vector <Territory*> adjacent_ter = map_obj->adjacent_territory_vector(this->p->getTerritories()[i]->getName());
        for (int j=0; j<adjacent_ter.size();j++){
            bool matchTerr=false;
            for(auto t: attack){
                if( adjacent_ter[j]->getName()==t->getName()){
                    matchTerr=true;
                    break;
                }
            }
            if(!matchTerr && !isTerritoryOwnedByPlayer(p, adjacent_ter[j])){
                attack.push_back(adjacent_ter[j]);
            }
        }
    }
    return attack;
}

//Aggressive

//Default Constructor
Aggressive::Aggressive(): PlayerStrategy() {
}

//Constructor
Aggressive::Aggressive(Player* p): PlayerStrategy(p) {}

//Copy constructor
Aggressive::Aggressive(const Aggressive &a):PlayerStrategy(a) {
}

//assignment operator
Aggressive& operator =(const Aggressive& a){
    PlayerStrategy::operator=(a);
    return *this;
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
    vector <Territory*> attack;
    vector <Territory*> territories = p->getTerritories();
    //sort the player's territories in descending order
    sort( territories.begin( ), territories.end( ), [ ]( const auto& lhs, const auto& rhs )
    {
       return lhs->army_nb > rhs->army_nb;
    });
    
    vector <Territory*> adjacent_terr = map_obj->adjacent_territory_vector(territories[0]->getName());
    
    //Remove from vector non enemy territories
    for(int i=0; i<adjacent_terr.size();i++){
        if(!isTerritoryOwnedByPlayer(p, adjacent_terr[i])){
            attack.push_back(adjacent_terr[i]);
        }
    }

    return attack;
}

void Aggressive::issueOrder() {
    cout << "Inside issueOrder of Agressive Player" << endl;
    vector<Territory*> my_contries = toDefend();
    vector<Territory*> adj_contries = toAttack();
    
    //deploy army to strongest contry
    p->getOrders()->addOrder(new Deploy(p,my_contries[0], p->getReinforcementPool()));
    
    if(adj_contries.size()!=0){
        int armies_attack = (my_contries[0]->army_nb + p->getReinforcementPool())/adj_contries.size();
        int armies_attack_remaider = (my_contries[0]->army_nb + p->getReinforcementPool()) % adj_contries.size();
        
        //issue bomb order
        for (auto const& i : p->getHand()->handDeck) {
            if(i->cardType=="bomb"){
                p->getOrders()->addOrder(new Bomb(p, adj_contries[0], map_obj));
            }
        }
        
        //advance armies to strongest contry's adjacent territories
        for (int i=0; i<adj_contries.size(); i++){
            p->getOrders()->addOrder(new Advance(p,my_contries[0],adj_contries[i], armies_attack, map_obj));
        }
        
        if(armies_attack_remaider!=0){
            p->getOrders()->addOrder(new Advance(p,my_contries[0],adj_contries[0], armies_attack_remaider, map_obj));
        }
    }
}

//Benevolent

//Default Constructor
Benevolent::Benevolent(): PlayerStrategy() {
}

//Constructor
Benevolent::Benevolent(Player* p): PlayerStrategy(p) {}

//Copy constructor
Benevolent::Benevolent(const Benevolent &b):PlayerStrategy(b) {
}

//assignment operator
Benevolent& operator =(const Benevolent& b){
    PlayerStrategy::operator=(b);
    return *this;
}

void Benevolent::issueOrder() {
    cout << "Inside issueOrder of Benevolent Player" << endl;
    vector<Territory*> weakest_contries=toDefend();
    int armies_defend = p->getReinforcementPool()/weakest_contries.size();
    int armies_defend_remaider =  p->getReinforcementPool()%weakest_contries.size();
    
    //deploy armies to weakest contries
    for (int i=0; i<toDefend().size(); i++){
        p->getOrders()->addOrder(new Deploy(p,weakest_contries[i], armies_defend));
    }
    
    if(armies_defend_remaider!=0){
        p->getOrders()->addOrder(new Deploy(p,weakest_contries[0], armies_defend_remaider));
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
