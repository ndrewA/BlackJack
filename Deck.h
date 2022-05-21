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
};


#endif // DECK_H
