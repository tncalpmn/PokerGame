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
#include "User.hpp"
#include <vector>
#include <map>

using namespace std;

class Decider {
    
private:
    vector<Card> all7Cards;
    vector<Card> highestCombination;
    map<char, int> numbOfSuits;
    map<int, int> numbOfNumbers;

    void setHighestFive();
    int getConsecutiveHighCard(Card, Card);
    map<char, int> countSuits();
    map<Card,int> groupCardsWithNums(vector<Card>);
    char atLeastFiveSuit();
    char atLeastFiveSuits = 'n';
    bool isConsecutive(vector<Card>);
    map<int, int>  countNumbers(vector<Card>);
    
public:

    Decider(vector<Card>);
    bool isRoyalFlush();
    bool isStraightFlush();
    bool is4ofaKind();
    bool isFullHouse();
    bool isFlush();
    bool isStraight();
    bool is3ofaKind();
    bool is2Pair();
    bool is1Pair();
    void setRankFor(User &usr);

};

#endif /* Decider_hpp */
