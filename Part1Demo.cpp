#include "Player.h"
#include "Orders.h"
#include "Map.h"
#include "GameEngine.h"
#include <vector>
#include <iostream>
using namespace std;

MapLoader* ml;
Map* map_obj;
vector <Player*> players;
Player* neutralPlayer;


int main() {
    Player* a = new Player("123");
    cout << regex_replace(typeid(*a->ps).name(), reg, "");
    GameEngine* gm = new GameEngine();
    cout << regex_replace(typeid(*gm).name(), reg, "");
    gm->startupPhase();
    ml = gm->map_loader;
    map_obj = ml->map_object;
    players = gm->players;
    for (auto p: players) {
        cout << *p << endl;
    }

    delete(gm);
    gm=NULL;
    return 0;
}