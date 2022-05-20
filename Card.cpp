#include "Card.h"

Card::Card(int ct, int cn) : cardNum(cn), cardType(ct) {
    if(cardNum == 1) {
        value = 11;
    } else if(cardNum >= 10) {
        value = 10;
    } else value = cardNum;

    switch(cardNum) {
        case 1 :
            name = "ace";
            break;
        case 11 :
            name = "jack";
            break;
        case 12 :
            name = "queen";
            break;
        case 13 :
            name = "king";
            break;
        default:
            name = std::to_string(cardNum);
            break;
    }
    switch(cardType) {
        case 1 :
            name.append(" of clubs");
            break;
        case 2 :
            name.append(" of diamonds");
            break;
        case 3 :
            name.append(" of hearts");
            break;
        case 4 :
            name.append(" of spades");
            break;
    }
}
