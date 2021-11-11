#include "Player.h"
#include "Orders.h"
#include "Cards.h"

#include <iostream>
using namespace std;

int main() {
    Hand* h = new Hand;
    OrderList* orderList = new OrderList();
    Territory* firstTerritory = new Territory("A", 0, 10);
    Territory* secondTerritory = new Territory("B", 0, 10);
    Territory* thirdTerritory = new Territory("C", 0, 10);

    vector <Territory*> v;
    v.push_back(firstTerritory);
    v.push_back(secondTerritory);
    // Player only owns A and B
    Player* player1 = new Player("testName", h, v);

    // Deploy test cases:
    cout << "-----Test case: player does deploy order but the target territory does not belong to the player-----" << endl;
    Deploy* deployOrder1 = new Deploy(player1, thirdTerritory, 3);
    cout << *deployOrder1 << endl;
    deployOrder1->execute();
    cout << endl;

    cout << "-----Test case: player does deploy order, target is their territory but the number of units exceed the number of reinforcement pool-----" << endl;
    Deploy* deployOrder2 = new Deploy(player1, secondTerritory, 500);
    cout << *deployOrder2 << endl;
    deployOrder2->execute();
    cout << endl;

    cout << "-----Test case: player does deploy order, target is their territory-----" << endl;
    Deploy* deployOrder3 = new Deploy(player1, firstTerritory, 5);
    cout << *deployOrder3 << endl;
    cout << "Before execution: " << endl << *firstTerritory << endl;
    cout << "Before execution: " << endl << *player1 << endl;
    deployOrder3->execute();
    cout << "After execution: " << endl << *firstTerritory << endl;
    cout << "After execution: " << endl << *player1 << endl;

    // Advance test cases:


    // Airlift test cases:
    cout << "-----Test case: create airlift order with card, valid order-----" << endl;
    h->addToHand(new Card("airlift"));
    Airlift* airliftOrder1 = dynamic_cast<Airlift*>(h->discardFromHand().play());
    airliftOrder1->setOrderIssuer(player1);
    airliftOrder1->setFrom(firstTerritory);
    airliftOrder1->setTarget(secondTerritory);
    airliftOrder1->setNumberOfUnits(5);

    cout << *airliftOrder1 << endl;
    cout << "Before execution A: " << *firstTerritory << endl;
    cout << "Before execution B: " << *secondTerritory << endl;
    airliftOrder1->execute();
    cout << "After execution A: " << *firstTerritory << endl;
    cout << "After execution B: " << *secondTerritory << endl;

    cout << "-----Test case: create airlift order with card, target does not belong to the player, invalid order-----" << endl;
    h->addToHand(new Card("airlift"));
    Airlift* airliftOrder2 = dynamic_cast<Airlift*>(h->discardFromHand().play());
    airliftOrder2->setOrderIssuer(player1);
    airliftOrder2->setFrom(firstTerritory);
    airliftOrder2->setTarget(thirdTerritory);
    airliftOrder2->setNumberOfUnits(5);

    cout << *airliftOrder2 << endl;
    airliftOrder2->execute();

    cout << "-----Test case: create airlift order with card, source does not belong to the player, invalid order-----" << endl;
    h->addToHand(new Card("airlift"));
    Airlift* airliftOrder3 = dynamic_cast<Airlift*>(h->discardFromHand().play());
    airliftOrder3->setOrderIssuer(player1);
    airliftOrder3->setFrom(thirdTerritory);
    airliftOrder3->setTarget(firstTerritory);
    airliftOrder3->setNumberOfUnits(5);

    cout << *airliftOrder3 << endl;
    airliftOrder3->execute();

    // Bomb test cases:
    cout << "-----Test case: create bomb order with card, valid order-----" << endl;
    h->addToHand(new Card("bomb"));
    Bomb* bombOrder1 = dynamic_cast<Bomb*>(h->discardFromHand().play());
    bombOrder1->setOrderIssuer(player1);
    bombOrder1->setTarget(thirdTerritory);

    cout << *bombOrder1 << endl;
    cout << "Before execution C: " << *thirdTerritory << endl;
    bombOrder1->execute();
    cout << "After execution C: " << *thirdTerritory << endl;

    cout << "-----Test case: create bomb order with card but target is the player's territory-----" << endl;
    h->addToHand(new Card("bomb"));
    Bomb* bombOrder2 = dynamic_cast<Bomb*>(h->discardFromHand().play());
    bombOrder2->setOrderIssuer(player1);
    bombOrder2->setTarget(firstTerritory);

    cout << *bombOrder2 << endl;
    bombOrder2->execute();

    // Blockade test cases:
    cout << "-----Test case: create blockade order with card, valid order-----" << endl;
    h->addToHand(new Card("blockade"));
    Blockade* blockadeOrder1 = dynamic_cast<Blockade*>(h->discardFromHand().play());
    blockadeOrder1->setOrderIssuer(player1);
    blockadeOrder1->setTarget(firstTerritory);

    cout << *blockadeOrder1 << endl;
    cout << "Before execution A: " << *firstTerritory << endl;
    blockadeOrder1->execute();
    cout << "After execution A: " << *firstTerritory << endl;

    cout << "-----Test case: create blockade order with card but the target is not player's territory-----" << endl;
    h->addToHand(new Card("blockade"));
    Blockade* blockadeOrder2 = dynamic_cast<Blockade*>(h->discardFromHand().play());
    blockadeOrder2->setOrderIssuer(player1);
    blockadeOrder2->setTarget(thirdTerritory);

    cout << *blockadeOrder2 << endl;
    blockadeOrder2->execute();

    // Negotiate test cases:

    orderList = NULL;
    firstTerritory = NULL;
    secondTerritory = NULL;
    thirdTerritory = NULL;
    player1 = NULL;
    deployOrder1 = NULL;
    deployOrder2 = NULL;
    airliftOrder1 = NULL;
    airliftOrder2 = NULL;
    airliftOrder3 = NULL;
    bombOrder1 = NULL;
    bombOrder2 = NULL;
    blockadeOrder1 = NULL;
    blockadeOrder2 = NULL;

    //delete all pointers
    delete orderList;
    delete firstTerritory; 
    delete secondTerritory;
    delete thirdTerritory; 
    delete player1;
    delete deployOrder1;
    delete deployOrder2;
    delete airliftOrder1;
    delete airliftOrder2;
    delete airliftOrder3;
    delete bombOrder1;
    delete bombOrder2;
    delete blockadeOrder1;
    delete blockadeOrder2;

    return 0;
}
