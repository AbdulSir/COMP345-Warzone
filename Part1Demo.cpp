#include "Player.h"
#include "Orders.h"
#include "Map.h"
#include "GameEngine.h"
#include <vector>
#include <iostream>
using namespace std;

MapLoader* ml = new MapLoader("europe.map");
Map* map_obj = ml->map_object;
vector <Player*> players;
Player* neutralPlayer;

int main() {
    // Human strategy player
    Player* humanPlayer = new Player("Human");
    players.push_back(humanPlayer);
    // Aggressive player
    Player* aggressivePlayer = new Player("Aggressive");
    aggressivePlayer->ps = new Aggressive(aggressivePlayer);
    players.push_back(aggressivePlayer);
    // Benevolent player
    Player* benevolentPlayer = new Player("Benevolent");
    benevolentPlayer->ps = new Benevolent(aggressivePlayer);
    players.push_back(benevolentPlayer);
    // Neutral player
    neutralPlayer = new Player("Neutral");
    neutralPlayer->ps = new Neutral(neutralPlayer);
    players.push_back(neutralPlayer);
    // Cheater player
    Player* cheaterPlayer = new Player("Cheater");
    cheaterPlayer->ps = new Cheater(cheaterPlayer);
    players.push_back(cheaterPlayer);

    int i = 0;
    for (auto t: map_obj->territories) {
        if (i < 5) {
            t->setOwner(humanPlayer);
        } else if (i < 10) {
            t->setOwner(aggressivePlayer);
        } else if (i < 15) {
            t->setOwner(benevolentPlayer);
        } else if (i < 20) {
            t->setOwner(neutralPlayer);
        } else if (i < 25) {
            t->setOwner(cheaterPlayer);
        }
        i++;
    }

    for (auto p: players) {
        for (auto t: p->getTerritories()) {
            cout << *t << endl;
        }
    }

    humanPlayer->ps->issueOrder();
    aggressivePlayer->ps->issueOrder();
    benevolentPlayer->ps->issueOrder();
    neutralPlayer->ps->issueOrder();
    cheaterPlayer->ps->issueOrder();

    for (auto p: players) {
        // cout<<*p->getOrders()<<endl;
        for (auto o: p->getOrders()->orderList) {
            cout << *o << endl;
            o->execute();
        }
    }

    return 0;
}