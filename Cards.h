#pragma once
#include<string>
#include<list>

class Card {
    public:
        string cardType;
        Card(string type);
        // execute the card
        string play();
};

class Deck {
    public:
        list<Card> deck;
        // randomly generate cards based on deckLength
        Deck(int deckLength);
        // remove card from deck and return the card
        Card draw();
        // add card to collection of deck
        void addToDeck(Card c);
};

class Hand {
    public:
        list<Card> handDeck;
        // remove card from hand and return the card
        Card discardFromHand();
        // add card to collection of hand
        void addToHand(Card c);
};
