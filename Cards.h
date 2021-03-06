#pragma once

#include "Orders.h"
#include "Player.h"
#include<string>
#include<list>
#include<iostream>
using namespace std;

class Order;
class Player;

class Card {
public:
    string cardType;
    Card();
    // default constructor to set cardType
    Card(string type);
    // copy constructor for Card
    Card(const Card &obj);
    // overloaded assignment operator
    Card& operator= (const Card& card);
    // play the card
    Order* play();
    // stream insertion operators
    friend ostream & operator<< (ostream &out, const Card &c);
};

class Deck {
public:
    list<Card*> deck;
    Deck();
    // desctructor
    ~Deck();
    // copy constructor for Deck
    Deck(const Deck& obj);
    // constructor, will randomly generate cards based on deckLength
    Deck(int deckLength);
    // overloaded assignment operator
    Deck& operator= (const Deck& deck);
    // remove card from deck and return the card
    Card* draw();
    // add card to collection of deck
    void addToDeck(Card* c);
    // stream insertion operators
    friend ostream & operator<< (ostream &out, Deck &c);
};

class Hand {
public:
    list<Card*> handDeck;
    Hand();
    // destructor
    ~Hand();
    // copy constructor for Hand
    Hand(const Hand& obj);
    // overloaded assignment operator
    Hand& operator= (const Hand& hand);
    // remove card from hand and return the card
    Card discardFromHand();
    void removeCardFromHand(string cardType);
    // add card to collection of hand
    void addToHand(Card* c);
    // stream insertion operators
    friend ostream & operator<< (ostream &out, Hand &h);
};
