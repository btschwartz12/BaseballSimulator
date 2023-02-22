//
//  Game.cpp
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//
#include <iostream>
#include <string>
#include "Team.h"
#include "Game.h"
#include "AtBat.h"


using namespace std;

Game::Game(Team t1, Team t2, int homeTeamNum, string weather1)
{
    if(homeTeamNum == 1){
        homeTeam = t1; awayTeam = t2;}
    else if(homeTeamNum == 2){
        homeTeam = t2; awayTeam = t1;}
    else
        std::cout << "ERROR: incorrect homeTeamNum";
	inning = 1;
	topHalf = true;
	homeTeamScore = 0;
	awayTeamScore = 0;
	homeHits = 0;
    awayHits = 0;
	homeErrors = 0;
    awayErrors = 0;
	homeLeftOnBase = 0;
    awayLeftOnBase = 0;
    weather = "clear_warm";
};
void Game::completeGame()
{
    //this will do the entire game
    vector<AtBat> inning1(9);// this needs a default constructor for atbat, is there another way i can use this?
    gameLog->push_back(inning1);
    
    
    
};




void Game::userStartGame(bool disp)
{
    //will print the names and records of both teams
    if(disp)
    {
        cout << "*\n\t\tWELCOME TO A BEAUTIFUL CONTEST BETWEEN :" << endl;
        cout << "\t" << homeTeam.getName() << " (home) | record = (" << homeTeam.getWins() << "-" << awayTeam.getLosses() << ")" << endl;
        cout << "\t" << awayTeam.getName() << " (away) | record = (" << awayTeam.getWins() << "-" << awayTeam.getLosses() << ")" << endl;
        //this will ask if they want to know any starting pitchers
        char c;
        cout << "\nwould you like to know starting pitchers? (y/n) : ";
        cin >> c;
        if(c == 'y')
            printStartingPitchers();
        else
            cout << "\nsorry for asking." << endl;
        //ask if they want any others
        char d;
        cout << "\nwould you like to know any player's stats? (y/n) : ";
        cin >> d;
        if(d == 'y')
        {
            int a;
            cout << "home team stats(0) or away team stats(1) : ";
            cin >> a;
            if(a == 0)
                homeTeam.printTeamStats();//need to write this
            else if(a == 1)
                awayTeam.printTeamStats();
            else
                cout << "\nsorry for asking." << endl << endl;
        }
        else
            cout << "\nokay sorry." << endl;
    }
    
    
};
void Game::simPromptManual()
{
    //have a menu on where you want to be in the game
    int i = 0;
    cout << "choose where you want to sim to : " << endl;
    cout << "\n\t1. next pitch" << endl;
    cout << "\t2. next at-bat" << endl;
    cout << "\t3. next half-inning" << endl;
    cout << "\t4. next inning" << endl;
    cout << "\t5. next score" << endl;
    cout << "\t6. end of game" << endl;
    cin >> i;
};
void Game::simPromptAutomatic()
{
    //have this one not skip to the next thing, can ask them where they want it to stop, and what
    //it should be incremented by, then use a time.wait function to make the game flow thru
    
    //maybe let them choose a start and and end
    
    //have a menu on where you want to be in the game
    int targetInning = 9;
    if(inning < 9){
        cout << "what inning would you like to sim to : " << endl;
        cin >> targetInning;
    }
    //how will i be able to go to a certain spot in the game, i dont want it to be you can go back
    //should I complete the game and then display it? i should do this
    //need something to store all of the game

};
void Game::printStartingPitchers()
{
    cout << "\nprintStartingPitchers\n" << endl;
};
void Game::print()
{
    cout << "\nprintGame\n" << endl;
};
vector<vector<AtBat>> Game::getGameLog()
{
    return *gameLog;
};
