//
//  AtBat.cpp
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//
#include "AtBat.h"
#include "Game.h"
#include "Batter.h"
#include "Pitch.h"
#include "Pitcher.h"


AtBat::AtBat(Game g, Batter b, Pitcher p) // these three MUST have default constructor, wonder why????
{//bulk of work will be done here. maybe create pitch objects in here?
    game = g;
    batter = b;
    gameState gs(g.getInning(), g.isTopOfInning(), g.getHomeHits(), g.getAwayHits(), g.getHomeErrors(), g.getAwayErrors(), g.getHomeLeftOnBase(), g.getAwayLeftOnBase(), g.getHomeTeamScore(), g.getAwayTeamScore());
    condition = gs;
    pitcher = p;
    inPlay = true;
};
void AtBat::print()
{
    cout << "\n\n******Batter : " << endl;
  // batter.printStats();
    cout << "\nPitcher : " << endl;
  //  pitcher.printStats();
    cout << "\nGame : " << endl;
    game.print();
};
