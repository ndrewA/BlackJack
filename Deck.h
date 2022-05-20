#ifndef DECK_H
#define DECK_H

#include "Card.h"

#include <vector>

class Deck {
    private:
        const int deckSize = 52;
        std::vector<Card*> deck;
        int pos;
    public:
        Deck();
        ~Deck();
        void shuffle();
        Card* getCard();
        //bool checkInDeck(Card* c) {find(deck.begin(), deck.end(), c) == deck.end() ? return true : return false;}
};


#endif // DECK_H
