#include "Cards.h"
#include <iostream>
using namespace std;
// Card driver to demonstrate the implemented functions

int main() {
    // define gameDeck with pointer type
    Deck* gameDeck = new Deck(40);
    // define hand with pointer type
    Hand *hand = new Hand();
    
    OrderList *orderList = new OrderList();

    Card *temp;
    Order *newOrder;

    // draw 5 cards and add to hand
    for (int i=0; i<5; i++) {
        hand->addToHand(gameDeck->draw());
    }

    // play 5 cards from hand
    for (int i=0; i<5; i++) {
        // remove card from hand and get a copy of the card
        temp = new Card(hand->discardFromHand());
        
        // call play(), get the order, add order to the order list, add the card to the deck
        newOrder = new Order(temp->play());
        orderList->addToList(*newOrder);
        gameDeck->addToDeck(*temp);
    }

    // delete pointers
    delete hand;
    delete gameDeck;
    delete orderList;
    delete temp;
    delete newOrder;
    temp = NULL;
    newOrder = NULL;
    gameDeck = NULL;
    hand = NULL;
    orderList = NULL;

    return 0;
}