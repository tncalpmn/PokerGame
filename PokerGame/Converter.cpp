//
//  Converter.cpp
//  PokerGame
//
//  Created by Tunc Alpman on 19/03/2018.
//  Copyright © 2018 Tunc Alpman. All rights reserved.
//

#include "Converter.hpp"

bool Converter::removeAmountAsChips(int amount, Chips &availableAmount, Chips init){
    
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

Chips& Converter::changeNextAvailableCoinsToOnes(Chips &availableAmount){
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

Chips Converter::amountToChipConverter(int amount, Chips init){
    
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
