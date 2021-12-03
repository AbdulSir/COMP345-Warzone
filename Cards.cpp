#include "Cards.h"
#include <iostream>
using namespace std;
#include <string>
#include <list>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Card class
Card::Card() {}

Card::Card(string type) {
    cardType = type;
}

Card::Card(const Card& obj): cardType(obj.cardType) {}

Card& Card::operator= (const Card& card) {
    cardType = card.cardType;
    return *this;
}

Order* Card::play() {
    if (cardType == "airlift") {
        return new Airlift();
    }
    if (cardType == "bomb") {
        return new Bomb();
    }
    if (cardType == "blockade") {
        return new Blockade();
    }
    if (cardType == "diplomacy") {
        return new Negotiate();
    }
    return NULL;
}

// Deck class

Deck::Deck() {}

Deck::~Deck() {
    for(Card *ptr : deck) {
        delete ptr;
    }
}

Deck::Deck(const Deck& obj): deck(obj.deck) {}

Deck& Deck::operator= (const Deck& anotherDeck) {
    deck = anotherDeck.deck;
    return *this;
}

Deck::Deck(int deckLength) {
    Card* cardToAdd;
    srand (time (0));
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
        cardToAdd = new Card(cardType);
        deck.push_back(cardToAdd);
    }
    delete cardToAdd;
    cardToAdd = NULL;
}

void Deck::addToDeck(Card* c) {
    deck.push_back(c);
};

Card* Deck::draw() {
    Card* temp(deck.front());
    deck.pop_front();
    return temp;
};

// Hand class

Hand::Hand() {}

Hand::~Hand() {
    for(Card *ptr : handDeck) {
        delete ptr;
    }
}

Hand::Hand(const Hand& obj): handDeck(obj.handDeck) {}

Hand& Hand::operator= (const Hand& hand) {
    handDeck = hand.handDeck;
    return *this;
}

void Hand::removeCardFromHand(string type) {
    list<Card*>::iterator it;
    for (it = handDeck.begin(); it != handDeck.end(); ++it){
        if ((*it)->cardType == type) {
            handDeck.erase(it);
            break;
        }
    }
};

Card Hand::discardFromHand() {
    Card temp(*handDeck.front());
    handDeck.pop_front();
    return temp;
};

void Hand::addToHand(Card* c) {
    handDeck.push_back(c);
}

// stream insertion operators
ostream & operator<< (ostream &out, const Card &c) {
    out << "Card: " << c.cardType << endl;
    return out;
}

ostream & operator<< (ostream &out, Deck &c) {
    for (auto card: c.deck) {
        if (card) {
            out << *card << endl;
        }
    }
    return out;
}

ostream & operator<< (ostream &out, Hand &h) {
    for (auto card: h.handDeck) {
        if (card) {
            out << *card << endl;
        }
    }
    return out;
}
