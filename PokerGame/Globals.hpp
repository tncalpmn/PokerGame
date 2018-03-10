//
//  Globals.hpp
//  PokerGame
//
//  Created by Tunc Alpman on 18/02/2018.
//  Copyright © 2018 Tunc Alpman. All rights reserved.
//

#ifndef Globals_h
#define Globals_h

static bool isDebuggerOn = false;           // For testing Functions and Classes a backdoor for debugging
const int SMALL_BLIND = 5;                  // Small Blind
const int BIG_BLIND = SMALL_BLIND * 2;      // Big Bling
const int8_t WEIGHT = 15;                   // Weight should be given to some variations (Ex: Full house, value of three numbers should have more weight then two number
                                            // 13-13-13-2-2 (197)> 12-12-12-A-A (194)
#endif /* Globals_h */
