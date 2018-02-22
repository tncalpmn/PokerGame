//
//  Debugger.hpp
//  PokerGame
//
//  Created by Tunc Alpman on 18/02/2018.
//  Copyright © 2018 Tunc Alpman. All rights reserved.
//

#ifndef Debugger_h
#define Debugger_h

#include <string>
#include <iostream>
#include "Table.hpp" // Card, Chips, Round, User
#include "Decider.hpp"

class Debugger {
    
    bool isOn;
    
    void testFunction_removeAmountAsChips();
    void testFunction_amountToChipConverter();
    void testClass_Decider();
    Table testTable;
    
public:
    Debugger();
    Debugger(bool);
    void start();
    bool getStatus();
    void setStatus(bool);
};

#endif /* Debugger_h */
