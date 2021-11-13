#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "Map.h"
#include "GameEngine.h"

#include <iostream>
using namespace std;

int main(){
    GameEngine *ge = new GameEngine();
    ge->reinforcementSetup();
    ge->reinforcementPhase();

}