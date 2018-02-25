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
    bool isUsersCard;
    
public:
    void getCardInfo();
    Card();
    Card(char,int);
    Card(char,int,bool); // Debug Purposes
    int getNumber();
    int getValue();
    char getSuit();
    bool isEqual(Card,bool);
    bool isThisUsersCard();
    void setAsUsersCard();
    
    
};

#endif /* Card_hpp */
