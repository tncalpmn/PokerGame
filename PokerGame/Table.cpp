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

using namespace std;

Round currentRound;
int smallBlindId;
int bigBlindId;
vector<Card> cardsOnTheTable;
int whoseTurn;
int toEven;

int getConsecutiveHighCard(Card, Card);
int sumHighComb(vector<Card>);


void Table::createTable(){
    cout << "- Table is being created..." << endl;
    createRound();
    cout << selectNumberOfPlayer() << " number of Player selected!" << endl;
    createPlayers();
    smallBlindId = 1;                   // Init
    bigBlindId = smallBlindId + 1;      // Init
    moneyOnTable = Chips(0,0,0,0,0,0);
    cout << "- Table is created!" << endl;
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

void Table::createRound(){
    Round newRound;
    currentRound = newRound;
}

void Table::createPlayers(){
    cout << "- Players are being created..." << endl;
    
    for(int i = 0; i<totalNumberofPlayer; i++){
        User newUsr;
        newUsr.setId(i+1);
        enterNames(newUsr,i);
        allUsers.push_back(newUsr);
    }
    
    cout << "- Players are created!" << endl;
}

void Table::enterNames(User &usr, int numberOfPlayer){
    cout << "Enter Name of "<< numberOfPlayer + 1 << ". player" << endl;
    string nameOfPlayer = "";
    cin >> nameOfPlayer;
    usr.setName(nameOfPlayer);
}

int Table::roundTurn(int turn){
    if(turn > allUsers.size()){
        return 1;
    }else{
        return turn;
    }
}

bool Table::removeAmountAsChips(int amount, Chips &availableAmount, Chips init){ // TODO Converter Class
  
    bool wasRemoveSuccesful = true;
    
    if(amount == 0){
        isDebuggerOn ? cout << "Reduction Successful!" << endl: cout << "";
    }else if(1 <= amount && amount <= availableAmount.getOnes() * 1){
        init.addChips(Chips(amount / 1,0,0,0,0,0));
        availableAmount.removeChips(Chips(amount / 1,0,0,0,0,0));
        amount = amount % 1;
        removeAmountAsChips(amount, availableAmount, init);
    }else if(5 <= amount && amount <= availableAmount.getFives() * 5){
        init.addChips(Chips(0,amount / 5,0,0,0,0));
        availableAmount.removeChips(Chips(0,amount / 5,0,0,0,0));
        amount = amount % 5;
        removeAmountAsChips(amount, availableAmount, init);
    }else if(10 <= amount && amount <= availableAmount.getTens() * 10){
        init.addChips(Chips(0,0,amount / 10,0,0,0));
        availableAmount.removeChips(Chips(0,0,amount / 10,0,0,0));
        amount = amount % 10;
        removeAmountAsChips(amount, availableAmount, init);
    }else if(20 <= amount && amount <= availableAmount.getTwentys() * 20){
        init.addChips(Chips(0,0,0,amount / 20,0,0));
        availableAmount.removeChips(Chips(0,0,0,amount / 20,0,0));
        amount = amount % 20;
        removeAmountAsChips(amount, availableAmount, init);
    }else if(50 <= amount && amount <= availableAmount.getFiftys() * 50){
        init.addChips(Chips(0,0,0,0,amount / 50,0));
        availableAmount.removeChips(Chips(0,0,0,0,amount / 50,0));
        amount = amount % 50;
        removeAmountAsChips(amount, availableAmount, init);
    }else if(100 <= amount && amount <= availableAmount.getHunderts() * 100) {
        init.addChips(Chips(0,0,0,0,0,amount / 100));
        availableAmount.removeChips(Chips(0,0,0,0,0,amount / 100));
        amount = amount % 100;
        removeAmountAsChips(amount, availableAmount, init);
    }else if(amount <= availableAmount.sumOfChips()){
        int div = 0;
        if(amount % 100 == 0 && availableAmount.getHunderts() != 0){
            div = amount / 100;
            init.addChips(Chips(0,0,0,0,0,1));
            amount = (div - 1) * 100;
            availableAmount.removeChips(Chips(0,0,0,0,0,1));
            removeAmountAsChips(amount, availableAmount, init);
        }else if(amount % 50 == 0 && availableAmount.getFiftys() != 0){
            div = amount / 50;
            init.addChips(Chips(0,0,0,0,1,0));
            amount = (div - 1) * 50;
            availableAmount.removeChips(Chips(0,0,0,0,1,0));
            removeAmountAsChips(amount, availableAmount, init);
        }else if(amount % 20 == 0 && availableAmount.getTwentys() != 0){
            div = amount / 20;
            init.addChips(Chips(0,0,0,1,0,0));
            amount = (div - 1) * 20;
            availableAmount.removeChips(Chips(0,0,0,1,0,0));
            removeAmountAsChips(amount, availableAmount, init);
        }else if(amount % 10 == 0 && availableAmount.getTens() != 0){
            div = amount / 10;
            init.addChips(Chips(0,0,1,0,0,0));
            amount = (div - 1) * 10;
            availableAmount.removeChips(Chips(0,0,1,0,0,0));
            removeAmountAsChips(amount, availableAmount, init);
        }else if(amount % 5 == 0 && availableAmount.getFives() != 0){
            div = amount / 5;
            init.addChips(Chips(0,1,0,0,0,0));
            amount = (div - 1) * 5;
            availableAmount.removeChips(Chips(0,1,0,0,0,0));
            removeAmountAsChips(amount, availableAmount, init);
        }else if(amount % 1 == 0 && availableAmount.getOnes() != 0){
            div = amount / 1;
            init.addChips(Chips(1,0,0,0,0,0));
            amount = (div - 1) * 1;
            availableAmount.removeChips(Chips(1,0,0,0,0,0));
            removeAmountAsChips(amount, availableAmount, init);
        }else{
            removeAmountAsChips(amount, changeNextAvailableCoinsToOnes(availableAmount), init);
        }
    }else{
        cout << "ERROR User Has Not enought money - TODO" << endl; // TODO
        wasRemoveSuccesful = false;
    }
    return wasRemoveSuccesful;
}

Chips& Table::changeNextAvailableCoinsToOnes(Chips &availableAmount){
    if(availableAmount.getFives() > 0){
        availableAmount.addChips(Chips(availableAmount.getFives()*5,0,0,0,0,0));
        availableAmount.removeChips(Chips(0,availableAmount.getFives(),0,0,0,0));
        return availableAmount;
    }else if(availableAmount.getTens() > 0){
        availableAmount.addChips(Chips(availableAmount.getTens()*10,0,0,0,0,0));
        availableAmount.removeChips(Chips(0,0,availableAmount.getTens(),0,0,0));
        return availableAmount;
    }else if(availableAmount.getTwentys() > 0){
        availableAmount.addChips(Chips(availableAmount.getTwentys()*20,0,0,0,0,0));
        availableAmount.removeChips(Chips(0,0,0,availableAmount.getTwentys(),0,0));
        return availableAmount;
    }else if(availableAmount.getFiftys() > 0){
        availableAmount.addChips(Chips(availableAmount.getFiftys()*50,0,0,0,0,0));
        availableAmount.removeChips(Chips(0,0,0,0,availableAmount.getFiftys(),0));
        return availableAmount;
    }else{
        availableAmount.addChips(Chips(availableAmount.getHunderts()*100,0,0,0,0,0));
        availableAmount.removeChips(Chips(0,0,0,0,0,availableAmount.getHunderts()));
        return availableAmount;
    }
}

Chips Table::amountToChipConverter(int amount, Chips init){
    
    if(amount >= 100){
        init.addChips(Chips(0,0,0,0,0, amount / 100));
        amount = amount % 100;
        return amountToChipConverter(amount, init);
    }else if(amount >= 50){
        init.addChips(Chips(0,0,0,0,amount / 50,0));
        amount = amount % 50;
        return amountToChipConverter(amount, init);
    }else if(amount >= 20){
        init.addChips(Chips(0,0,0,amount / 20,0,0));
        amount = amount % 20;
        return amountToChipConverter(amount, init);
    }else if(amount >= 10){
        init.addChips(Chips(0,0,amount / 10,0,0,0));
        amount = amount % 10;
        return amountToChipConverter(amount, init);
    }else if(amount >= 5){
        init.addChips(Chips(0,amount/5,0,0,0,0));
        amount = amount % 5;
        return amountToChipConverter(amount, init);
    }else if(amount >= 1){
        init.addChips(Chips(amount/1,0,0,0,0,0));
        amount = amount % 1;
        return amountToChipConverter(amount, init);
    }else{
        return init;
    }
}

void Table::startRound(){
    
    
    cout << "---------------- New Round Starts ----------------" <<endl;
    
    currentRound.startRound(moneyOnTable); // Money on the Table cleared & Deck initialized
    setBlinds();
    
    for(User &usr : allUsers){
        usr.setRandomCards(currentRound);
        usr.initCurrentRoundMoney();
        usr.getPlayerInfo();
    }
    
    putBlindsMoney();
    putCardsOnTheTable();
    whoseTurn = roundTurn(bigBlindId + 1);
    
    bool roundDone = false;
    toEven = BIG_BLIND;
    int turn = 0;
    
    cout << "---------------- First Turn of the Round Starts ---------------- " <<endl;
    
    while(!roundDone){
        
        for(User usr : allUsers){
            if(usr.getId() == whoseTurn){
                cout << "- Player " << usr.getName() << "'s turn..." << endl;
            }
        }
        if(whoseTurn == smallBlindId && allUsers[whoseTurn-1].getDecision()=="i"){
            makeMove(allUsers[whoseTurn-1]); // TODO Is return String necessary?
        }else if(whoseTurn == bigBlindId && allUsers[whoseTurn-1].getDecision()=="i"){
            makeMove(allUsers[whoseTurn-1]);
        }else{
            makeMove(allUsers[whoseTurn-1]);
        }
        
        if(allUsers[whoseTurn-1].getDecision() != "i"){
            turn++;
            cout << "INFO: A New Turn Starts..." <<endl;
            initAllUserDecisions();
            
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
                smallBlindId = roundTurn(smallBlindId + 1); // increment SmallBlindId prepare for new Round
                bigBlindId  = roundTurn(bigBlindId + 1);    // increment BigBlindId prepare for new Round
                // TODO Decide who won and give money
                payTheWinner();
                cardsOnTheTable.clear();
                roundDone = true;
                cout << "---------------- A Round Finished ---------------- "<<endl;
            }
        }
    }
}

void Table::payTheWinner(){ // TODO Pay the money who is on the Game on the Current Round
    
    map<int,vector<Card>> combined7Cards;
    
    for(User usr : allUsers){
        vector<Card> cardArray;
        for(int i = 0; i< 2;i++){
            cardArray.push_back(usr.getCards()[i]);
        }
        for(Card card : cardsOnTheTable){
            cardArray.push_back(card);
        }
        combined7Cards.insert(pair<int,vector<Card>>(usr.getId(),cardArray)); // map = (UserID & Users_Combined_7_Card)
    }
    
    map<int,vector<Card>>::iterator it;
    
    for(it = combined7Cards.begin(); it != combined7Cards.end(); it++){ // iterate through all users
    
        Decider decisionMaker(it->second); // All this function can go into Decider give User&
        
        if(decisionMaker.isRoyalFlush()){           // Royal Flush (DONE)
            allUsers[(it->first)-1].addRank(9000);
        }
        else if(decisionMaker.isStraightFlush()){   // Straight Flush (DONE)
            allUsers[(it->first)-1].addRank(8000);
            //sort(decisionMaker.highestCombination.begin(), decisionMaker.highestCombination.end(), Decider::sortNumbers); Not Necessary
            allUsers[(it->first)-1].addRank(getConsecutiveHighCard(decisionMaker.highestCombination.front(),
                                                                   decisionMaker.highestCombination.back())); // Extra Ranking for HighCard
        }
        else if(decisionMaker.is4ofaKind()){        // 4 of a Kind (DONE)
            allUsers[(it->first)-1].addRank(7000);
            allUsers[(it->first)-1].addRank(sumHighComb(decisionMaker.highestCombination));
        }
        else if(decisionMaker.isFullHouse()){       // Full House (DONE)
            allUsers[(it->first)-1].addRank(6000);
            map<Card, int> twosAndThrees = decisionMaker.groupCardsWithNums(decisionMaker.highestCombination);
            for(pair<Card,int> each : twosAndThrees){
                allUsers[(it->first)-1].addRank(each.second == 3 ? 15 * each.first.getValue() : each.first.getValue() ); // 15 is here weight given for threes
            }
        }
        else if(decisionMaker.isFlush()){           // Flush (DONE)
            allUsers[(it->first)-1].addRank(5000);
            allUsers[(it->first)-1].addRank(decisionMaker.highestCombination.front().getValue());
        }
        else if(decisionMaker.isStraight()){        // Straight (DONE)
            allUsers[(it->first)-1].addRank(4000);
            sort(decisionMaker.highestCombination.begin(), decisionMaker.highestCombination.end(), Decider::sortNumbers);
            allUsers[(it->first)-1].addRank(getConsecutiveHighCard(decisionMaker.highestCombination.front(),
                                                                   decisionMaker.highestCombination.back())); // Extra Ranking for HighCard
        }
        else if(decisionMaker.is3ofaKind()){        // 3 Of a Kind (DONE)
            allUsers[(it->first)-1].addRank(3000);
            map<Card, int> threesAnd2Highs = decisionMaker.groupCardsWithNums(decisionMaker.highestCombination);
            for(pair<Card,int> each : threesAnd2Highs){
                allUsers[(it->first)-1].addRank(each.second == 3 ? 15 * each.first.getValue() : each.first.getValue() ); // 15 is here weight given for threes
            }
        }
        else if(decisionMaker.is2Pair()){           // Two Pair
            allUsers[(it->first)-1].addRank(2000);
        }
        else if(decisionMaker.is1Pair()){           // One Pair
            allUsers[(it->first)-1].addRank(1000);
        }
        else{                           // High Card
            allUsers[(it->first)-1].addRank(max(allUsers[(it->first)-1].getCards()[0].getNumber(), allUsers[(it->first)-1].getCards()[1].getNumber()));
            // TODO if high card in deck is bigger than tie
        }                               //if(usr.getCards()[0 or 1]== 1 (A) then) rank += 14
    
        cout << "User ID: "<< allUsers[(it->first)-1].getId() << " User Rank: "<<allUsers[(it->first)-1].getRank() << " Highest Combination: " << endl;
        for(Card crd : decisionMaker.highestCombination){
            
            crd.getCardInfo();
            
        }
    }
    
    // TODO if two user have same rank check hands higest card it belongs to USer then rank++ otherwise tie
    
}

int getConsecutiveHighCard(Card front, Card back){
    if(front.getNumber() == 1 && back.getNumber() == 13){
        return front.getValue();
    }else{
        return back.getValue();
    }
}

int sumHighComb(vector<Card> higCom){
   
    int sum = 0;
    int8_t counter = 0; // TODO Change All int counters to int8 if possible
    for(Card crd : higCom){
        
        if(counter < 4)
            sum = sum + (crd.getValue() * 15); // 15 is here weight, to give more value to 4 of a kind Cards
        else
            sum = sum + crd.getValue();
        counter++;
    }
    
    return sum;
}


void Table::initAllUserDecisions(){

    for(User &eachUser : allUsers){
        eachUser.initDecisions();
    }
    
}

string Table::makeMove(User &userToMakeMove){
    
    bool flag = true;
    string decision = "";
    
    while(flag){
        
        cout << "Do you want to even/check(e) raise(r<ChipCode><Amount>), or fold(f)? " << endl;
        cin >> decision;
    
        if(decision == "e"){
            cout << "Selection Even/Check" << endl;
            userToMakeMove.setDecision(decision);
            if(toEven > userToMakeMove.amoundPutOnCurrentRound){
                int rest = toEven - userToMakeMove.amoundPutOnCurrentRound;
                moneyOnTable.addChips(amountToChipConverter(rest, Chips(0,0,0,0,0,0)));      // 1
                removeAmountAsChips(rest, userToMakeMove.getChips(), Chips(0,0,0,0,0,0));    // 2
                userToMakeMove.addCurrentRoundMoney(rest);                                   // 3 TODO All in One
            }
            whoseTurn = roundTurn(userToMakeMove.getId() + 1);
            flag = false;
        }
        else if(decision == "f"){
            cout << "Selection Fold" << endl;
            flag = false;
        }else if(decision == "r"){ // TODO Regex
            // TODO all but this user decision should go to init -> i
            cout << "Selection raise" << endl;
            flag = false;
        }else{ // TODO All IN
            cout << "Selection not available select again." << endl;
        }
    }
    return decision;
}

void Table::putCardsOnTheTable(){
    int seed = static_cast<int>(time(0)); // Seed for Random Number Generator
    srand(seed);
    
    for(int i = 0;i<5;i++){
        int randNum = (rand() % (currentRound.deck.size()));
        cardsOnTheTable.push_back(currentRound.deck[randNum]);
        currentRound.deck.erase(currentRound.deck.begin() + randNum);
    }
}

void Table::putBlindsMoney(){
    moneyOnTable.addChips(amountToChipConverter(SMALL_BLIND + BIG_BLIND, Chips(0,0,0,0,0,0))); // TODO If remove from user is Successfull then add chips
    for(User usr : allUsers){
        if(usr.getId()==smallBlindId){
            removeAmountAsChips(SMALL_BLIND, usr.getChips(), Chips(0,0,0,0,0,0)); // TODO Check if Remove Succesfull
            usr.addCurrentRoundMoney(SMALL_BLIND);
            allUsers[smallBlindId-1] = usr;
        }else if(usr.getId()== bigBlindId){
            removeAmountAsChips(BIG_BLIND, usr.getChips(), Chips(0,0,0,0,0,0)); // TODO Check if Remove Succesfull
            usr.addCurrentRoundMoney(BIG_BLIND);
            allUsers[bigBlindId-1] = usr;
        }
    }
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
