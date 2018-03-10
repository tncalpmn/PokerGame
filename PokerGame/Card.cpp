//
//  Card.cpp
//  PokerGame
//
//  Created by Tunc Alpman on 05/12/2017.
//  Copyright © 2017 Tunc Alpman. All rights reserved.
//

#include "Card.hpp"
#include <string>
#include <iostream>

using namespace std;

Card::Card(){
    this->number  = -1;
    this->suit = 'n';
    this->value = 0;
}

Card::Card(char suit, int number){
    this->number  = number;
    this->suit = suit;
    this->value = (number == 1) ? 14 : number; // A has actually bigger value than all other cards therefore its value is equaled to maxVal + 1 (13(K) + 1)
}

int Card::getNumber(){
    return this->number;
}

int Card::getValue(){
    return this->value;
}

char Card::getSuit(){
    return this->suit;
}

void Card::getCardInfo(){
    cout << "   - Number: "<< this->number <<endl;
    cout << "   - Suit: "<< this->suit <<endl;
}

bool Card::isEqual(Card crd, bool isSuitRelevant){ // Compares two cards depending on the switch "isSuitRelevant". If Suit is not relevant only numbers will be compared
    if(isSuitRelevant)
        return this->number == crd.getNumber() && this->suit == crd.getSuit();
    else
        return this->number == crd.getNumber();
}
