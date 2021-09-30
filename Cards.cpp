#include <iostream>
using namespace std;
#include "Cards.h"
#include<string>
#include<list>

class Card {
    public:
        string cardType;
        Card(string type) {
            cardType = type;
        }
        string Card::play() {
            cout << "Playing " << cardType << "card." << endl;
            return cardType;
        };
};

class Deck {
    public:
        static list<Card> deck;
        Deck() {};
        Deck(int deckLength) {
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
                Card cardToAdd = Card(cardType);
                deck.push_front(cardToAdd);
            }
        };
        Card Deck::draw() {
            Card temp = deck.front();
            deck.pop_front();
            return temp;
        };
        void addToDeck(Card c) {
            deck.push_back(c);
        };
};

class Hand {
    list<Card> handDeck;
    Card discardFromHand() {
        Card temp = handDeck.front();
        handDeck.pop_front();
        return temp;
    };
    void addToHand(Card c) {
        handDeck.push_back(c);
    }
};