#include "Player.h"
#include "Orders.h"
#include "Cards.h"

#include <iostream>
using namespace std;

int main() {
    Hand* h = new Hand;
    OrderList* orderList = new OrderList();
    Territory* first = new Territory("A", 0, 10);
    Territory* second = new Territory("B", 0, 10);
    Territory* third = new Territory("C", 0, 10);
    Territory* fourth = new Territory("D", 0, 10);
    Territory* fifth = new Territory("E", 0, 10);
    Territory* sixth = new Territory("F", 0, 10);

    vector <Territory*> v;
    v.push_back(first);
    v.push_back(second);
    // Player only owns A and B
    Player* player1 = new Player("testName", h, v);

    cout << "-----Test case: player does deploy order but the target territory does not belong to the player-----" << endl;
    Deploy* order1 = new Deploy(player1, third, 3);
    order1->execute();
    cout << endl;

    cout << "-----Test case: player does deploy order, target is their territory-----" << endl;
    Deploy* order2 = new Deploy(player1, first, 5);
    cout << "Before execution: " << endl << *first << endl;
    order2->execute();
    cout << "After execution: " << endl << *first << endl;

    cout << "-----Test case: create airlift order with card, valid order-----" << endl;
    h->addToHand(new Card("airlift"));
    Airlift* airliftOrderFromCard = dynamic_cast<Airlift*>(h->discardFromHand().play());
    airliftOrderFromCard->setOrderIssuer(player1);
    airliftOrderFromCard->setFrom(first);
    airliftOrderFromCard->setTarget(second);
    airliftOrderFromCard->setNumberOfUnits(5);

    cout << "Before execution A: " << *first << endl;
    cout << "Before execution B: " << *second << endl;
    airliftOrderFromCard->execute();
    cout << "After execution A: " << *first << endl;
    cout << "After execution B: " << *second << endl;

    cout << "-----Test case: create airlift order with card, invalid order-----" << endl;
    h->addToHand(new Card("airlift"));
    Airlift* airliftOrderFromCard2 = dynamic_cast<Airlift*>(h->discardFromHand().play());
    airliftOrderFromCard2->setOrderIssuer(player1);
    airliftOrderFromCard2->setFrom(first);
    airliftOrderFromCard2->setTarget(third);
    airliftOrderFromCard2->setNumberOfUnits(5);

    cout << "Before execution A: " << *first << endl;
    cout << "Before execution B: " << *second << endl;
    airliftOrderFromCard2->execute();
    cout << "After execution A: " << *first << endl;
    cout << "After execution B: " << *second << endl;

    // Advance* order2 = new Advance("3", player1, test, test2, 3);
    // order2->execute();

    // Airlift* order3 = new Airlift("4", player1, test, test2, 3);
    // order3->execute();

    //delete all pointers
    delete orderList;

    return 0;
}
