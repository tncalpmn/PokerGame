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
    
    static bool sortNumbers (Card first,Card second) { return (first.getNumber() < second.getNumber());}
    static bool sortNumeric (int first,int second) { return (first < second);}
    static bool sortSuits (Card first,Card second) { return (first.getSuit() < second.getSuit());}
    static int max (int first,int second) {if(first > second) return first; else return second;}
    static bool containsNumber(vector<int> vec, int num ){return find(vec.begin(), vec.end(), num) != vec.end();}
    static bool containsCard(vector<Card> vec, Card crd, bool isSuitRelevant){ for(Card v : vec){ if(v.isEqual(crd,isSuitRelevant)){return true;}}return false;}

    Decider(vector<Card>);
};

#endif /* Decider_hpp */
