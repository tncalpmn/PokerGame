//
//  Debugger.cpp
//  PokerGame
//
//  Created by Tunc Alpman on 18/02/2018.
//  Copyright © 2018 Tunc Alpman. All rights reserved.
//


#include "Debugger.hpp"
#include "Globals.hpp"


using namespace std;


Debugger::Debugger(){
    
}

void Debugger::start(){

    //testFunction_removeAmountAsChips();     // TEST 1
    //testFunction_amountToChipConverter();   // TEST 2
    testClass_Decider();                      // TEST 3
    
}

void Debugger::testFunction_removeAmountAsChips(){
    cout << "DEBUG_START: testFunction_removeAmountAsChips" << endl;
    Chips availableAmount = Chips(50,30,20,10,4,2);
    cout << "Before Reduction: "<< endl;
    availableAmount.getChipInfo();

    testTable.removeAmountAsChips(367, availableAmount , Chips(0,0,0,0,0,0));
    cout <<  "After Reduction: "<< endl;
    availableAmount.getChipInfo();
    cout << "DEBUG_END: testFunction_removeAmountAsChips" << endl;
}

void Debugger::testFunction_amountToChipConverter(){
    cout << "DEBUG_START:  testFunction_amountToChipConverter" << endl;
    // TODO
    cout << "DEBUG_END:  testFunction_amountToChipConverter" << endl;
}

void Debugger::testClass_Decider(){
    cout << "DEBUG_START: testClass_Decider" << endl;

    // suit s,c,d,h
    vector<Card> test7Cards;
    
    // Test_1 RoyalFlush Ex: (S_10, S_11, S_12, S_13, S_1, C_1, C_11)                   -> PASSED
    test7Cards.push_back(Card('c',12));
    test7Cards.push_back(Card('c',13));
    test7Cards.push_back(Card('c',1));      // Random
    test7Cards.push_back(Card('c',10));
    test7Cards.push_back(Card('d',4));      // Random
    test7Cards.push_back(Card('c',11));
    test7Cards.push_back(Card('c',9));
    
    Decider decider(test7Cards);
    cout << "Is this Combination a Royal Flush: ";
    decider.isRoyalFlush() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;
    
    // Test_2.1 Straight Flush                                                          -> PROGRESS
    test7Cards.clear();
    test7Cards.push_back(Card('c',3));
    test7Cards.push_back(Card('c',4));
    test7Cards.push_back(Card('c',5));
    test7Cards.push_back(Card('c',6));
    test7Cards.push_back(Card('d',4));      // Random
    test7Cards.push_back(Card('s',11));     // Random
    test7Cards.push_back(Card('c',2));
    
    // Test_2.2 Straight Flush
    test7Cards.clear();
    test7Cards.push_back(Card('s',13));
    test7Cards.push_back(Card('s',12));
    test7Cards.push_back(Card('d',1));
    test7Cards.push_back(Card('s',10));
    test7Cards.push_back(Card('s',11));
    test7Cards.push_back(Card('c',1));      // Random
    test7Cards.push_back(Card('s',2));      // Random
    
    // Test_2.3 Straight Flush
    test7Cards.clear();
    test7Cards.push_back(Card('h',3));
    test7Cards.push_back(Card('h',2));
    test7Cards.push_back(Card('h',1));
    test7Cards.push_back(Card('s',1));      // Random
    test7Cards.push_back(Card('c',1));      // Random
    test7Cards.push_back(Card('h',4));
    test7Cards.push_back(Card('h',5));
    
    // TODO 1) 10 11 12 13 A    2) 2,3,4,5,6 & 3,4,5,6,7 (HighCard)
    
    decider = Decider(test7Cards);
    cout << "Is this Combination a Straigt Flush: ";
    decider.isStraightFlush() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;
    
    // Test_3.1 4 of a Kind
    test7Cards.clear();
    test7Cards.push_back(Card('s',3));      // Random
    test7Cards.push_back(Card('d',1));
    test7Cards.push_back(Card('h',1));
    test7Cards.push_back(Card('s',1));
    test7Cards.push_back(Card('c',1));
    test7Cards.push_back(Card('h',3));      // Random
    test7Cards.push_back(Card('h',5));      // Random
    

    decider = Decider(test7Cards);
    cout << "Is this Combination a Four of a Kind: ";
    decider.is4ofaKind() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;
    
    // Test_4.1 Full House
    test7Cards.clear();
    test7Cards.push_back(Card('s',3));      // Random
    test7Cards.push_back(Card('d',3));
    test7Cards.push_back(Card('h',3));
    test7Cards.push_back(Card('c',8));
    test7Cards.push_back(Card('d',6));
    test7Cards.push_back(Card('h',6));      // Random
    test7Cards.push_back(Card('s',6));      // Random
    
    
    decider = Decider(test7Cards);
    cout << "Is this Combination a Full House: ";
    decider.isFullHouse() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;
    
    // Test_5.1 Flush
    test7Cards.clear();
    test7Cards.push_back(Card('s',1));
    test7Cards.push_back(Card('s',11));
    test7Cards.push_back(Card('s',13));
    test7Cards.push_back(Card('s',8));      // Random
    test7Cards.push_back(Card('c',6));      // Random
    test7Cards.push_back(Card('h',6));      // Random
    test7Cards.push_back(Card('s',6));
    
    decider = Decider(test7Cards);
    cout << "Is this Combination a Flush: ";
    decider.isFlush() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;

    cout << "DEBUG_END: testClass_Decider" << endl;
}

bool Debugger::getStatus(){
    return isOn;
}
void Debugger::setStatus(bool status){
    this->isOn = status;
    isDebuggerOn = status;
}
