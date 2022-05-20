#include "Dealer.h"

std::string Dealer::makeTurn() {
    if(hand->getPoints() < 17) {
        hand->addCard();
        return "hit";
    }
    return "stand";
}
