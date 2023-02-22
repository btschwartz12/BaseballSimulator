//
//  Batter.h
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//
#pragma once

#ifndef BATTER_H
#define BATTER_H

#include <iostream>
#include <string>
#include "Player.h"

class Game;

using namespace std;

class Batter : public Player
{
private:
    bool hasInfo; // if it has info from baseball reference
    batter_invisibleStats invisibleStats; // i want a better name
    batter_visibleStats visibleStats;
public:
	//constructors for files
    //Batter(Player &p, string position, double trueBatAvg, double trueSlugPct, double trueOBP);
    
    Batter(Player&, batter_visibleStats&, batter_invisibleStats&);
    
    //manual constructors
    Batter(string name, string position, char batsO, double tBA, double tSlg, double tOBP);
    
    //special constructors
    Batter() {};//for atbat class
    ~Batter() {};

    //other methods
    void updateStats(); // check pitcher.cpp comment
    void getGameStats(Game);
    void printStats();
    int testo() { return 0; };
    void setTrueStats(double batAvg, double slugPct, double obp);
    
	//simple mutators / accessors
    
    batter_visibleStats& getVisStats() { return visibleStats; };
    batter_invisibleStats& getInvisStats() { return invisibleStats; };

    
    
    int getHits() { return visibleStats.hits; }; void setHits(int n) { visibleStats.hits = n; };
    int getGamesPlayed(){ return visibleStats.gp; }; void setGamesPlayed(int n) { visibleStats.gp = n; };
    int getHomeRuns() { return visibleStats.homeRuns; }; void setHomeRuns(int n) { visibleStats.homeRuns = n; };
    int getStrikeouts() { return visibleStats.strikeouts; }; void setStrikeouts(int n) { visibleStats.strikeouts = n; };
    int getWalks() { return visibleStats.walks; }; void setWalks(int n) { visibleStats.walks = n; };
    
    
    int getAtBats() { return visibleStats.atBats; }; void setAtBats(int n) { visibleStats.atBats = n; };
    int getRBI() { return visibleStats.rbi; }; void setRBI(int n) { visibleStats.rbi = n; };
    int getSB() { return visibleStats.sb; }; void setSB(int n) { visibleStats.sb = n; };
    int getCS() { return visibleStats.cs; }; void setCS(int n) { visibleStats.cs = n; };
    int getHBP() { return visibleStats.hbp; }; void setHBP(int n) { visibleStats.hbp = n; };
    int getPAs() { return visibleStats.plateApps; }; void setPAs(int n) { visibleStats.plateApps = n; };
    int getSingles() { return visibleStats.singles; }; void setSingles(int n) { visibleStats.singles = n; };
    int getDoubles() { return visibleStats.doubles; }; void setDoubles(int n) { visibleStats.doubles = n; };
    int getTriples() { return visibleStats.triples; }; void setTriples(int n) { visibleStats.triples = n; };
    int getPlateApps() { return visibleStats.plateApps; }; void setPlateApps(int n) { visibleStats.plateApps = n; };
	double getBatAvg() { return visibleStats.avg; }; void setBatAvg(double n) { visibleStats.avg = n; };
    double getSlugPct() { return visibleStats.slg; }; void setSlugAvg(double n) { visibleStats.slg = n; };
    double getOBP() { return visibleStats.obp; }; void setOBP(double n) { visibleStats.obp = n; };
    double getOPSplus() { return visibleStats.opsPlus; }; void setOPSplus(double n) { visibleStats.opsPlus = n; };

    void resetStats() { visibleStats.avg = invisibleStats.trueAvg; visibleStats.slg = invisibleStats.trueSlg; visibleStats.obp = invisibleStats.trueOBP; };
};


#endif
