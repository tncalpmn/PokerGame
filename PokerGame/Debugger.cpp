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
    //testClass_Decider();                    // TEST 3
    testFunction_payTheWinner();              // TEST 4
    
}

void Debugger::testFunction_payTheWinner(){

    // Manuel Fill of Cards on the Table and User Cards
    testTable.cardsOnTheTable.push_back(Card('c',13));
    testTable.cardsOnTheTable.push_back(Card('c',12));
    testTable.cardsOnTheTable.push_back(Card('c',11));
    testTable.cardsOnTheTable.push_back(Card('c',10));
    testTable.cardsOnTheTable.push_back(Card('c',6));
    
    User testUser1;
    testUser1.setId(1);
    testUser1.setName("Test User 1");
    testUser1.setCards(Card('c',1), Card('s',7));
    User testUser2;
    testUser2.setId(2);
    testUser2.setName("Test User 2");
    testUser2.setCards(Card('c',9), Card('s',1));
    
    testTable.allUsers.push_back(testUser1);
    testTable.allUsers.push_back(testUser2);
    
    testTable.payTheWinner();

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
    
    // Test_1.1 RoyalFlush Ex: (S_10, S_11, S_12, S_13, S_1, C_1, C_11)                   -> PASSED
    clearAndfillVectorWith7Cards(
                                 test7Cards,
                                 Card('c',12),
                                 Card('c',13),
                                 Card('c',1),
                                 Card('c',10),
                                 Card('d',4),   // Random
                                 Card('c',11),
                                 Card('c',9)    // Random
                                 );
    
    Decider decider(test7Cards);
    cout << "Test_1.1: Is this Combination a Royal Flush: ";
    decider.isRoyalFlush() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;
    
    // Test_2.1 Straight Flush                                                          -> PROGRESS
    clearAndfillVectorWith7Cards(
                                 test7Cards,
                                 Card('c',3),
                                 Card('c',4),
                                 Card('c',5),
                                 Card('c',6),
                                 Card('d',4),   // Random
                                 Card('s',11),  // Random
                                 Card('c',2)
                                 );
    
    decider = Decider(test7Cards);
    cout << "Test_2.1: Is this Combination a Straigt Flush: ";
    decider.isStraightFlush() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;
    
    // Test_2.2 Straight Flush
    clearAndfillVectorWith7Cards(
                                 test7Cards,
                                 Card('c',13),
                                 Card('s',12),
                                 Card('d',1),
                                 Card('s',10),
                                 Card('s',11),
                                 Card('c',1),  // Random
                                 Card('s',2)   // Random
                                 );

    
    decider = Decider(test7Cards);
    cout << "Test_2.2: Is this Combination a Straigt Flush: ";
    decider.isStraightFlush() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;
    
    // Test_2.3 Straight Flush
    clearAndfillVectorWith7Cards(
                                 test7Cards,
                                 Card('h',3),
                                 Card('h',2),
                                 Card('h',1),
                                 Card('s',1), // Random
                                 Card('c',1), // Random
                                 Card('h',4),
                                 Card('h',5)
                                 );
  
    // TODO 1) 10 11 12 13 A    2) 2,3,4,5,6 & 3,4,5,6,7 (HighCard)
    
    decider = Decider(test7Cards);
    cout << "Test_2.3: Is this Combination a Straigt Flush: ";
    decider.isStraightFlush() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;
    
    // Test_3.1 4 of a Kind
    clearAndfillVectorWith7Cards(
                                 test7Cards,
                                 Card('s',3), // Random
                                 Card('d',1),
                                 Card('h',1),
                                 Card('s',1),
                                 Card('c',1),
                                 Card('h',3), // Random
                                 Card('h',5)  // Random
                                 );
    

    decider = Decider(test7Cards);
    cout << "Test_3.1: Is this Combination a Four of a Kind: ";
    decider.is4ofaKind() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;
    
    // Test_4.1 Full House
    clearAndfillVectorWith7Cards(
                                 test7Cards,
                                 Card('s',3), // Random
                                 Card('d',3),
                                 Card('h',3),
                                 Card('c',8),
                                 Card('d',6),
                                 Card('h',6), // Random
                                 Card('s',6)  // Random
                                 );
    
    decider = Decider(test7Cards);
    cout << "Test_4.1: Is this Combination a Full House: ";
    decider.isFullHouse() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;
    
    // Test_5.1 Flush
    clearAndfillVectorWith7Cards(
                                 test7Cards,
                                 Card('s',1),
                                 Card('s',11),
                                 Card('s',13),
                                 Card('s',8), // Random
                                 Card('c',6), // Random
                                 Card('h',6), // Random
                                 Card('s',6)
                                 );
    
    decider = Decider(test7Cards);
    cout << "Test_5.1: Is this Combination a Flush: ";
    decider.isFlush() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;
    
    // Test_6.1 Straigt
    clearAndfillVectorWith7Cards(
                                 test7Cards,
                                 Card('s',1), // Random
                                 Card('c',1), // Random
                                 Card('h',1), // Random
                                 Card('s',2),
                                 Card('c',3),
                                 Card('h',4),
                                 Card('s',5)
                                 );
    
    decider = Decider(test7Cards);
    cout << "Test_6.1: Is this Combination a Straight: ";
    decider.isStraight() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;
    
    // Test_7.1 3 of a Kind
    clearAndfillVectorWith7Cards(
                                 test7Cards,
                                 Card('s',1),
                                 Card('c',2),
                                 Card('h',1),
                                 Card('s',2),
                                 Card('c',3),
                                 Card('h',2),
                                 Card('c',1)
                                 );
    
    decider = Decider(test7Cards);
    cout << "Test_7.1: Is this Combination a 3 of a Kind: ";
     decider.is3ofaKind() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;
    
    // Test_8.1 2 Pair
    clearAndfillVectorWith7Cards(
                                 test7Cards,
                                 Card('s',1),
                                 Card('c',1),
                                 Card('h',2),
                                 Card('s',2),
                                 Card('c',3),
                                 Card('h',3),
                                 Card('s',3)
                                 );
    
    decider = Decider(test7Cards);
    cout << "Test_8.1: Is this Combination a 2 Pair ";
    decider.is2Pair() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;

    // Test_9.1 1 Pair
    clearAndfillVectorWith7Cards(
                                 test7Cards,
                                 Card('s',1),
                                 Card('c',1),
                                 Card('h',4),
                                 Card('s',9),
                                 Card('c',13),
                                 Card('h',8),
                                 Card('s',5)
                                 );
    
    decider = Decider(test7Cards);
    cout << "Test_9.1: Is this Combination a 1 Pair ";
    decider.is1Pair() ? cout << "TRUE" << endl: cout << "FALSE" <<endl;
    
    cout << "DEBUG_END: testClass_Decider" << endl;
}
void Debugger::clearAndfillVectorWith7Cards(vector<Card>& test7Cards, Card card1, Card card2, Card card3, Card card4, Card card5, Card card6, Card card7){

    test7Cards.clear();
    test7Cards.push_back(card1);
    test7Cards.push_back(card2);
    test7Cards.push_back(card3);
    test7Cards.push_back(card4);
    test7Cards.push_back(card5);
    test7Cards.push_back(card6);
    test7Cards.push_back(card7);
    
}


bool Debugger::getStatus(){
    return isOn;
}
void Debugger::setStatus(bool status){
    this->isOn = status;
    isDebuggerOn = status;
}
