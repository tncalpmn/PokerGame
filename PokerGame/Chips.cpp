//
//  Chips.cpp
//  PokerGame
//
//  Created by Tunc Alpman on 07/12/2017.
//  Copyright © 2017 Tunc Alpman. All rights reserved.
//

#include "Chips.hpp"
#include <iostream>
using namespace std;

Chips::Chips(){
    this->one = 0;
    this->five = 0;
    this->ten = 0;
    this->twenty = 0;
    this->fifty = 0;
    this->hundert = 0;
}

Chips::Chips(int one, int five, int ten, int twenty, int fifty, int hundert){
    this->one = one;
    this->five = five;
    this->ten = ten;
    this->twenty = twenty;
    this->fifty = fifty;
    this->hundert = hundert;
}

void Chips::addChips(Chips chipsToAdd){
    this->one = this->one  + (chipsToAdd.one);
    this->five = this->five+ (chipsToAdd.five);
    this->ten = this->ten + (chipsToAdd.ten);
    this->twenty = this->twenty+ (chipsToAdd.twenty);
    this->fifty = this->fifty + (chipsToAdd.fifty);
    this->hundert = this->hundert + (chipsToAdd.hundert);
}

// This function should be used cautiously, it should be first checked if the player has enougt money to be reduced.
void Chips::removeChips(Chips chipsToRemove){
    this->one = this->one  - (chipsToRemove.one);
    this->five = this->five - (chipsToRemove.five);
    this->ten = this->ten - (chipsToRemove.ten);
    this->twenty = this->twenty - (chipsToRemove.twenty);
    this->fifty = this->fifty - (chipsToRemove.fifty);
    this->hundert = this->hundert - (chipsToRemove.hundert);
}

int Chips::getOnes(){
    return this->one;
}
int Chips::getFives(){
    return this->five;
}
int Chips::getTens(){
    return this->ten;
}
int Chips::getTwentys(){
    return this->twenty;
}
int Chips::getFiftys(){
    return this->fifty;
}
int Chips::getHunderts(){
    return this->hundert;
}

void Chips::resetChips(){
    this->one = 0;
    this->five = 0;
    this->ten = 0;
    this->twenty = 0;
    this->fifty = 0;
    this->hundert = 0;
}

int Chips::sumOfChips(){
    return (1 * one) + (5 * five) + (10 * ten) + (20 * twenty) + (50 * fifty) + (100 * hundert);
}

void Chips::getChipInfo(){
    cout << "ONE: "<< one << " | FIVE: "<< five << " | TEN: "<< ten << " | TWENTY: "<< twenty<< " | FIFTY: "<< fifty << " | HUNDERT: " << hundert << " = " << sumOfChips() << endl;
}
