//
//  Card.hpp
//  PokerGame
//
//  Created by Tunc Alpman on 05/12/2017.
//  Copyright © 2017 Tunc Alpman. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>

class Card {
private:
    int number;
    char suit;
    int value;
    
public:
    void getCardInfo();
    Card();
    Card(char,int);
    int getNumber();
    int getValue();
    char getSuit();
    bool isEqual(Card,bool);
    
    bool operator<(const Card& crd) const // This operator overload is necesaary in order to store this object in a Map, in other way we define a sort condition
    {
        if (crd.number < this->number)
            return true;
        else
            return false;
    }
    
};

#endif /* Card_hpp */
