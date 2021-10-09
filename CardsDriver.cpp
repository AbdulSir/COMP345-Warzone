#include "Cards.h"
#include <iostream>
using namespace std;

// Card driver to demonstrate the implemented functions

int main() {
    // define gameDeck with pointer type
    Deck* gameDeck = new Deck(10);
    // define hand with pointer type
    Hand *hand = new Hand();
    // define dummy order list class with pointer type
    OrderList *orderList = new OrderList();
    // define a temp card class for copying later
    Card *temp;
    // define a temp order class for copying later
    Order *newOrder;

    cout << "cards in game deck now:" << endl << *gameDeck << endl;
    // draw 5 cards from game deck and add to hand
    for (int i=0; i<5; i++) {
        temp = gameDeck->draw();
        hand->addToHand(temp);
        cout << "cards in game deck now:" << endl << *gameDeck << endl;
        cout << "cards in hand now" << endl << *hand << endl;
    }

    // play 5 cards from hand
    for (int i=0; i<5; i++) {
        // remove card from hand and get a copy of the card
        temp = new Card(hand->discardFromHand());
        cout << "cards in hand now" << endl << *hand << endl;
        // call play(), get the order, add order to the order list, add the card to the deck
        newOrder = new Order(temp->play());
        orderList->addToList(*newOrder);
        cout << endl;
        gameDeck->addToDeck(temp);
        cout << "cards in game deck now:"<< endl << *gameDeck << endl;
    }

    // delete pointers
    delete orderList;
    delete temp;
    delete newOrder;
    temp = NULL;
    newOrder = NULL;
    orderList = NULL;

    return 0;
}