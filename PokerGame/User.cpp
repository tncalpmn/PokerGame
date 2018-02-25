//
//  User.cpp
//  PokerGame
//
//  Created by Tunc Alpman on 05/12/2017.
//  Copyright © 2017 Tunc Alpman. All rights reserved.
//

#include "User.hpp"
#include "Card.hpp"
#include <string>
#include <iostream>

using namespace std;

User::User(){

    this->name = "";
    this->chips = Chips(50,30,20,10,4,2);
    this->folded = false;
    this->amoundPutOnCurrentRound = 0;
    this->decision = "i";
    this->rank = 0;
}

void User::addCurrentRoundMoney(int amount){
    
    amoundPutOnCurrentRound = amoundPutOnCurrentRound + amount;
    
}

void User::initCurrentRoundMoney(){
    
    this->amoundPutOnCurrentRound = 0;
    
}

void User::setDecision(string stand){
    
    this->decision = stand;
    
}

int User::getRank(){
    return this->rank;
}

void User::addRank(int rank){
    
    this->rank = this->rank + rank;
    
}

void User::initDecisions(){
    this->decision = "i";
}

string User::getDecision(){
    return this->decision;
}

void User::setName(string name){

    this->name = name;

}

bool User::isFolded(){
    return this->folded;
}

void User::setFold(bool fld){
    this->name = fld;
}

string User::getName(){
    return this->name;
}

void User::setBlind(bool small, bool big){
    
    this->smallBlind = small;
    this->bigBlind = big;
    
}

void User::setId(unsigned int id){
    
    this->id = id;
    
}

unsigned int User::getId(){
    
    return this->id;
    
}

Chips& User::getChips(){
    
    return this->chips;
    
}

Card* User::getCards(){
    
    return this->cards;
    
}

void User::setCards(Card card1, Card card2){ // ONLY FOR DEBUGGING!!!!
    
    this->cards[0] = card1;
    this->cards[1] = card2;
    
}

void User::setRandomCards(Round &curRnd){
    
    int seed = static_cast<int>(time(0)); // Seed for Random Number Generator
    srand(seed);
    
    for(int i = 0;i<2;i++){
        int randNum = (rand() % (curRnd.deck.size() + 1));
        this->cards[i] = curRnd.deck[randNum];
        this->cards[i].setAsUsersCard();
        curRnd.deck.erase(curRnd.deck.begin() + randNum);
    }
    
}

void User::getPlayerInfo(){
    cout << "Player Name: "<<this->name << endl;
    cout << "Player Money: "<< endl;
    this->chips.getChipInfo();
    for(Card card : this->cards){ 
        card.getCardInfo();
    }
    
}
