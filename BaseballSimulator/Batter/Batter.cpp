//
//  Batter.cpp
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//
#include <iostream>
#include "Batter.h"
#include "Player.h"
#include "Team.h"
#include "Game.h"

#include <string>

//Batter::Batter(Player &p, string position, double trueBatAvg1, double trueSlugPct1, double trueOBP1) : Player(p)
//{
//
//    //this is because when the player file is first read in it can make the players there then for team file it will assign everything to a team and make batters/pitchers
//    trueBatAvg = trueBatAvg1;
//    trueSlugPct = trueSlugPct1;
//    trueOBP = trueOBP1;
//    OBP = trueOBP;
//    singles = 0;
//    doubles = 0;
//    triples = 0;
//    batAvg = trueBatAvg;
//	slugPct = trueSlugPct;
//    opsPlus = -1;
//    HBP = 0;
//    plateApps = 0;
//    setPosition(position);
//};
Batter::Batter(Player& p, batter_visibleStats &vis, batter_invisibleStats &invis) : Player(p)
{
    hasInfo = true;
    visibleStats = vis;
    invisibleStats = invis;
    setTrueStats(visibleStats.avg, visibleStats.slg, visibleStats.obp);
};
Batter::Batter(string name1, string position, char batsO, double tBA, double tSlg, double tOBP) : Player(name1)
{
    hasInfo = false;
    invisibleStats.trueAvg = tBA;
    invisibleStats.trueSlg = tSlg;
    invisibleStats.trueOBP = tOBP;
    visibleStats.obp = tOBP;
    visibleStats.singles = 0;
    visibleStats.doubles = 0;
    visibleStats.triples = 0;
    visibleStats.avg = tBA;
    visibleStats.slg= tSlg;
    visibleStats.opsPlus = -1;
    visibleStats.hbp = 0;
    visibleStats.plateApps = 0;
    setPosition(position);
    setBatsO(batsO);
    setTrueStats(visibleStats.avg, visibleStats.slg, visibleStats.obp);
};
void Batter::setTrueStats(double batAvg, double slugPct, double obp)
{
	invisibleStats.trueAvg = batAvg;
	invisibleStats.trueSlg = slugPct;
	invisibleStats.trueOBP = obp;
};
void Batter::updateStats()
{
    
};
void getGameStats(Game g)
{
    
};

void Batter::printStats()
{
    Player::printInfo();
    cout << "BATTER STATS : ";
    cout << "at bats : " << visibleStats.atBats << endl;
    cout << "hits : " << visibleStats.hits << endl;
    cout << "strikeouts : " << visibleStats.strikeouts << endl;
    cout << "walks : " << visibleStats.walks << endl;
    cout << "games played : " << visibleStats.gp  << endl;
    cout << "avg = " << visibleStats.avg << ", ";
    cout << "slg = " << visibleStats.slg << ", ";
    cout << "obp = " << visibleStats.obp << endl;
    cout << "singles = " << visibleStats.singles << ", ";
    cout << "doubles = " << visibleStats.doubles << ", ";
    cout << "triples = " << visibleStats.triples << ", ";
    cout << "home runs = " << visibleStats.homeRuns << ", ";
    cout << "PAs = " << visibleStats.plateApps << ", ";
    cout << "ops+ = " << visibleStats.opsPlus << ", ";
    cout << "rbi = " << visibleStats.rbi << ", ";
    cout << "sb = " << visibleStats.sb << ", ";
    cout << "cs = " << visibleStats.cs << endl << endl;
};
//add other methods here
