#include "Cards.cpp"

// Card driver
int main() {
    Deck gameDeck(40);
    Hand hand;
    for (int i=0; i<5; i++) {
        hand.addToHand(gameDeck.draw());
    }
    for (int i=0; i<5; i++) {
        hand.discardFromHand().play();
    }
    return 0;
}