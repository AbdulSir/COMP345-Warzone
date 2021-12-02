#include "Player.h"
#include "Orders.h"
#include "Map.h"
#include "GameEngine.h"
#include <vector>
#include <iostream>
using namespace std;

MapLoader* ml;
Map* map;
vector <Player*> players;
Player* neutralPlayer;

int main() {
    GameEngine* gm = new GameEngine();
    gm->startupPhase();
    ml = gm->map_loader;
    map = ml->map_object;
    players = gm->players;
    for (auto p: players) {
        cout << *p << endl;
    }

    delete(gm);
    gm=NULL;
    return 0;
}