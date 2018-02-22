//
//  User.hpp
//  PokerGame
//
//  Created by Tunc Alpman on 05/12/2017.
//  Copyright © 2017 Tunc Alpman. All rights reserved.
//

#ifndef User_hpp
#define User_hpp

#include <stdio.h>
#include "Card.hpp"
#include "Round.hpp"
#include "Chips.hpp"
#include <string>

using namespace std;

class User{
public:
    // Variables
    bool folded;
    int amoundPutOnCurrentRound;

    
    //Function
    User();
    void setName(string);
    string getName();
    void getPlayerInfo();
    bool isFolded();
    void setFold(bool);
    void setRandomCards(Round&);
    void setBlind(bool,bool);
    void setId(unsigned int);
    Card* getCards();
    Chips& getChips();
    unsigned int getId();
    void addCurrentRoundMoney(int);
    void setDecision(string);
    string getDecision();
    void initDecisions();
    void initCurrentRoundMoney();
    int getRank();
    void addRank(int);
    
private:
    // Variable
    unsigned int id;
    bool smallBlind;
    bool bigBlind;
    string name;
    Card cards[2];
    Chips chips;
    string decision;
    int rank;
    //Function
};




#endif /* User_hpp */
