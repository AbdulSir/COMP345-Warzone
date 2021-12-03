#pragma once

#include "Player.h"
#include "Map.h"
#include <iostream>
#include <vector>
class Player;
class Map;

extern vector <Player*> players_obj;
extern Map* map_obj;
extern Player* neutralPlayer;
bool hasCard(string a, Player* p);

void printTerritories(vector<Territory*>);

class PlayerStrategy {
public:
    Player* p;
    PlayerStrategy();
    PlayerStrategy(Player* p);
    ~PlayerStrategy();
    PlayerStrategy(const PlayerStrategy &p); //copy constructor
    void setPlayer(Player* p);
    virtual void issueOrder() = 0;
    virtual vector <Territory*> toAttack() = 0;
    virtual vector <Territory*> toDefend() = 0;
    PlayerStrategy& operator =(const PlayerStrategy& p); //assignment operator
    friend ostream& operator << (ostream &out, const PlayerStrategy& p); // stream insertion operator
};

class Neutral: public PlayerStrategy {
public:
    Neutral(Player* p);
    Neutral(const Neutral &n); //copy constructor
    void issueOrder();
    vector <Territory*> toAttack();
    vector <Territory*> toDefend();
    Neutral& operator =(const Neutral& n); //assignment operator
    friend ostream& operator << (ostream &out, const Neutral& n); // stream insertion operator
};

class Cheater: public PlayerStrategy {
public:
    Cheater(Player* p);
    Cheater(const Cheater &c); //copy constructor
    void issueOrder();
    vector <Territory*> toAttack();
    vector <Territory*> toDefend();
    Cheater& operator =(const Cheater& c); //assignment operator
    friend ostream& operator << (ostream &out, const Cheater& c); // stream insertion operator
};

class Human: public PlayerStrategy {
public:
    Human(Player* p);
    Human(const Human &h); //copy constructor
    void issueOrder();
    vector <Territory*> toAttack();
    vector <Territory*> toDefend();
    Human& operator =(const Human& h); //assignment operator
    friend ostream& operator << (ostream &out, const Human& h); // stream insertion operator
};

class Aggressive: public PlayerStrategy {
public:
    Aggressive();
    Aggressive(Player* p);
    Aggressive(const Aggressive &a); //copy constructor
    void issueOrder();
    vector <Territory*> toAttack();
    vector <Territory*> toDefend();
    Aggressive& operator =(const Aggressive& a); //assignment operator
    friend ostream& operator << (ostream &out, const Aggressive& a); // stream insertion operator
};

class Benevolent: public PlayerStrategy {
public:
    Benevolent();
    Benevolent(Player* p);
    Benevolent(const Benevolent &b); //copy constructor
    void issueOrder();
    vector <Territory*> toAttack();
    vector <Territory*> toDefend();
    Benevolent& operator =(const Benevolent& b); //assignment operator
    friend ostream& operator << (ostream &out, const Benevolent& b); // stream insertion operator
};
