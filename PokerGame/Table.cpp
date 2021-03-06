//
//  Table.cpp
//  PokerGame
//
//  Created by Tunc Alpman on 05/12/2017.
//  Copyright © 2017 Tunc Alpman. All rights reserved.
//

#include "Table.hpp"
#include "User.hpp"
#include "Round.hpp"
#include "Decider.hpp"
#include "Globals.hpp"
#include <iostream>
#include <map>
#include <unistd.h>

using namespace std;

Round currentRound;
int smallBlindId;
int bigBlindId;
vector<Card> cardsOnTheTable;
int whoseTurn;
int toEven;

int getConsecutiveHighCard(Card, Card);

void Table::createTable(){
    cout << selectNumberOfPlayer() << " number of Player selected!" << endl;
    createPlayers();
    smallBlindId = 1;                   // Init
    bigBlindId = smallBlindId + 1;      // Init
    moneyOnTable = Chips(0,0,0,0,0,0);
}

int Table::selectNumberOfPlayer(){
    int numberOfPlayer = 0;
    int counter = 0;
    
    cout << "Please select the number of Player!" << endl;
    
    while(!cin.good() || numberOfPlayer <= 1 || numberOfPlayer > 6){
        
        if(counter >= 1){
            cout << "Please select number of Player between 2-6 " << endl;
        }
        counter ++;
        cin >> numberOfPlayer;
        cin.clear();                // Check if entered Value is OK
        cin.ignore(INT_MAX,'\n');
    }
    
    totalNumberofPlayer = numberOfPlayer;
    return numberOfPlayer;
}

void Table::createPlayers(){
    for(int i = 0; i<totalNumberofPlayer; i++){
        User newUsr;
        newUsr.setId(i+1);
        enterNames(newUsr,i);
        allUsers.push_back(newUsr);
    }
}

void Table::enterNames(User &usr, int numberOfPlayer){
    cout << "Enter Name of "<< numberOfPlayer + 1 << ". player" << endl;
    string nameOfPlayer = "";
    cin >> nameOfPlayer;
    usr.setName(nameOfPlayer);
}

void Table::startRound(){
    
    //New Round Starts
    currentRound.startRound(); // Deck initialized
    setBlinds();
    
    for(User &usr : allUsers){
        usr.setRandomCards(currentRound); // If not playing anymore, because no money (permanant fold), not include these steps
        usr.initCurrentRoundMoney();
        usr.initRankings();
        usr.initDecisions();
        usr.setFold(false);
        usr.getPlayerInfo();
    }
    
    putBlindsMoney();
    putCardsOnTheTable();
    whoseTurn = roundTurn(bigBlindId + 1);
    
    bool roundDone = false;
    toEven = BIG_BLIND;
    int turn = 0;
    
    // First Round Starts
    while(!roundDone){
        
        for(User usr : allUsers){
            if(usr.getId() == whoseTurn && !usr.isFolded()){
                cout << "- Player " << usr.getName() << "'s turn..." << endl;
                break;
            }
        }
        if(whoseTurn == smallBlindId && allUsers[whoseTurn-1].getDecision()=="i" && !allUsers[whoseTurn-1].isFolded()){
            makeMove(allUsers[whoseTurn-1]); // TODO Is return String necessary?
        }else if(whoseTurn == bigBlindId && allUsers[whoseTurn-1].getDecision()=="i" && !allUsers[whoseTurn-1].isFolded()){
            makeMove(allUsers[whoseTurn-1]);
        }else if(!allUsers[whoseTurn-1].isFolded()){
            makeMove(allUsers[whoseTurn-1]);
        }else{
            whoseTurn = roundTurn(whoseTurn + 1);// FOLDED USER
        }
        
        int idOfremainder = allFoldedButOne(); // if everyone folded but one ? id : -1;
        
        
        if(!isThereInitDecision() && idOfremainder == -1){
            turn++;
            cout << "INFO: A New Turn Starts..." <<endl;
            initAllUserDecisions(); // Folded Users decisions are also initializes however they stay as "folded" until next hand
            
            if(turn == 1){
                for(int i = 0;i<3;i++){
                    cardsOnTheTable[i].getCardInfo();
                }
            }else if(turn == 2){
                cardsOnTheTable[3].getCardInfo();
            }else if(turn == 3){
                cardsOnTheTable[4].getCardInfo();
            }
            else{ // Round Finishes Here
                roundFinishedConditions(roundDone,-1);
            }
        }else if(idOfremainder != -1){
            roundFinishedConditions(roundDone, idOfremainder);
        }
    }
}

void Table::roundFinishedConditions(bool &roundDone, int oneRemainderId){
    smallBlindId = roundTurn(smallBlindId + 1); // increment SmallBlindId prepare for new Round
    bigBlindId  = roundTurn(bigBlindId + 1);    // increment BigBlindId prepare for new Round
    payTheWinner(oneRemainderId); // TODO Exclude Folded Players from payTheWinner
    sleep(SLEEP_TIME);
    cardsOnTheTable.clear();
    roundDone = true;
}


bool Table::isThereInitDecision(){
    for(User usr : allUsers){
        if(usr.getDecision() == "i" && !usr.isFolded()){
            return true;
            break;
        }
    }
    return false;
}

int Table::allFoldedButOne(){
    
    uint8_t counter = 0;
    uint8_t numberOfPlayerOnTheTable = allUsers.size();
    int usedIdOfNonfolder = -1;
    
    for(User usr : allUsers){
        if(usr.isFolded()){
            counter++;
        }else{
            usedIdOfNonfolder = usr.getId();
        }
    }
    
    if(counter == numberOfPlayerOnTheTable-1){
        return usedIdOfNonfolder;
    }
    
    return -1;
}

void Table::setBlinds(){
    for(User &usr : allUsers){
        if(usr.getId() == smallBlindId){
            usr.setBlind(true,false);
        }else if(usr.getId() == bigBlindId){
            usr.setBlind(false,true);
        }else{
            usr.setBlind(false,false);
        }
    }
}


void Table::putBlindsMoney(){
    
    moneyOnTable.addChips(Converter::amountToChipConverter(SMALL_BLIND + BIG_BLIND, Chips(0,0,0,0,0,0))); // TODO If remove from user is Successfull then add chips otherwise infinite Money
    for(User usr : allUsers){
        if(usr.getId()==smallBlindId){
            Converter::removeAmountAsChips(SMALL_BLIND, usr.getChips(), Chips(0,0,0,0,0,0)); // TODO Check if Remove Succesfull
            usr.addCurrentRoundMoney(SMALL_BLIND);
            allUsers[smallBlindId-1] = usr;
        }else if(usr.getId()== bigBlindId){
            Converter::removeAmountAsChips(BIG_BLIND, usr.getChips(), Chips(0,0,0,0,0,0)); // TODO Check if Remove Succesfull
            usr.addCurrentRoundMoney(BIG_BLIND);
            allUsers[bigBlindId-1] = usr;
        }
    }
}

void Table::putCardsOnTheTable(){
    int seed = static_cast<int>(time(0)); // Seed for Random Number Generator
    srand(seed);
    
    for(int i = 0;i<5;i++){ // TODO Something Wrong
        int randNum = (rand() % (currentRound.deck.size())); // 0 - 51, 50, 49, 48, 47
        cardsOnTheTable.push_back(currentRound.deck[randNum]);
        currentRound.deck.erase(currentRound.deck.begin() + randNum);
    }
}

int Table::roundTurn(int turn){
    if(turn > allUsers.size()){
        return 1;
    }else{
        return turn;
    }
}

string Table::makeMove(User &userToMakeMove){
    
    bool flag = true;
    string decision = "";
    
    while(flag){
        
        cout << "Do you want to even/check(e) raise(r<ChipCode><Amount>), or fold(f)? " << endl;
        cin >> decision;
        //decision = "e";
        
        if(decision == "e"){
            cout << "Selection Even/Check" << endl;
            userToMakeMove.setDecision(decision);
            if(toEven > userToMakeMove.amoundPutOnCurrentRound){
                int rest = toEven - userToMakeMove.amoundPutOnCurrentRound;
                moneyOnTable.addChips(Converter::amountToChipConverter(rest, Chips(0,0,0,0,0,0)));      // 1
                Converter::removeAmountAsChips(rest, userToMakeMove.getChips(), Chips(0,0,0,0,0,0));    // 2
                userToMakeMove.addCurrentRoundMoney(rest);                                   // 3 TODO All in One
            }
            whoseTurn = roundTurn(userToMakeMove.getId() + 1);
            flag = false;
        }
        else if(decision == "f"){
            cout << "Selection Fold" << endl;
            userToMakeMove.setDecision(decision);
            userToMakeMove.setFold(true);
            whoseTurn = roundTurn(userToMakeMove.getId() + 1);
            flag = false;
        }else if(decision == "r"){ // TODO Regex & getLine func
            // TODO all but this user decision should go to init -> i
            cout << "Selection raise" << endl;
            flag = false;
        }else{ // TODO All IN
            cout << "Selection not available select again." << endl;
        }
    }
    return decision;
}

void Table::initAllUserDecisions(){
    for(User &eachUser : allUsers){
        eachUser.initDecisions();
    }
}

void Table::payTheWinner(int oneRemainderId){
    
    map<int,vector<Card>> combined7Cards;
    int highestRank = 0;
    int8_t numberOfWinners = 0;
    map<int,vector<Card>>::iterator it;
    
    if(oneRemainderId == -1){
    
        for(User usr : allUsers){ // TODO More Efficient maybe?
            vector<Card> cardArray;
            for(int i = 0; i< 2;i++){
                cardArray.push_back(usr.getCards()[i]);
            }
            for(Card card : cardsOnTheTable){
                cardArray.push_back(card);
            }
            combined7Cards.insert(pair<int,vector<Card>>(usr.getId(),cardArray)); // map = (UserID & Users_Combined_7_Card)
        }
        
        for(it = combined7Cards.begin(); it != combined7Cards.end(); it++){ // iterate through all users
            
            Decider decider(it->second); // Sets the ranks of the user from Current Round
            decider.setRankFor(allUsers[it->first-1]);
            
            if(allUsers[(it->first)-1].getRank() > highestRank){
                highestRank = allUsers[(it->first)-1].getRank();
            }
        }
        
        for(it = combined7Cards.begin(); it != combined7Cards.end(); it++){
            if(allUsers[(it->first)-1].getRank() == highestRank){
                numberOfWinners++;
            }
        }
    
        // TODO Turn into Function
        int totalAmount = moneyOnTable.sumOfChips();
        int toShare = 0;
        if(totalAmount % numberOfWinners != 0){
            toShare = (int) (totalAmount / numberOfWinners);
            moneyOnTable.resetChips();
            moneyOnTable.addChips(Converter::amountToChipConverter(totalAmount % numberOfWinners, Chips())); // Remainders leave it on the Table for next Round
        }else{
            toShare = totalAmount / numberOfWinners;
            moneyOnTable.resetChips();
        }
        
        for(it = combined7Cards.begin(); it != combined7Cards.end(); it++){
            if(allUsers[(it->first)-1].getRank() == highestRank){
                User *winner = &allUsers[(it->first)-1];
                winner->getChips().addChips(Converter::amountToChipConverter(toShare,Chips()));
                cout << "Winner(s): " << winner->getName() << " with Rank: " << winner->getRank() << endl;
            }
            if(isDebuggerOn) allUsers[(it->first)-1].getChips().getChipInfo();
        }
    
    }else{
        User *winner = &allUsers[oneRemainderId-1];
        winner->getChips().addChips(moneyOnTable);
        cout << "Everyone folded but " << winner->getName() << ". Therefore is the only Winner!" << endl;;
        moneyOnTable.resetChips();
    }
}

