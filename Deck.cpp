#include "Deck.h"

Deck::Deck() : pos(0) {
    deck.reserve(deckSize);
    for(int i = 1; i <= 4; i++) {
        for(int j = 1; j <= 13; j++) {
            deck.push_back(new Card(i, j));
        }
    }
}

Deck::~Deck() {
    for(auto i : deck) {
        delete i;
    }
}

void Deck::shuffle() {
    for(long long unsigned i = 0; i < deck.size(); i++) {
        std::swap(deck[i], deck[rand()%deck.size()]);
    }
/*
    deck[0] = new Card(1, 4);
    deck[1] = new Card(2, 4);
    deck[2] = new Card(3, 4);
    deck[3] = new Card(4, 4);
*/
}

Card* Deck::getCard() {
    if(pos >= deckSize) {
        shuffle();
        pos = 0;
    }
    return deck[pos++];
}
