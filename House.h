#ifndef HOUSE_H
#define HOUSE_H

#include "Hand.h"
#include "Deck.h"
#include "Dealer.h"

#include <iostream>
#include <algorithm>

class House {
    private:
        Deck* deck;
        std::vector<Hand*> hands;
        Dealer* dealer;

    private:
        bool giveCards(float& multimplier, Hand* curHand);
        bool doubleDown(float& multiplier, std::unordered_set<Hand*>& validHands);
        void splitHands(Hand* curHand, std::unordered_set<Hand*>& validHands);
        bool playPlayer(float& multimplier, std::unordered_set<Hand*>& validHands);
        bool playDealer(float& multimplier);
        void compareHands(float& multimplier);

        float playRound();

    public:
        House() : deck(new Deck()), dealer(new Dealer(deck)) {}
        ~House() {delete deck; delete dealer;}
        void playBlackJack(float& totalMoney);
};

#endif // HOUSE_H

