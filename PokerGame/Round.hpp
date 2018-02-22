//
//  Round.hpp
//  PokerGame
//
//  Created by Tunc Alpman on 05/12/2017.
//  Copyright © 2017 Tunc Alpman. All rights reserved.
//

#ifndef Round_hpp
#define Round_hpp

#include <stdio.h>
#include <vector>
#include "Card.hpp"
#include "Chips.hpp"


using namespace std;


class Round {
 
public:
    vector<Card> deck;
    Round();
    void startRound(Chips&);
private:
    char suits[4] = {'s','h','d','c'};
    int numbersOfEachSuit = 13;
    void createNewDeck();
};



#endif /* Round_hpp */
