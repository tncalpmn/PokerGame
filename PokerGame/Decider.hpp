//
//  Decider.hpp
//  PokerGame
//
//  Created by Tunc Alpman on 28/12/2017.
//  Copyright © 2017 Tunc Alpman. All rights reserved.
//

#ifndef Decider_hpp
#define Decider_hpp

#include <stdio.h>
#include <iostream>
#include "Card.hpp"
#include <vector>
#include <map>

using namespace std;

class Decider {
    
private:
    vector<Card> all7Cards;
    map<char, int> countSuits();
    map<char, int> numbOfSuits;
    map<int, int> numbOfNumbers;
    char atLeastFiveSuit();
    char atLeastFiveSuits = 'n';
    map<int, int>  countNumbers();
    bool isConsecutive(vector<int>);
   
public:
    bool isRoyalFlush();
    bool isStraightFlush();
    bool is4ofaKind();
    bool isFullHouse();
    bool isFlush();
    bool isStraight();
    bool is3ofaKind();
    bool is2Pair();
    bool is1Pair();
    
    
    Decider(vector<Card>);
    Decider();
};









#endif /* Decider_hpp */
