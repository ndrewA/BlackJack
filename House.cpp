#include "House.h"

bool House::giveCards(float& multiplier, Hand* curHand) {
    deck->shuffle();
    hands.push_back(curHand);

    hands[0]->addCard();
    hands[0]->addCard();
    dealer->addCard();

    std::cout << "DEALERS first card: ";
    std::cout << dealer->getHand()->getCards().back()->getName() << std::endl;

    dealer->addCard();

    if(hands[0]->getPoints() ==  21) {
        if(dealer->getScore() == 21) {
            std::cout << "YOU and the DEALER have TIED ";
            for(auto i : hands[0]->getCards()) std::cout << i->getName() << "; ";
            std::cout << std::endl;
            for(auto i :  hands) {
                delete i;
            }
            hands.clear();
            dealer->getNewHand();
            multiplier = 1;
        } else {
            std::cout << "YOU have WON with hand: ";
            for(auto i : hands[0]->getCards()) std::cout << i->getName() << "; ";
            std::cout << std::endl;
            for(auto i :  hands) {
                delete i;
            }
            hands.clear();
            dealer->getNewHand();
            multiplier = 1.5;
        }
        return false;
    }
    return true;
}

void House::splitHands(Hand* curHand, std::unordered_set<Hand*>& validHands) {
    validHands.insert(hands[0]);

    std::string answer = "placeholder";

    long long unsigned iter = 0;

    while((answer != "no") && (iter < hands.size())) {
        if((hands[iter]->getCards()[0]->getNum() != 1) &&
           (hands[iter]->getCards()[1]->getNum() != 1) &&
           (hands[iter]->getCards()[0]->getNum() == hands[iter]->getCards()[1]->getNum())) {

            std::cout << "YOUR HAND: ";
            for(auto i : hands[iter]->getCards()) std::cout << i->getName() << "; ";
            std::cout << "SCORE = " << hands[0]->getPoints() << std::endl;
            answer = "placeholder";
            while(answer != "yes" && answer != "no") {
                std::cout << "SPLIT? yes/no" << std::endl;
                std::cin >> answer;
            }
            if(answer == "yes") {
                Hand* newHand = new Hand(deck);
                newHand->addSpecificCard(curHand->removeCard());
                newHand->addCard();
                curHand->addCard();
                hands.push_back(newHand);
                curHand = newHand;
                validHands.insert(curHand);
            }
        }
        iter++;
    }
}

bool House::doubleDown(float& multiplier, std::unordered_set<Hand*>& validHands) {
    std::unordered_set<Hand*>::const_iterator hand = validHands.cbegin();
    while(hand != validHands.end()) {
        std::string answer = "placeholder";
        std::cout << "YOUR HAND: ";
        for(auto i : (*hand)->getCards()) std::cout << i->getName() << "; ";
        std::cout << "with SCORE = " << (*hand)->getPoints() << std::endl;
        while(answer != "yes" && answer != "no") {
            std::cout << "DOUBLE DOWN? yes/no" << std::endl;
            std::cin >> answer;
        }
        if(answer == "yes") {
            (*hand)->addCard();
            std::cout << "YOUR HAND: ";
            for(auto i : (*hand)->getCards()) std::cout << i->getName() << "; ";
            std::cout << "with SCORE = " << (*hand)->getPoints() << std::endl;
            if((*hand)->getPoints() > 21){
                hands.erase(std::find(hands.begin(), hands.end(), *hand));
                multiplier -= 4;
            } else {
                hands.push_back(new Hand(deck));
                hands.back()->addSpecificCard((*hand)->getCards()[0]);
                hands.back()->addSpecificCard((*hand)->getCards()[1]);
                hands.back()->addSpecificCard((*hand)->getCards()[2]);
                }
            hand = validHands.erase(hand);
        } else ++hand;
    }

    if(hands.empty()) {
        dealer->getNewHand();
        return false;
    }

    return true;
}

bool House::playPlayer(float& multiplier, std::unordered_set<Hand*>& validHands) {
    std::string answer = "hit";

    while(answer == "hit" || answer != "stand") {
        std::unordered_set<Hand*>::const_iterator hand = validHands.cbegin();
        while(hand != validHands.end()) {
            std::cout << "YOUR HAND: ";
            for(auto i : (*hand)->getCards()) std::cout << i->getName() << "; ";
            std::cout << "with SCORE = " << (*hand)->getPoints() << std::endl;
            std::cout << "HIT? hit/stand" << std::endl;
            std::cin >> answer;
            if(answer == "hit") {
                (*hand)->addCard();
                if((*hand)->getPoints() > 21) {
                    std::cout << "YOU have hand: ";
                    for(auto i : (*hand)->getCards()) std::cout << i->getName() << "; ";
                    std::cout << "with SCORE = " << (*hand)->getPoints() << std::endl;
                    hands.erase(std::find(hands.begin(), hands.end(), *hand));
                    multiplier -= 2;
                    hand = validHands.erase(hand);
                    if(hand == validHands.end()) answer = "stand";
                } else if((*hand)->getPoints() == 21) {
                    std::cout << "YOU have hand: ";
                    for(auto i : (*hand)->getCards()) std::cout << i->getName() << "; ";
                    std::cout << "with SCORE = " << (*hand)->getPoints() << std::endl;
                    hand = validHands.erase(hand);
                    if(hand == validHands.end()) answer = "stand";
                } else ++hand;
            } else ++hand;
        }
    }

    return !hands.empty();
}

bool House::playDealer(float& multiplier) {
    std::string answer = "hit";
    while(answer != "stand")
        answer = dealer->makeTurn();

    if(dealer->getScore() > 21) {
        std::cout << "DEALER has LOST with hand: ";
        for(auto i : dealer->getHand()->getCards()) std::cout << i->getName() << "; ";
        std::cout << "with SCORE: " << dealer->getScore() << std::endl;
        for(auto i :  hands) {
            delete i;
        }
        multiplier += 2*hands.size();
        hands.clear();
        dealer->getNewHand();
        return false;
    }
    return true;
}

void House::compareHands(float& multiplier) {
    for(auto hand : hands) {
        std::cout << "your hand with hand SCORE = " << hand->getPoints() << " has ";
        if(dealer->getScore() == hand->getPoints()) {
            std::cout << "TIED with dealers hand: ";
            for(auto i : dealer->getHand()->getCards()) std::cout << i->getName() << "; ";
            std::cout << "with SCORE: " << dealer->getScore() << std::endl;
        } else {
            if(hand->getPoints() > dealer->getScore()) {
                std::cout << "WON";
                multiplier += 2;
            } else {
                std::cout << "LOST";
                multiplier -= 2;
            }
            std::cout << " against the dealers hand: ";
            for(auto i : dealer->getHand()->getCards()) std::cout << i->getName() << "; ";
            std::cout << "with SCORE: " << dealer->getScore() << std::endl;
        }
    }
    for(auto i : hands) {
        delete i;
    }
    hands.clear();
    dealer->getNewHand();
}

float House::playRound() {
    float multiplier = 0;
    Hand* curHand = new Hand(deck);
    bool continueGame = giveCards(multiplier, curHand);
    if(continueGame) {
        std::unordered_set<Hand*> validHands;
        splitHands(curHand, validHands);
        continueGame = doubleDown(multiplier, validHands);
        if(continueGame) {
            if(!validHands.empty()) continueGame = playPlayer(multiplier, validHands);
            continueGame = playDealer(multiplier);
            if(continueGame) compareHands(multiplier);
        }
    }
    return multiplier;
}

void House::playBlackJack(float& totalMoney) {
    std::cout << "your total money = " << totalMoney << std::endl;
    std::string cashOut = "no";
    while((totalMoney > 0) && (cashOut == "no" || cashOut != "yes")) {
        if(cashOut == "no") {
            std::string in = "placeholder";
            while(true) {
                std::cout << "bet number?" << std::endl;
                std::cin >> in;
                if(in.find_first_not_of("0123456789") == std::string::npos &&
                   (std::stoi(in) <= totalMoney && std::stoi(in) > 0)) break;
            }
            int bet = std::stoi(in);
            totalMoney += bet*playRound()/2;
            std::cout << "your total money = " << totalMoney << std::endl;
        }
        if(totalMoney > 0) {
            std::cout << "cash out? yes/no" << std::endl;
            std::cin >> cashOut;
        }
    }
}
