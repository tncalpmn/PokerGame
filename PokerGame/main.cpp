//
//  main.cpp
//  PokerGame
//
//  Created by Tunc Alpman on 05/12/2017.
//  Copyright © 2017 Tunc Alpman. All rights reserved.
//

#include <iostream>
#include "Table.hpp"
#include "User.hpp"
#include "Decider.hpp"
#include "Debugger.hpp"
#include "Globals.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

    Debugger debugger;
    debugger.setStatus(isDebuggerOn);
    
    if(isDebuggerOn){
        debugger.start();
    }else{
        cout << "Let the Game Begin!\n";
        
        Table mainTable;
        mainTable.createTable();
    
        while(true) {
        
            mainTable.startRound();

            for(User singlePlayer: mainTable.allUsers){
                singlePlayer.getPlayerInfo();
            }
            
            cout << "Money On the Table" << endl;
            mainTable.moneyOnTable.getChipInfo();
        }
    }
    return 0;
}
