#include "Player.h"
#include "Orders.h"
#include "Cards.h"
#include "Map.h"

#include <iostream>
using namespace std;

int main() {
    Map* m = new Map("[continents]\nNorth_Europe 5 red\nEast_Europe 4 magenta\nSouth_Europe 5 green\nWest_Europe 3 blue\n\n[countries]\n1 England 1 164 126\n2 Scotland 1 158 44\n3 N_Ireland 1 125 70\n4 Rep_Ireland 1 106 90\n5 Wales 1 141 109\n6 Belgum 1 213 153\n7 Netherlands 1 226 128\n\n[borders]\n1 6 7 5 2 3 4\n2 1 3\n3 1 2\n4 1 5\n5 1 4\n6 7 1\n7 6 1\n\n");
    cout << endl << endl;
    Hand* h = new Hand;
    Hand* h1 = new Hand;
    OrderList* orderList = new OrderList();
    Territory* firstTerritory = m->territories[0];
    Territory* secondTerritory = m->territories[1];
    Territory* thirdTerritory = m->territories[2];
    Territory* fourthTerritory = m->territories[3];
    Territory* fifthTerritory = m->territories[4];
    Territory* sixthTerritory = m->territories[5];
    Territory* seventhTerritory = m->territories[6];
    
    cout << *firstTerritory << endl;
    cout << *secondTerritory << endl;
    cout << *thirdTerritory << endl;
    cout << *fourthTerritory << endl;
    cout << *fifthTerritory << endl;
    cout << *sixthTerritory << endl;
    cout << *seventhTerritory << endl;

    vector <Territory*> v;
    vector <Territory*> v1;
    vector <Territory*> v2;

    v.push_back(firstTerritory);
    v.push_back(secondTerritory);
    v2.push_back(fifthTerritory);
    v2.push_back(sixthTerritory);

    // Player only owns A and B
    Player* player1 = new Player("testName", h, v);
    Player* player2 = new Player("anotherName", h1, v2);
    Player* neutralPlayer = new Player("Neutral", new Hand, v1);

    // Deploy test cases:
    cout << "-----Test case: player does deploy order but the target territory does not belong to the player-----" << endl;
    Deploy* deployOrder1 = new Deploy(player1, thirdTerritory, 3);
    deployOrder1->execute();
    cout << *deployOrder1 << endl;

    cout << "-----Test case: player does deploy order, target is their territory but the number of units exceed the number of reinforcement pool-----" << endl;
    Deploy* deployOrder2 = new Deploy(player1, secondTerritory, 500);
    deployOrder2->execute();
    cout << *deployOrder2 << endl;

    cout << "-----Test case: player does deploy order, target is their territory-----" << endl;
    Deploy* deployOrder3 = new Deploy(player1, firstTerritory, 5);
    cout << "Before execution: " << *firstTerritory << endl;
    cout << "Before execution reinforcement pool: " << player1->getReinforcementPool() << endl;
    deployOrder3->execute();
    cout << "After execution: " << *firstTerritory << endl;
    cout << "After execution reinforcement pool: " << player1->getReinforcementPool() << endl;
    cout << *deployOrder3 << endl;

    // Advance test cases:
    cout << "-----Test case: player does advance order, target is their territory-----" << endl;
    Advance* advanceOrder1 = new Advance(player1, firstTerritory, secondTerritory, 5, m);
    advanceOrder1->execute();
    cout << *advanceOrder1 << endl;

    cout << "-----Test case: player does advance order, target is enemy's territory, guaranteed to win-----" << endl;
    thirdTerritory->setArmy(0);
    Advance* advanceOrder2 = new Advance(player1, firstTerritory, thirdTerritory, 10, m);
    advanceOrder2->execute();
    cout << *advanceOrder2 << endl;

    cout << "-----Test case: player does advance order, target is enemy's territory, guaranteed to lose-----" << endl;
    thirdTerritory->setArmy(1000);
    Advance* advanceOrder3 = new Advance(player1, firstTerritory, thirdTerritory, 1, m);
    advanceOrder3->execute();
    cout << *advanceOrder3 << endl;

    cout << "-----Test case: player does advance order, target not adjacent-----" << endl;
    Advance* advanceOrder4 = new Advance(player1, firstTerritory, seventhTerritory, 10, m);
    advanceOrder4->execute();
    cout << *advanceOrder4 << endl;

    // Airlift test cases:
    cout << "-----Test case: create airlift order with card, valid order-----" << endl;
    h->addToHand(new Card("airlift"));
    Airlift* airliftOrder1 = dynamic_cast<Airlift*>(h->discardFromHand().play());
    airliftOrder1->setOrderIssuer(player1);
    airliftOrder1->setFrom(firstTerritory);
    airliftOrder1->setTarget(secondTerritory);
    airliftOrder1->setNumberOfUnits(5);

    cout << "Before execution: " << *firstTerritory << endl;
    cout << "Before execution: " << *secondTerritory << endl;
    airliftOrder1->execute();
    cout << "After execution: " << *firstTerritory << endl;
    cout << "After execution: " << *secondTerritory << endl;
    cout << *airliftOrder1 << endl;

    cout << "-----Test case: create airlift order with card, target does not belong to the player, invalid order-----" << endl;
    h->addToHand(new Card("airlift"));
    Airlift* airliftOrder2 = dynamic_cast<Airlift*>(h->discardFromHand().play());
    airliftOrder2->setOrderIssuer(player1);
    airliftOrder2->setFrom(firstTerritory);
    airliftOrder2->setTarget(thirdTerritory);
    airliftOrder2->setNumberOfUnits(5);

    airliftOrder2->execute();
    cout << *airliftOrder2 << endl;

    cout << "-----Test case: create airlift order with card, source does not belong to the player, invalid order-----" << endl;
    h->addToHand(new Card("airlift"));
    Airlift* airliftOrder3 = dynamic_cast<Airlift*>(h->discardFromHand().play());
    airliftOrder3->setOrderIssuer(player1);
    airliftOrder3->setFrom(thirdTerritory);
    airliftOrder3->setTarget(firstTerritory);
    airliftOrder3->setNumberOfUnits(5);

    airliftOrder3->execute();
    cout << *airliftOrder3 << endl;

    // Bomb test cases:
    cout << "-----Test case: create bomb order with card, valid order-----" << endl;
    h->addToHand(new Card("bomb"));
    Bomb* bombOrder1 = dynamic_cast<Bomb*>(h->discardFromHand().play());
    bombOrder1->setOrderIssuer(player1);
    bombOrder1->setTarget(thirdTerritory);
    bombOrder1->setMap(m);

    cout << "Before execution C: " << *thirdTerritory << endl;
    bombOrder1->execute();
    cout << "After execution C: " << *thirdTerritory << endl;
    cout << *bombOrder1 << endl;

    cout << "-----Test case: create bomb order with card but target is the player's territory-----" << endl;
    h->addToHand(new Card("bomb"));
    Bomb* bombOrder2 = dynamic_cast<Bomb*>(h->discardFromHand().play());
    bombOrder2->setOrderIssuer(player1);
    bombOrder2->setTarget(firstTerritory);
    bombOrder2->setMap(m);

    bombOrder2->execute();
    cout << *bombOrder2 << endl;

    cout << "-----Test case: create bomb order with card but target is not adjacent to any player's territory-----" << endl;
    h->addToHand(new Card("bomb"));
    Bomb* bombOrder3 = dynamic_cast<Bomb*>(h->discardFromHand().play());
    bombOrder3->setOrderIssuer(player1);
    bombOrder3->setTarget(seventhTerritory);
    bombOrder3->setMap(m);

    bombOrder3->execute();
    cout << *bombOrder3 << endl;

    // Blockade test cases:
    cout << "-----Test case: create blockade order with card, valid order-----" << endl;
    h->addToHand(new Card("blockade"));
    Blockade* blockadeOrder1 = dynamic_cast<Blockade*>(h->discardFromHand().play());
    blockadeOrder1->setOrderIssuer(player1);
    blockadeOrder1->setTarget(firstTerritory);
    blockadeOrder1->setNeutralPlayer(neutralPlayer);

    cout << "Before execution A: " << *firstTerritory << endl;
    blockadeOrder1->execute();
    cout << "After execution A: " << *firstTerritory << endl;
    cout << *blockadeOrder1 << endl;

    cout << "-----Test case: create blockade order with card but the target is not player's territory-----" << endl;
    h->addToHand(new Card("blockade"));
    Blockade* blockadeOrder2 = dynamic_cast<Blockade*>(h->discardFromHand().play());
    blockadeOrder2->setOrderIssuer(player1);
    blockadeOrder2->setTarget(thirdTerritory);
    blockadeOrder2->setNeutralPlayer(neutralPlayer);

    blockadeOrder2->execute();
    cout << *blockadeOrder2 << endl;

    // Negotiate test cases:
    cout << "-----Test case: create negotiate order with card, valid order-----" << endl;
    h1->addToHand(new Card("diplomacy"));
    Negotiate* negotiateOrder1 = dynamic_cast<Negotiate*>(h1->discardFromHand().play());
    negotiateOrder1->setOrderIssuer(player1);
    negotiateOrder1->setTarget(player2);

    negotiateOrder1->execute();
    cout << *negotiateOrder1 << endl;
    Advance* testAttackOrder = new Advance(player1, firstTerritory, fifthTerritory, 5, m);
    testAttackOrder->execute();
    cout << *testAttackOrder << endl;

    cout << "-----Test case: create negotiate order with card, target is the issuer, invalid order-----" << endl;
    h1->addToHand(new Card("diplomacy"));
    Negotiate* negotiateOrder2 = dynamic_cast<Negotiate*>(h1->discardFromHand().play());
    negotiateOrder2->setOrderIssuer(player1);
    negotiateOrder2->setTarget(player1);

    negotiateOrder2->execute();
    cout << *negotiateOrder2 << endl;

    h = NULL;
    h1 = NULL;
    orderList = NULL;
    firstTerritory = NULL;
    secondTerritory = NULL;
    thirdTerritory = NULL;
    fourthTerritory = NULL;
    fifthTerritory = NULL;
    sixthTerritory = NULL;
    player1 = NULL;
    player2 = NULL;
    neutralPlayer = NULL;
    deployOrder1 = NULL;
    deployOrder2 = NULL;
    deployOrder3 = NULL;
    advanceOrder1 = NULL;
    advanceOrder2 = NULL;
    advanceOrder3 = NULL;
    airliftOrder1 = NULL;
    airliftOrder2 = NULL;
    airliftOrder3 = NULL;
    bombOrder1 = NULL;
    bombOrder2 = NULL;
    blockadeOrder1 = NULL;
    blockadeOrder2 = NULL;
    negotiateOrder1 = NULL;
    negotiateOrder2 = NULL;
    testAttackOrder = NULL;

    //delete all pointers
    delete orderList;
    delete firstTerritory;
    delete secondTerritory;
    delete thirdTerritory;
    delete fourthTerritory;
    delete fifthTerritory;
    delete sixthTerritory;
    delete player1;
    delete player2;
    delete neutralPlayer;
    delete deployOrder1;
    delete deployOrder2;
    delete deployOrder3;
    delete advanceOrder1;
    delete advanceOrder2;
    delete advanceOrder3;
    delete airliftOrder1;
    delete airliftOrder2;
    delete airliftOrder3;
    delete bombOrder1;
    delete bombOrder2;
    delete blockadeOrder1;
    delete blockadeOrder2;
    delete negotiateOrder1;
    delete negotiateOrder2;
    delete testAttackOrder;

    return 0;
}
