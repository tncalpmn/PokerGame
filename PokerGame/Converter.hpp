//
//  Converter.hpp
//  PokerGame
//
//  Created by Tunc Alpman on 19/03/2018.
//  Copyright © 2018 Tunc Alpman. All rights reserved.
//

#ifndef Converter_hpp
#define Converter_hpp

#include <stdio.h>
#include <iostream>

#include "Chips.hpp"
#include "Globals.hpp"

using namespace std;



class Converter {
    
public:
    static bool removeAmountAsChips(int,Chips&,Chips);
    static Chips& changeNextAvailableCoinsToOnes(Chips&);
    static Chips amountToChipConverter(int, Chips);
};



#endif /* Converter_hpp */
