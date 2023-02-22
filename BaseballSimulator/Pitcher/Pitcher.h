//
//  Pitcher.h
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//
#pragma once
#ifndef PITCHER_H
#define PITCHER_H

#include <iostream>
#include "Player.h"
#include <string>
#include <vector>

//class Game; // try including


// pitch speed or naw


using namespace std;
class Pitcher : public Player
{
private:
    bool hasInfo;
    pitcher_visibleStats visibleStats;
    pitcher_invisibleStats invisibleStats;
    batter_invisibleStats batVisStats;
    batter_invisibleStats batInvisStats;
public:
    bool hasBattingStats;
    //constructors for file
    Pitcher(Player&, pitcher_visibleStats, pitcher_invisibleStats);
    
    //manual constructors
    Pitcher(string name, string position, double trueERA, double trueK9, double trueWHIP);
    Pitcher(Player &p, pitcher_visibleStats vis, pitcher_invisibleStats invis, batter_invisibleStats batInvis);
    
    //special constructors
    Pitcher() {};//for atbat class
    ~Pitcher() {};
    
	//other methods
    void getGameStats(Game g);
    void updateStats(); //maybe have the addAtBat function in Player call this for both pitchers and batters
    void printStats();
    int testo() { return 1; };
    
    
    //accessors / mutators
    int getW() { return visibleStats.wins; }; void setW(int n) { visibleStats.wins = n; };
    int getL() { return visibleStats.losses; }; void setL(int n) { visibleStats.losses = n; };
    double getERA() { return visibleStats.era; }; void setERA(double n) { visibleStats.era = n; };
    int getGP() { return visibleStats.gamesPitched; }; void setGP(int n) { visibleStats.gamesPitched = n; };
    int getGS() { return visibleStats.gamesStarted; }; void setGS(int n) { visibleStats.gamesStarted = n; };
    int getCG() { return visibleStats.completeGames; }; void setCG(int n) { visibleStats.completeGames = n; };
    int getSHO() { return visibleStats.shutouts; }; void setSHO(int n) { visibleStats.shutouts = n; };
    double getIP() { return visibleStats.ip; }; void setIP(double n) { visibleStats.ip = n; };
    int getH() { return visibleStats.hits; }; void setH(int n) { visibleStats.hits = n; };
    int getR() { return visibleStats.runs; }; void setR(int n) { visibleStats.runs = n; };
    int getER() { return visibleStats.er; }; void setER(int n) { visibleStats.er = n; };
    int getHR() { return visibleStats.hr; }; void setHR(int n) { visibleStats.hr = n; };
    int getBB() { return visibleStats.bb; }; void setBB(int n) { visibleStats.bb = n; };
    int getSO() { return visibleStats.so; }; void setSO(int n) { visibleStats.so = n; };
    int getHBP() { return visibleStats.hbp; }; void setHBP(int n) { visibleStats.hbp = n; };
    int getBF() { return visibleStats.bf; }; void setBF(int n) { visibleStats.bf = n; };
    double getFIP() { return visibleStats.fip; }; void setFIP(double n) { visibleStats.fip = n; };
    double getWHIP() { return visibleStats.whip; }; void setWHIP(double n) { visibleStats.whip = n; };
    double getH9() { return visibleStats.h9; }; void setH9(double n) { visibleStats.h9 = n; };
    double getHR9() { return visibleStats.hr9; }; void setHR9(double n) { visibleStats.hr9 = n; };
    double getBB9() { return visibleStats.bb9; }; void setBB9(double n) { visibleStats.bb9 = n; };
    double getKperBB() { return visibleStats.K_per_BB; }; void setKperBB(double n) { visibleStats.K_per_BB = n; };

};
#endif
