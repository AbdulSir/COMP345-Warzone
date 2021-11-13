#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

#include <iostream>
using namespace std;

int main() {
    MapLoader* map_loader = new MapLoader("europe.map");
    Map* m = map_loader->map_object;
    cout << endl << endl;
    GameEngine* GE = new GameEngine();

    Hand* h = new Hand;
    Hand* h1 = new Hand;

    //create a few test territories
    Territory* firstTerritory = m->territories[0];
    Territory* secondTerritory = m->territories[1];
    Territory* thirdTerritory = m->territories[2];
    Territory* fourthTerritory = m->territories[3];
    Territory* fifthTerritory = m->territories[4];
    Territory* sixthTerritory = m->territories[5];


    vector <Territory*> v;
    vector <Territory*> v1;
    vector <Territory*> v2;
    
    Player* player1 = new Player("testName", h, v);
    Player* player2 = new Player("anotherName", h1, v2);
    Player* neutralPlayer = new Player("Neutral", new Hand, v1);

    firstTerritory->setOwner(player1);
    secondTerritory->setOwner(player1);
    fifthTerritory->setOwner(player2);
    
    cout << *firstTerritory << endl;
    cout << *secondTerritory << endl;
    cout << *thirdTerritory << endl;
    cout << *fourthTerritory << endl;
    cout << *fifthTerritory << endl;
    cout << *sixthTerritory << endl;


    player1->hand->addToHand(new Card(""));
    player2->hand->addToHand(new Card(""));



    GE->mainGameLoop();