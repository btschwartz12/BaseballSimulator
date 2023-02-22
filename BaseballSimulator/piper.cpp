//
//  MAIN
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//

// be able to either simulate 1 game or millions of games, see tendencies after games
// allow user to enter player stats
// have a true average, then lower it if they are in a slump and vice versa (can average the true vs actual and use that for randomization)
// seperate averages for how they actually perform
//make a function for error catching?????
//might be easier to use friend functions idk tho
//the player class does not need to store atBats, but I think it would be cool if it did
// graphics?

//destruct everything


#include <iostream>
#include <stdio.h>
#include <ctime>
#include <math.h>
#include <memory>
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

#include "AtBat.h"
#include "Game.h"
#include "Team.h"
#include "Player.h"
#include "Batter.h"
#include "Pitcher.h"
#include "playerFile.h"
#include "TeamFile.h"
//#include "misc.cpp"
using namespace std;

//https://nektony.com/duplicate-finder-free/folders-permission

//eventually just have one function that uses all of these so main isnt cluttered

int main()
{
    string path = "/Users/benschwartz/Desktop/C++/BaseballSimulator/teamFiles";
    
 
    
    
    //run and check
    vector<TeamFile> vec = readAllFiles(path);
    for(TeamFile t: vec)
        t.printInfo();
    

    
    
    
    
    
    //working on this
   // TeamFile t = makeTeamFile(path, "Cleveland Indians");
    
    
    
    
    
    
    
   // vector<TeamFile> teamFiles = readAllFiles(path);

  
    cout << "\n\npippy" << endl;
    
    cout << "\n******\nHello World! " << time(0) << "\n";
    srand(static_cast<int>(time(0)));
    int num = abs(rand());
    cout << "\nwill return " << num % 256 << endl;
    return num;
}

//i want players to be able to add themselves to the player list

//do i even need a constructor with team parameter for playrs
