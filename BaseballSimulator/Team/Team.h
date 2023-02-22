//
//  Team.h
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//
#pragma once
#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include "Pitcher.h"
#include "Batter.h"
#include <vector>
#include <map>

#include <string>

class Game;

class Team
{
    
    //should i do national league and american league
    
private:
    vector<Game>* gameList;
    vector<Player> players;
    vector<Batter> batters;
    vector<Pitcher> pitchers;
	int totHits = 0, totErrors = 0, totLeftOnBase = 0;
    int wins = 0, losses = 0;
    map<string, int> posMap;//players or ints? 
    string name;
    string manager;
public:
    //constructors
    Team(string name1, vector<Batter> bs, vector<Pitcher> ps);
    Team() {};//so that the game.h can build
    
    
    //other methods
    void addGame(Game g);
    void printTeam();
    void printTeamStats();
    
    //accessors / mutators
    vector<Player> getPlayers() { return players; };
    vector<Batter> getBatters() { return batters; };
    vector<Pitcher> getPitchers() { return pitchers; };
    double getAverage();//do this for other stats for like home runs and stuff(look thru ABs, not batters)
    int getTotHits() { return totHits; };
    int getTotErrors() { return totErrors; };
    int getTotLOB() { return totLeftOnBase; };
    int getWins() { return wins; };
    int getLosses() { return losses; };
    int getSingles();
    int getDoubles();
    int getTriples();
    int getHomeRuns();
    int getStrikeouts();
    Batter getBatter(int spotInLineup);
    Pitcher getPitcher(bool isSstarter);
    string getName() { return name; };
    
};
//
#endif
