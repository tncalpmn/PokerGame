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
}

Card::Card(char suit, int number){
    this->number  = number;
    this->suit = suit;
}

void Card::getCardInfo(){

    cout << "   - Number: "<< this->number <<endl;
    cout << "   - Suit: "<< this->suit <<endl;

}

int Card::getNumber(){
    return this->number;
}

char Card::getSuit(){
    return this->suit;
}
