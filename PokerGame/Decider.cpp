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
    numbOfNumbers = countNumbers(all7Cards);
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

map<int, int> Decider::countNumbers(vector<Card> cards){
    
    map<int, int> numberCounts;
    
    for(Card crd : cards){
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
    
    if(containsCard(listOfCards, Card('n',1), false)  && // Suits are  here is not important because function with false parameter compare only numbers
       containsCard(listOfCards, Card('n',13), false) &&
       containsCard(listOfCards, Card('n',12), false) &&
       containsCard(listOfCards, Card('n',11), false) &&
       containsCard(listOfCards, Card('n',10), false)){
   
        for(Card crd : listOfCards){
            if((crd.isEqual(Card('n',1), false) || crd.isEqual(Card('n',13), false) || crd.isEqual(Card('n',12), false) || crd.isEqual(Card('n',11), false) || crd.isEqual(Card('n',10), false)) && !containsCard(highestCombination, crd, false))
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
                    if((card.isEqual(Card('n',crd.getNumber()), false) || card.isEqual(Card('n',crd.getNumber() + 1), false) || card.isEqual(Card('n',crd.getNumber() + 2), false) || card.isEqual(Card('n',crd.getNumber() + 3), false) || card.isEqual(Card('n',crd.getNumber() + 4), false)) && !containsCard(highestCombination, card, false))

                        highestCombination.push_back(card);
                }
                isConsecutive = true;
            }
            counter++;
        }
    }
    return isConsecutive;
}

bool Decider::isStraightFlush(){
    
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

bool Decider::is4ofaKind(){
    
    bool is4K = false;
    int mutlNum = 0;
    Card higestCard;
    
    for(pair<int,int> item : numbOfNumbers){
        if(item.second == 4){
            is4K = true;
            mutlNum = item.first;
            break;
        }
    }

    if(is4K){
        for(Card crd : all7Cards){
            
            if(crd.isEqual(Card('n',mutlNum), false)){
                highestCombination.push_back(crd);
            }else{
                if(crd.getValue() > higestCard.getValue()){
                    higestCard = crd;
                }
            }
        }
        highestCombination.push_back(higestCard);
    }

    return is4K;
}


map<Card,int> Decider::groupCardsWithNums(vector<Card> cards){

    map<Card,int> group;

    for(Card crd : cards){
        if(group.count(Card('n',crd.getNumber()))){
            group.insert(pair<Card,int>(Card('n',crd.getNumber()), group.find(Card('n',crd.getNumber()))->second++));
        }else{
            group.insert(pair<Card,int>(Card('n',crd.getNumber()), 1));
        }
    }
    return group;
}

bool Decider::isFullHouse(){
    
    bool isFH = false;
    
    bool checked2 = false;
    bool checked3 = false;
    
    Card threeNum;
    Card twoNum;
    
    map<Card,int> groupedCards = groupCardsWithNums(all7Cards);

    for(pair<Card,int> item : groupedCards){
        
        if(item.second == 3 && !checked3){
            checked3 = true;
            threeNum = item.first;
        }else if(item.second >= 2){
            checked2 = true;
            if(item.second == 3 && (threeNum.getValue() < item.first.getValue())){
                twoNum = threeNum;
                threeNum = item.first;
            }else{ // get biggest Two
                if(twoNum.getValue() < item.first.getValue()){
                    twoNum = item.first;
                }
            }
        }
    }

    if(checked3 && checked2){
        isFH = true;
    }
    
    int8_t counter = 0;
    
    if(isFH){
        for(Card crd : all7Cards){
            if(crd.isEqual(threeNum, false)){
                highestCombination.push_back(crd);
            }else if(crd.isEqual(twoNum, false) && counter < 2){
                highestCombination.push_back(crd);
                counter++;
            }
        }
    }

    return isFH;
}

bool Decider::isFlush(){
    
    bool isFL = (atLeastFiveSuits != 'n') ?  true : false;
    
    sort(all7Cards.begin(), all7Cards.end(), sortByValue);

    int8_t counter = 0;
    if(isFL){
        for(Card crd : all7Cards){
            if(crd.getSuit() == atLeastFiveSuits && counter < 5){
                highestCombination.push_back(crd);
                counter++;
            }
        }
    }
    
    return isFL;
}

bool Decider::isStraight(){
    
    return isConsecutive(all7Cards);
}

bool Decider::is3ofaKind(){
    
    bool is3K = false;
    Card max3;
    Card maxH1;
    Card maxH2;
    map<Card,int> groupedCards = groupCardsWithNums(all7Cards);
    
    for(pair<Card,int> item : groupedCards){
        if(item.second == 3){
            is3K = true;
            max3 = item.first;
        }else{
            if(item.first.getValue() > maxH1.getValue() || item.first.getValue() > maxH2.getValue()){
                if(item.first.getValue() > maxH1.getValue()){
                    maxH2 = maxH1;
                    maxH1 = item.first;
                }
                if(item.first.getValue() > maxH2.getValue() && item.first.getValue() < maxH1.getValue()){
                    maxH2 = item.first;
                }
            }
        }
    }
    
    if(is3K){
        for(Card crd: all7Cards){
            if(crd.isEqual(max3, false) || crd.isEqual(maxH1, false) || crd.isEqual(maxH2, false)  ){
                highestCombination.push_back(crd);
            }
        }
    }
    
    return is3K;
}

bool Decider::is2Pair(){
    bool is2P = false;
    int counter = 0;
    
    Card highTwo1;
    Card highTwo2;
    Card highCrd;
    
    map<Card,int> groupedCards = groupCardsWithNums(all7Cards);
    
    for(pair<Card,int> item : groupedCards){
        if(item.second == 2){
            if(item.first.getValue() > highTwo1.getValue() || item.first.getValue() > highTwo2.getValue()){
                if(item.first.getValue() > highTwo1.getValue()){
                    highTwo2 = highTwo1;
                    highTwo1 = item.first;
                }
                if(item.first.getValue() > highTwo2.getValue() && item.first.getValue() < highTwo1.getValue()){
                    highTwo2 = item.first;
                }
            }
            counter++;
        }
        if(counter == 2){
            is2P = true;
        }
    }
    
    for(pair<Card,int> item : groupedCards){
        if(item.first.getValue() > highCrd.getValue() && !(item.first.isEqual(highTwo1, false))  && !(item.first.isEqual(highTwo2, false))){
            highCrd = item.first;
        }
    }

    if(is2P){
        for(Card crd: all7Cards){
            if(crd.isEqual(highTwo1, false) || crd.isEqual(highTwo2, false)){
                highestCombination.push_back(crd);
            }else if(crd.isEqual(highCrd, false) && !containsCard(highestCombination, highCrd, false) ){
                highestCombination.push_back(crd);
            }
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
