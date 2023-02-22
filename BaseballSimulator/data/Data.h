//
//  Data.h
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//

#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <array>
#include "Player.h"
#include <fstream>
#include <vector>
#include "Team.h"
#include "Player.h"
#include "Batter.h"
#include "Pitcher.h"
#include "Game.h"
#include "teamFile.h"
#include <sstream>

using namespace std;

struct Data
{
    //this shit retarded
    Player playerList[100];
    Team teamList[100];
    Game gameList[100];
    int playerIDs[100];
    int gameIDs[100];
    int teamIDs[100];
    void resetData()
    {
        for(int i = 0; i < 100; i++)
        {
            playerIDs[i] = -1;
            teamIDs[i] = -1;
            gameIDs[i] = -1;
            //do i need to initialize the other lists
        }
    }
};



#endif /* ID_hpp */
