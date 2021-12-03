//
//  TournamentModeDriver.cpp
//  Assignment2
//

#include "CommandProcessing.h"
#include "GameEngine.h"
#include <iostream>
using namespace std;

MapLoader* ml;
Map* map_obj;
vector <Player*> players_obj;
Player* neutralPlayer = new Player("Neutral");


int main() {
    neutralPlayer->ps = new Neutral(neutralPlayer);
    GameEngine* g = new GameEngine();
    delete g;
    g = NULL;
}
