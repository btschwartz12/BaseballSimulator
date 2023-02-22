//
//  Pitcher.cpp
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//
#include <iostream>
#include <string>
#include "Pitcher.h"
#include "Team.h"

Pitcher::Pitcher(Player &p, pitcher_visibleStats vis, pitcher_invisibleStats invis) : Player(p)
{
    hasInfo = true;
    hasBattingStats = false;
    visibleStats = vis;
    invisibleStats = invis;
};
Pitcher::Pitcher(Player &p, pitcher_visibleStats vis, pitcher_invisibleStats invis, batter_invisibleStats batInvis) : Player(p)
{
    hasInfo = true;
    hasBattingStats = true;
    batInvisStats = batInvis;
    visibleStats = vis;
    invisibleStats = invis;
};
Pitcher::Pitcher(string name, string position, double trueERA, double trueK9, double trueWHIP) : Player(name)
{
    hasInfo = false;
    invisibleStats.trueERA = trueERA;
    invisibleStats.trueK9 = trueK9;
    invisibleStats.trueWHIP = trueWHIP;
    setPosition(position);
};
void Pitcher::updateStats()
{
    
};
//add other methods here
void Pitcher::printStats()
{
    
//    cout << "\nPITCHER STATS : ";
//    cout << "FBspeed = " << FBspeed << "mph, ";
//    cout << "fb% = " << fastballPct << "%, ";
//    cout << "pitchTypes = " << pitchTypes << ", ";
//    cout << "K/9 = " << k9 << ", ";
//    cout << "WHIP = " << WHIP << ", ";
//    cout << "IP = " << IP << ", ";
//    cout << "ERA = " << ERA << ", ";
//    cout << "BF = " << battersFaced << ", ";
//    cout << "totP = " << totPitches << ", ";
//    cout << "P = " << pitches << endl;
    //dont forget home runs
};
