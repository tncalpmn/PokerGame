//
//  Table.hpp
//  PokerGame
//
//  Created by Tunc Alpman on 05/12/2017.
//  Copyright © 2017 Tunc Alpman. All rights reserved.
//

#ifndef Table_hpp
#define Table_hpp

#include <stdio.h>
#include "User.hpp"
#include "Round.hpp"
#include <vector>


class Table {
    
private:
    //Variables
    int selectNumberOfPlayer();
    //Functions
    void createPlayers();
    void enterNames(User&,int);
    string makeMove(User&);
    void setBlinds();
    int roundTurn(int);
    void initAllUserDecisions();
    void payTheWinner();
public:
    //Variables
    Round currentRound;
    Chips moneyOnTable;
    void startRound();
    int totalNumberofPlayer;
    std::vector<User> allUsers;
    void putBlindsMoney();
    void putCardsOnTheTable();
    //Functions
    void createTable();
    void createRound();
    bool removeAmountAsChips(int,Chips&,Chips);
    Chips& changeNextAvailableCoinsToOnes(Chips&);
    Chips amountToChipConverter(int, Chips);
};


#endif /* Table_hpp */
