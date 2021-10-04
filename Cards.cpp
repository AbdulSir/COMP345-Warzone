#include "Cards.h"
#include <iostream>
using namespace std;
#include <string>
#include <list>

// dummy classes
Order::Order() {};

OrderList::OrderList() {};

void OrderList::addToList(Order o) {
    cout << "Add an order to list" << endl;
};

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

Order Card::play() {
    Order newOrder;
    cout << "Playing " << cardType << " card." << endl;
    return newOrder;
}

ostream & operator << (ostream &out, const Card &c) {
    out << c.cardType << endl;
    return out;
}
 
istream & operator >> (istream &in,  Card &c) {
    cout << "Enter card type ";
    in >> c.cardType;
    return in;
}

// Deck class

Deck::Deck() {}
Deck::Deck(const Deck& obj): deck(obj.deck) {}

Deck& Deck::operator= (const Deck& anotherDeck) {
    deck = anotherDeck.deck;
    return *this;
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

ostream & operator << (ostream &out, Deck &c) {

    for (list<Card>::iterator it = c.deck.begin(); it!= c.deck.end(); ++it) {
        out << it->cardType << endl;
    }
    return out;
}
 
istream & operator >> (istream &in,  Deck &c) {
    while (true) {
        string type;
        cout << "Type end to exit" << endl;
        cout << "Enter card type ";
        in >> type;
        if (type.compare("end") == 0) {
            break;
        } else {
            c.addToDeck(Card(type));
        }
    }
    return in;
}

Card Deck::draw() {
    Card temp(deck.front());
    deck.pop_front();
    return temp;
};

// Hand class

Hand::Hand() {}

Hand::Hand(const Hand& obj): handDeck(obj.handDeck) {}

Hand& Hand::operator= (const Hand& hand) {
    handDeck = hand.handDeck;
    return *this;
}

Card Hand::discardFromHand() {
    Card temp(handDeck.front());
    handDeck.pop_front();
    return temp;
};

void Hand::addToHand(Card c) {
    handDeck.push_back(c);
}

ostream & operator << (ostream &out, Hand &h) {

    for (list<Card>::iterator it = h.handDeck.begin(); it!= h.handDeck.end(); ++it) {
        out << it->cardType << endl;
    }
    return out;
}
 
istream & operator >> (istream &in,  Hand &h) {
    while (true) {
        string type;
        cout << "Type end to exit" << endl;
        cout << "Enter card type ";
        in >> type;
        if (type.compare("end") == 0) {
            break;
        } else {
            h.addToHand(Card(type));
        }
    }
    return in;
}
