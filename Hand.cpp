#include "Hand.h"

void Hand::clearHand() {
    points = 0;
    aces = std::unordered_set<Card*>();
    cards = std::vector<Card*>();
}

void Hand::addCard() {
    cards.push_back(deck->getCard());
    if(cards.back()->getNum() == 1) aces.insert(cards.back());
    points += cards.back()->getVal();
    if(points > 21) {
        while(!aces.empty() && points > 21) {
            points -= 10;
            aces.erase(aces.begin());
        }
    }
}

void Hand::addSpecificCard(Card* c) {
    cards.push_back(c);
    if(c->getNum() == 1) aces.insert(c);
    points+=c->getVal();
}

Card* Hand::removeCard() {
    Card* lastCard = cards.back();
    points -= lastCard->getVal();
    if(lastCard->getNum() == 1) aces.erase(lastCard);
    cards.pop_back();
    return lastCard;
}
