//
//  Round.cpp
//  PokerGame
//
//  Created by Tunc Alpman on 05/12/2017.
//  Copyright © 2017 Tunc Alpman. All rights reserved.
//

#include "Round.hpp"
#include <string>
#include "Table.hpp"

using namespace std;

Round::Round(){

}

void Round::createNewDeck(){
    deck.clear();
    for(char suit: suits){
        for(int i = 0 ; i < numbersOfEachSuit ; i++){
            Card newCard(suit,i+1); // 1(A),2,3...11(J),12(Q),13(K)
            deck.push_back(newCard);
        }
    }
}

void Round::startRound(Chips &moneyOnTable){
    
    moneyOnTable.resetChips();
    createNewDeck();

}



