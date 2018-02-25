//
//  Decider.cpp
//  PokerGame
//
//  Created by Tunc Alpman on 28/12/2017.
//  Copyright © 2017 Tunc Alpman. All rights reserved.
//

#include "Decider.hpp"
#include <algorithm>


using namespace std;

Decider::Decider(vector<Card> all7Cards){
    this->all7Cards = all7Cards;
    numbOfSuits = countSuits();
    numbOfNumbers = countNumbers();
    atLeastFiveSuits = atLeastFiveSuit();
}

bool Decider::isRoyalFlush(){
    
    bool isRF = false;
    char atLFiveSuit = atLeastFiveSuit();
    
    if(atLFiveSuit != 'n'){
        
        int counter = 0;
        
        for(Card crd : all7Cards){
            if(crd.getNumber() == 1 && crd.getSuit() == atLFiveSuit){
                counter++;
            }else if(crd.getNumber() == 10 && crd.getSuit() == atLFiveSuit){
                counter++;
            }else if(crd.getNumber() == 11 && crd.getSuit() == atLFiveSuit){
                counter++;
            }else if(crd.getNumber() == 12 && crd.getSuit() == atLFiveSuit){
                counter++;
            }else if(crd.getNumber() == 13 && crd.getSuit() == atLFiveSuit){
                counter++;
            }
        }
        
        if(counter == 5){
            isRF = true;
        }
    }else{
        isRF = false;
    }
    return isRF;
}

map<char, int>  Decider::countSuits(){
    
     map<char, int> suitCounts;
     
     suitCounts.insert(pair<char,int>('s', 0));
     suitCounts.insert(pair<char,int>('c', 0));
     suitCounts.insert(pair<char,int>('d', 0));
     suitCounts.insert(pair<char,int>('h', 0));
     
     map<char, int>::iterator it;
     
     for(Card singCard : all7Cards){

         for(it = suitCounts.begin();it != suitCounts.end();it++){
             if(singCard.getSuit() == it->first){
                 it->second++;
                 break;
             }
         }
     }
    
    return suitCounts;
}

map<int, int> Decider::countNumbers(){
    
    map<int, int> numberCounts;
    
    for(Card crd : all7Cards){
    
        if(numberCounts.count(crd.getNumber())){
            numberCounts.insert(pair<int,int>(crd.getNumber(), numberCounts.find(crd.getNumber())->second++));
        }else {
            numberCounts.insert(pair<int,int>(crd.getNumber(), 1));
        }
    }
    
    return numberCounts;
}

char Decider::atLeastFiveSuit(){
    
    map<char, int>::iterator it;
    
    for(it = numbOfSuits.begin(); it != numbOfSuits.end(); it++){
        if(it->second >= 5){
            atLeastFiveSuits = it->first;
        }
    }
    return atLeastFiveSuits;
}

bool Decider::isConsecutive(vector<Card> listOfCards){
    
    bool isConsecutive = false;

    vector<Card> tableCards (listOfCards.size());
    auto it = copy_if(listOfCards.begin(), listOfCards.end(), tableCards.begin(), [](Card crd){return !(crd.isThisUsersCard());});
    
    tableCards.resize(distance(tableCards.begin(),it));
    
    sort(listOfCards.begin(), listOfCards.end(), sortNumbers);
    
    if(containsCard(listOfCards, Card('n',1), false)  && // n (Suits)  here is not important because function with false parameter compare only Numbers
       containsCard(listOfCards, Card('n',13), false) &&
       containsCard(listOfCards, Card('n',12), false) &&
       containsCard(listOfCards, Card('n',11), false) &&
       containsCard(listOfCards, Card('n',10), false)){
   
        for(Card crd : listOfCards){
            if((crd.isEqual(Card('n',1), false)||crd.isEqual(Card('n',13), false)||crd.isEqual(Card('n',12), false)||crd.isEqual(Card('n',11), false)|| crd.isEqual(Card('n',10), false)) /* && !(crd.isThisUsersCard() && containsCard(tableCards,crd,false))*/)
            highestCombination.push_back(crd);
        }
       
        isConsecutive = true;
    }else{
        int counter = 0;
        for(Card crd : listOfCards){
            if(counter == 3){ // Sorted List therefore check first 3 Cards only
                break;
            }else if(containsCard(listOfCards, Card('n',crd.getNumber() + 1), false)  &&
                     containsCard(listOfCards, Card('n',crd.getNumber() + 2), false)  &&
                     containsCard(listOfCards, Card('n',crd.getNumber() + 3), false)  &&
                     containsCard(listOfCards, Card('n',crd.getNumber() + 4), false) )
            {
                highestCombination.clear();
                for(Card card : listOfCards){
                    if((card.isEqual(Card('n',crd.getNumber()), false)||card.isEqual(Card('n',crd.getNumber() + 1), false)||card.isEqual(Card('n',crd.getNumber() + 2), false)||card.isEqual(Card('n',crd.getNumber() + 3), false)|| card.isEqual(Card('n',crd.getNumber() + 4), false)) /*&& !(card.isThisUsersCard() && containsCard(tableCards,card,false))*/)

                        highestCombination.push_back(card);
                }
                isConsecutive = true;
            }
            counter++;
        }
    }
    return isConsecutive;
}

bool Decider::isStraightFlush(){ // In case of two user have straigt flush TODO return high Card
    
    bool isSF = false;
    
    if(atLeastFiveSuits != 'n'){
        vector<Card> suitFilteredCardNumbers;
        for(Card crd : all7Cards){
            if(crd.getSuit() == atLeastFiveSuits){
                suitFilteredCardNumbers.push_back(crd);
            }
        }
        isSF = isConsecutive(suitFilteredCardNumbers);
    }else{
        isSF = false;
    }
    return isSF;
}

bool Decider::is4ofaKind(){ // TODO In Case of multiple User have 4 Of a Kind select high card
    
    bool is4K = false;
    
    for(pair<int,int> item : numbOfNumbers){
        if(item.second == 4){
            is4K = true;
            break;
        }
    }
    return is4K;
}

bool Decider::isFullHouse(){
    
    bool isFH = false;
    bool checked2 = false;
    bool checked3 = false;
    
    for(pair<int,int> item : numbOfNumbers){
        
        if(item.second == 3 && !checked3){
            checked3 = true;
        }else if(item.second >= 2){
            checked2 = true;
        }
        
        if(checked3 && checked2){
            isFH = true;
            break;
        }
    }
    
    return isFH;
}

bool Decider::isFlush(){
    return (atLeastFiveSuits != 'n') ?  true : false;
}

bool Decider::isStraight(){
    
    return isConsecutive(all7Cards);
}

bool Decider::is3ofaKind(){
    
    bool is3K = false;
    
    for(pair<int,int> item : numbOfNumbers){
        if(item.second == 3){
            is3K = true;
            break;
        }
    }
    return is3K;
}

bool Decider::is2Pair(){
    bool is2P = false;
    int counter = 0;
    
    for(pair<int,int> item : numbOfNumbers){
        if(item.second == 2){
            counter++;
        }
        if(counter == 2){
            is2P = true;
            break;
        }
    }
    return is2P;
}

bool Decider::is1Pair(){
    bool is1P = false;
    
    for(pair<int,int> item : numbOfNumbers){
        if(item.second == 2){
            is1P = true;
            break;
        }
    }
    return is1P;
}
