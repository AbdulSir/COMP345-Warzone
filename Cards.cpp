#include <iostream>
using namespace std;
#include "Cards.h"
#include<string>
#include<list>

Card::Card(string type) {
    cardType = type;
}

string Card::play() {
    cout << "Playing " << cardType << "card." << endl;
    return cardType;
}

Deck::Deck(int deckLength) {
    for (int i=0; i<deckLength; i++) {
        int random = rand() % 5;
        string cardType;
        switch (random) {
            case 0:
                cardType = "bomb";
            break;
            case 1:
                cardType = "reinforcement";
            break;
            case 2:
                cardType = "blockade";
            break;
            case 3:
                cardType = "airlift";
            break;
            default:
                cardType = "diplomacy";
        }
        Card cardToAdd(cardType);
        deck.push_back(cardToAdd);
    }
}

void Deck::addToDeck(Card c) {
    deck.push_back(c);
};

Card Deck::draw() {
    Card temp(deck.front().cardType);
    deck.pop_front();
    return temp;
};

Card Hand::discardFromHand() {
    Card temp(handDeck.front().cardType);
    handDeck.pop_front();
    return temp;
};

void Hand::addToHand(Card c) {
    handDeck.push_back(c);
}
