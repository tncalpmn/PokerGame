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
    this->isUsersCard = false;
}

Card::Card(char suit, int number){
    this->number  = number;
    this->suit = suit;
    this->isUsersCard = false;
    this->value = number == 1 ? 14 : number; // A has actually bigger value than all other cards therefore its value is equaled to maxVal + 1 (13(K) + 1)
}

Card::Card(char suit, int number, bool isUsersCard){
    this->number  = number;
    this->suit = suit;
    this->isUsersCard = isUsersCard;
    this->value = number == 1 ? 14 : number;
}

void Card::getCardInfo(){

    cout << "   - Number: "<< this->number <<endl;
    cout << "   - Suit: "<< this->suit <<endl;
    cout << "        Is Users Card? : "<< this->isUsersCard <<endl;

}

int Card::getNumber(){
    return this->number;
}

int Card::getValue(){
    return this->value;
}

bool Card::isEqual(Card crd, bool isSuitRelevant){
   
    if(isSuitRelevant)
        return this->number == crd.getNumber() && this->suit == crd.getSuit();
    else
        return this->number == crd.getNumber();
    
}

char Card::getSuit(){
    return this->suit;
}

bool Card::isThisUsersCard(){
    return this->isUsersCard;
}

void Card::setAsUsersCard(){
    this->isUsersCard = true;
}
