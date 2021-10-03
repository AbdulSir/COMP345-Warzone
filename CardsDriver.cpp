#include "Cards.cpp"

// Card driver to demonstrate the implemented functions

int main() {
    // define gameDeck with pointer type
    Deck *gameDeck;
    gameDeck = new Deck(40);
    // define hand with pointer type
    Hand* hand;
    hand = new Hand();
    
    OrderList* orderList;
    orderList = new OrderList();

    // add 5 cards to hand
    for (int i=0; i<5; i++) {
        hand->addToHand(gameDeck->draw());
    }
    // play 5 cards from hand
    for (int i=0; i<5; i++) {
        Card* temp;
        // remove card from hand and get a copy of the card
        temp = new Card(hand->discardFromHand());
        Order* newOrder;
        // call play(), get the order, add order to the order list, add the card to the deck
        newOrder = new Order(temp->play());
        orderList->addToList(*newOrder);
        gameDeck->addToDeck(*temp);

        // delete pointers
        delete temp;
        delete newOrder;
        temp = NULL;
        newOrder = NULL;
    }

    // delete pointers
    delete hand;
    delete gameDeck;
    delete orderList;
    gameDeck = NULL;
    hand = NULL;
    orderList = NULL;
    
    return 0;
}