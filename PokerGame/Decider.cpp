//
//  Decider.cpp
//  PokerGame
//
//  Created by Tunc Alpman on 28/12/2017.
//  Copyright © 2017 Tunc Alpman. All rights reserved.
//

#include "Decider.hpp"


using namespace std;

bool sortNumbers (Card first,Card second) { return (first.getNumber() < second.getNumber());}
bool sortNumeric (int first,int second) { return (first < second);}
bool sortSuits (Card first,Card second) { return (first.getSuit() < second.getSuit());}
int max (int first,int second) {if(first > second) return first; else return second;}

Decider::Decider(){
    
}

Decider::Decider(vector<Card> all7Cards){
    this->all7Cards = all7Cards;
    numbOfSuits = countSuits();
    numbOfNumbers = countNumbers();
    atLeastFiveSuits = atLeastFiveSuit();
}

bool Decider::isRoyalFlush(){ // Ex: (S_10, S_11, S_12, S_13, S_1, C_1, C_11)
    
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

bool Decider::isStraightFlush(){ // In case of two user have straigt flush TODO return high Card
    
    bool isSF = false;
    
    if(atLeastFiveSuits != 'n'){
        vector<int> suitFilteredCardNumbers;
        for(Card crd : all7Cards){
            if(crd.getSuit() == atLeastFiveSuits){
                suitFilteredCardNumbers.push_back(crd.getNumber());
            }
        }
        sort(suitFilteredCardNumbers.begin(), suitFilteredCardNumbers.end(), sortNumeric);
        
        if(find(suitFilteredCardNumbers.begin(), suitFilteredCardNumbers.end(), 1) != suitFilteredCardNumbers.end()  &&
           find(suitFilteredCardNumbers.begin(), suitFilteredCardNumbers.end(), 13) != suitFilteredCardNumbers.end() &&
           find(suitFilteredCardNumbers.begin(), suitFilteredCardNumbers.end(), 12) != suitFilteredCardNumbers.end() &&
           find(suitFilteredCardNumbers.begin(), suitFilteredCardNumbers.end(), 11) != suitFilteredCardNumbers.end() &&
           find(suitFilteredCardNumbers.begin(), suitFilteredCardNumbers.end(), 10) != suitFilteredCardNumbers.end()){
        
            isSF = true;
        }else{
            int counter = 0;
            for(int num : suitFilteredCardNumbers){
                if(counter == 3){ // Sorted List therefore check first 3 Cards only
                    break;
                }else if(find(suitFilteredCardNumbers.begin(), suitFilteredCardNumbers.end(), num +1) != suitFilteredCardNumbers.end() &&
                   find(suitFilteredCardNumbers.begin(), suitFilteredCardNumbers.end(), num +2) != suitFilteredCardNumbers.end()  &&
                   find(suitFilteredCardNumbers.begin(), suitFilteredCardNumbers.end(), num +3) != suitFilteredCardNumbers.end()  &&
                   find(suitFilteredCardNumbers.begin(), suitFilteredCardNumbers.end(), num +4) != suitFilteredCardNumbers.end())
                {
                    isSF = true;
                    break;
                }
                counter++;
            }
        }
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
    // TODO
    return false;
}

bool Decider::is3ofaKind(){
    // TODO
    return false;
}

bool Decider::is2Pair(){
    // TODO
    return false;
}

bool Decider::is1Pair(){
    // TODO
    return false;
}
