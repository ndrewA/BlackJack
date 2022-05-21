#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
    private:
        int cardNum;
        int cardType;
        int value;
        std::string name;
    public:
        Card(int ct, int cn);
        ~Card() {}
        int getType() {return cardType;}
        int getNum() {return cardNum;}
        int getVal() {return value;}
        std::string getName() {return name;}
};

#endif // CARD_H

