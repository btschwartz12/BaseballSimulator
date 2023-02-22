//
//  Pitch.h
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//
#pragma once

#include "Pitcher.h"
#include "Game.h"

struct Pitch
{
    Pitcher pitcher;
    Game game;
    double speed;
    char pitchType;
    double spinRate;//will determine if swing/miss //https://fivethirtyeight.com/features/baseballs-top-staffs-have-come-around-on-the-high-spin-fastball/
    Pitch(Pitcher p, Game g)
    {
        pitcher = p;
        game = g;
        speed = 98.5;
        pitchType = 'y';
        spinRate = 203.23;
    }
};
