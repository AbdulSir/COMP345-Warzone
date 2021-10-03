#include "Cards.cpp"

// Card driver
int main() {
    // define gameDeck with pointer type
    Deck *gameDeck;
    gameDeck = new Deck(40);
    // define hand with pointer type
    Hand* hand;
    hand = new Hand();

    // add 5 cards to hand
    for (int i=0; i<5; i++) {
        hand->addToHand(gameDeck->draw());
    }
    // play 5 cards from hand
    for (int i=0; i<5; i++) {
        hand->discardFromHand().play();
    }

    // delete pointers
    delete hand;
    delete gameDeck;
    gameDeck = NULL;
    hand = NULL;
    return 0;
}