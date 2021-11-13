//
//  GameEngineDriver.cpp
//  COMP 345 - Assignment 1 - Team DN02
//  Warzone Game Engine: controls the flow of the game using the user's keyboard inputs as commands
//

#include "GameEngine.h"

#include <iostream>
using namespace std;

#include <string>

#include <fstream>
#include <sstream>
#include "Map.h"

int main() {

    GameEngine* gm = new GameEngine();
    gm->startupPhase();
    delete(gm);
    gm=NULL;

    return(0);
};
