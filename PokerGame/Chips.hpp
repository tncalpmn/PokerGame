//
//  Chips.hpp
//  PokerGame
//
//  Created by Tunc Alpman on 07/12/2017.
//  Copyright © 2017 Tunc Alpman. All rights reserved.
//

#ifndef Chips_hpp
#define Chips_hpp

#include <stdio.h>

class Chips {
    
private:
    int one;
    int five;
    int ten;
    int twenty;
    int fifty;
    int hundert;
public:
    Chips();
    Chips(int,int,int,int,int,int);
    int sumOfChips();
    void addChips(Chips);
    void removeChips(Chips);
    void getChipInfo();
    void resetChips();
    int getOnes();
    int getFives();
    int getTens();
    int getTwentys();
    int getFiftys();
    int getHunderts();
};

#endif /* Chips_hpp */
