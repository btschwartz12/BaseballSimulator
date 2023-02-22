//
//  AtBat.h
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//
#pragma once
#ifndef ATBAT_H
#define ATBAT_H

#include "Game.h"
#include "Batter.h"
#include "Pitcher.h"

//https://batflipsandnerds.com/2018/07/23/the-anatomy-of-an-at-bat/

class AtBat
{
private:
	bool inPlay;//many many others for tracking what happens

    Game game;
    gameState condition;
    Batter batter;
    Pitcher pitcher;

public:
	//constructors
    AtBat(Game g, Batter b, Pitcher p);//when finding outcome for at bat, use pitcher with pitches to create probability, then use batAvg, and if fail, use OBP for second chance
    AtBat() {};//to build player class

    //other methods
    void print();

    //accessors / mutators?
    Game getGame() { return game; };
    Batter getBatter() { return batter; };
    Pitcher getPitcher() { return pitcher; };

};
#endif
