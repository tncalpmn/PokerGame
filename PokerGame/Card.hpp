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
    
public:
    void getCardInfo();
    Card();
    Card(char,int);
    int getNumber();
    char getSuit();
    
};

#endif /* Card_hpp */
