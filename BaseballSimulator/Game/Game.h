//
//  Game.h
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//
#pragma once

#ifndef GAME_H
#define GAME_H

#include "Team.h"
#include "Batter.h"
#include "Pitcher.h"
#include <string>

class AtBat;

//after game is completed how will i have hits/errors/lob be for that spot in the game and not total after the game
//make a struct called gameState for each atBat?

//find a time to set numbers, for when games are long simulated (maybe with logic on what is chosen to be done i wont need mult. batter constructors?

//if home team is in national league, adjust accordingly

class Game
{
private:
    vector<vector<AtBat>> *gameLog;
    Team homeTeam, awayTeam;
	int inning, homeHits, awayHits, homeErrors, awayErrors, homeLeftOnBase, awayLeftOnBase, homeTeamScore, awayTeamScore;
	bool topHalf;
    bool complete;
    bool started;
    string weather;
	//add more variables
public:
	//constructors
    Game(Team t1, Team t2, int homeTeam, string weather1);
    Game() {}; //for atbat class
	
    //othermethods
    bool isComplete();
    void print();
    void userStartGame(bool disp);//when user folows through game
    void simPromptManual();
    void simPromptAutomatic();
    void completeGame();
    void printStartingPitchers();

    
    
    //mutators / accessors
    vector<vector<AtBat>> getGameLog();
    Team getHomeTeam() { return homeTeam; };
    Team getAwayTeam() { return awayTeam; };
    int getInning() { return inning; };
    bool isTopOfInning() { return topHalf; };
    int getHomeHits() { return homeHits; };
    int getAwayHits() { return awayHits; };
    int getHomeErrors() { return homeErrors; };
    int getAwayErrors() { return awayErrors; };
    int getHomeLeftOnBase() { return homeLeftOnBase; };
    int getAwayLeftOnBase() { return awayLeftOnBase; };
    int getHomeTeamScore() { return homeTeamScore; };
    int getAwayTeamScore() { return awayTeamScore; };
    string getWeather() { return weather; };
    

};
struct gameState
{
    int inning;
    bool topHalf;
    int hHits, aHits, hErrors, aErrors, hLOB, aLOB, hScore, aScore;
    gameState(int inning1, bool topHalf1, int hHits1, int aHits1, int hErrors1, int aErrors1, int hLOB1, int aLOB1, int hScore1, int aScore1) : inning{inning1}, topHalf{topHalf1}, hHits{hHits1}, aHits{aHits1}, hErrors{hErrors1}, aErrors{aErrors1}, hLOB{hLOB1}, aLOB{aLOB1}, hScore{hScore1}, aScore{aScore1} {};
    gameState() {};
    
};

#endif
