#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include "Deck.h"

#include <unordered_set>

class Hand {
    private:
        Deck* deck;
        std::vector<Card*> cards;
        int points;
        std::unordered_set<Card*> aces;
    public:
        Hand(Deck* d) : deck(d), points(0) {}
        ~Hand() {}
        void clearHand();
        void addCard();
        void addSpecificCard(Card* c);
        int getPoints() {return points;}
        Card* removeCard();
        std::vector<Card*> getCards() {return cards;}
};

#endif // HAND_H

