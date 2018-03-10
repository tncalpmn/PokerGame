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
    bool isConsecutive(vector<Card>);

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
    vector<Card> highestCombination;
    map<int, int>  countNumbers(vector<Card>);
    map<Card,int> groupCardsWithNums(vector<Card>);
    vector<Card> getAll7Cards();
    void setHighestFive();
    
    static bool sortNumbers (Card first,Card second) { return (first.getNumber() < second.getNumber());}
    static bool sortByValue (Card first,Card second) { return (first.getValue() > second.getValue());} // bigger to smaller
    static bool containsCard(vector<Card> vec, Card crd, bool isSuitRelevant){ for(Card v : vec){ if(v.isEqual(crd,isSuitRelevant)){return true;}}return false;}

    Decider(vector<Card>);
};

#endif /* Decider_hpp */
