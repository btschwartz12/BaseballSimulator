//
//  Player.h
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//
#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include "playerStructs.h"



//during the declaration of the PLayer class, the compiler doesn't know what AtBat is
// when doing the line below, you are telling the compiler trust me, this exists
// this works, but when you declare AtBat somewhere yu must use an *instance, because
// it still doesnt have the class definition
// https://stackoverflow.com/questions/4964482/how-to-create-two-classes-in-c-which-use-each-other-as-data
class AtBat;
class Team;
class Game;//why

using namespace std;

class Player
{//can i have different constuctors for player and batter/pitcher
protected:
   //should i do variable isPositionPlayer
    string name;//"first_last"
    string position;// SP, RP, CL, CP, C, 1B, 2B, 3B, SS, LF, CF, RF, DH
    playerMiscInfo info;
    char batsO = 'X', throwsO = 'X'; // 'L or 'R' or 'S'
    int number = -1;
    
    //still do this********************************************
    bool starter; // if they start or not
    
    vector<AtBat>* atBatList;  //this will work for computing indiv game stats bc a atbat knows the game
    Team* team;
    
    
        //NEW
    bool detailed; //true if age,weight,number are included in the player
    string teamName = "notset";
   // bool empty;
public:
	playerStatTuple tuple;
    playerStatTuple pitcherBattingTuple;
    bool complete;
    //constructors for file reading
    Player(string name); //when not in playerFile
    Player(int num, string name1, string position1, char batsOrientation, char throwsOrientation, playerMiscInfo miscInfo);
    //constructors for manual creation
        //maybe i can do this with other constructor
    //Player(string name, char throwsOrientation
    
    //special constructors
    Player () {};//{ empty = true; }; //this lets at bat class build;
    Player(const Player &p);
    ~Player() {};//cout << "~~~~" << name << "  destroyed" << endl;
    
    //other functions
    void updateStats(AtBat ab);
    AtBat getAtBat(int n);
    vector<AtBat> getGameAtBats(Game g);//should i even care if they have 2 ABs in an inning
    vector<AtBat> getAtBatList();
    void checkAge(int n);
    void checkName(string s);
    void printInfo();
    
    
    
    //mutators / accessors
    string getName() { return name; };
    string getTeamName() { return teamName; }; void setTeamName(string s) { teamName = s; };
    string getPosition() { return position; }; void setPosition(string s) { position = s; };
    string getHeight() { return info.height; }; void setHeight(string s) { info.height = s; };
    string getNationality() { return info.nationality; }; void setNationality(string s) { info.nationality = s; };
    string getDOB() { return info.dateOfBirth; }; void setDOB(string s) { info.dateOfBirth = s; };
    int getAge() { return info.age; };
    char getBatsO() { return batsO; }; void setBatsO(char c);
    char getThrowsO() { return throwsO; }; void setThrowsO(char c);;
    int getNumber() { return number; }; void setNumber(int n) { number = n; }
    bool isDetailed() { return detailed; };
  //  bool isEmpty() { return empty; };
    bool isStarter() { return starter; };
    Team getTeam(); void setTeam(Team &t);
    
    //for tuple
//    void setTupleTeam(vector<string> v) { tuple.team = v; };
//    void setTupleRatio(vector<string> v) { tuple.ratios = v; };
//    void setTuplePitches(vector<string> v) { tuple.pitches = v; };
    
};
#endif
