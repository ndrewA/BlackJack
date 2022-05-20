#ifndef DEALER_H
#define DEALER_H

#include "Hand.h"

class Dealer{
    private:
        Hand* hand;
    public:
        Dealer(Deck* d) : hand(new Hand(d)) {}
        ~Dealer() {delete hand;}
        void getNewHand() {hand->clearHand();}
        void addCard() {return hand->addCard();}
        std::string makeTurn();
        int getScore() {return hand->getPoints();}
        Hand* getHand() {return hand;}
};

#endif // DEALER_H
