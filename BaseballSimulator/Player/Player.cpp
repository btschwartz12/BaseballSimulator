//
//  Player.cpp
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//
#include <iostream>
#include "Player.h"
#include "AtBat.h"


#include <string>
#include <vector>

using namespace std;



Player::Player(string name1)
{//can I just put this in the header
   // empty = false;
    detailed = false;
    number = -1;
    name = name1;
    position = "notset";
    info = playerMiscInfo("notset", "notset", "notset", -1, -1, -1);
//    throwsO = 'X';
//    batsO = 'X';
    atBatList = new vector<AtBat>;
};
Player::Player(int num, string name1, string position1, char batsOrientation, char throwsOrientation, playerMiscInfo miscInfo)
{
   // empty = false;
    detailed = true;
    info = miscInfo;
    number = num;
    name = name1;
    position = position1;
    throwsO = throwsOrientation;
    batsO = batsOrientation;
    atBatList = new vector<AtBat>;
};
Player::Player(const Player &p)
{//copy constructor this is very useful
  //  empty = false;
    
    detailed = p.detailed;
    name = p.name;
    info = p.info;
    position = p.position;
    throwsO = p.throwsO;
    batsO = p.batsO;
    atBatList = p.atBatList;
    number = p.number;
    team = p.team;
    atBatList = p.atBatList;
    tuple = p.tuple;
    teamName = p.teamName;
    pitcherBattingTuple = p.pitcherBattingTuple;
    complete = p.complete;
    //********************************************
    //MAKE SURE ALL VARIABLES ARE INCLUDED IN HERE
    //********************************************

};
void Player::setBatsO(char c)
{
    if(batsO != 'X' && batsO != c)
        cout << "ERROR : " << name << " has multiplebatsO" << endl;
    batsO = c;
    
};
void Player::setThrowsO(char c)
{
    if(throwsO != 'X' && throwsO != c)
        cout << "ERROR : " << name << " has multiple throwsO" << endl;
    throwsO = c;
}
void Player::checkAge(int n)
{
    if(info.age != -1 && n != info.age)
        cout << "ERROR : non-matching age (" << name << ")" << endl;
    info.age = n;
}
void Player::updateStats(AtBat ab)
{
    atBatList->push_back(ab);
    //find out from the at bat what happened, and then adjust stats accordingly
};
AtBat Player::getAtBat(int n)
{
    if(n >= atBatList->size()){
        cout << "ERROR: out of range index"; /*return AtBat();*/ }//return something else
    return atBatList->at(n);
};
vector<AtBat> Player::getGameAtBats(Game g)
{
    vector<AtBat> gameABlist;
    for(AtBat a: *atBatList)
    {//if its in the game add it
        //if(a.getGame() == g)//overload the operator to check the date of each gamr
            gameABlist.push_back(a);
    }
    return *atBatList;
};
vector<AtBat> Player::getAtBatList()
{
    return *atBatList;//i dont want this how can i fix it
};
void Player::setTeam(Team &t)
{
    team = &t;
};
Team Player::getTeam()
{
    if(team == nullptr)
        cout << "NO TEAM";
    return *team;
};
bool operator ==(Player p1, Player p2)
{
    //return &p1 == &p2;
    return p1.getName() == p2.getName();
};
void Player::checkName(string s)
{
    if(name == "")
        name = s;
    else if(name != s)
        cout << "ERROR : non-matching names" << endl;
};
void Player::printInfo()
{//for batters and pitchers print call super
    
    cout << "******\nname : " << name << endl;
    cout << boolalpha << "has info : " << detailed << endl << "****\n";
    if(detailed)
    {
        cout << "number : " << number << endl;
        cout << "position : " << position << endl;
        cout << "nationality : " << info.nationality << endl;
        cout << "age : " << info.age << endl;
        cout << "bats : " << batsO << endl;
        cout << "throws : " << throwsO << endl;
        cout << "height : " << info.height << endl;
        cout << "weight : " << info.weight << endl;
        cout << "DOB : " << info.dateOfBirth << endl;
        cout << "1st year : " << info.yearStarted << endl;
    }
    else
    {
        if(batsO == 'X')
            cout << "throws : " << throwsO << endl;
        else //if(throwsO == 'X')
            cout << "bats : " << batsO << endl;
    }
    

    cout << endl;
    //for(AtBat a: *atBatList){}
        //a.print();

};

