//
//  TeamFile.h
//  BaseballSimulator
//
//  Created by Ben Schwartz on 12/20/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//

#ifndef TeamFile_h
#define TeamFile_h

#include <stdio.h>
#include <array>
#include "Player.h"
#include <fstream>
#include <vector>
#include "Team.h"
#include "Player.h"
#include "Batter.h"
#include "Pitcher.h"
#include "Game.h"
#include "misc.h"
#include "playerStructs.h"

#include "playerFile.h"
#include <sstream>
#include <filesystem>
#include <unistd.h>


//a team file reads in data from baseballreference.com and makes teams with it
struct TeamFile
{
private:
    vector<Batter> batters;
    vector<Pitcher> pitchers;
public:
    vector<Batter> getBatters(){ return batters; };
    vector<Pitcher> getPitchers(){ return pitchers; };
    playerFile playersFile;
    string teamName;
    int wins, losses;
    string manager;
    TeamFile() {};
    TeamFile(string name1, string mng, int w, int l, vector<string> tb, vector<string> tbr, vector<string> tbp, vector<string> tp, vector<string> tpr, vector<string> tpp, playerFile &pf)
    {
        //have method that does all the string reading
        teamName = name1;
        manager = mng;
        wins = w;
        losses = l;
        playersFile = pf;
        
        //bulk of work is done here
        pair<vector<Player>, vector<Player>> pair = makePlayerLists(teamName, tb, tbr, tbp, tp, tpr, tpp, pf);
        
        vector<Player> batterList = pair.first;
        vector<Player> pitcherList = pair.second;
        
        vector<Player> complete;
        vector<Player> noVis;
        vector<Player> incomplete;
        

        //have methods for checking and adding batters
        
        
        //overloaded operator for this but i dont think its necesary
    //    vector<Player> fullTeamList = batterList + pitcherList;
        
        //going through all players designated as batters and making them
        for(Player p: batterList)
        {
            p.setTeamName(teamName);
            if(p.tuple.isComplete())//if it has all stats
                complete.push_back(p);
            else if(p.tuple.hasInvis())//if it has just visible stats
                noVis.push_back(p);
            else if(p.tuple.isPartial())// if it is missing invisible stats
                incomplete.push_back(p);
            else
                cout << "error : code shouldn't reach here" << endl;
        }

        //now will make the baters
        for(Player pl: complete)
            batters.push_back(makeBatter(pl, true));
        for(Player pl: noVis)
            batters.push_back(makeBatter(pl, false));
        for(Player pl: incomplete)
            pl.~Player();
        
        complete.clear();
        noVis.clear();
        incomplete.clear();
        //make vectors here for pitcher and pitcher batting shit
        vector<Player> battingInvis;//do what i did for batters for pitchers
        
        for(Player &p: pitcherList)
        {
            p.setTeamName(teamName);
            if(!p.tuple.isComplete() || p.tuple.isPartial())
                cout << "ERROR : " << p.getName() << " has incomplete data" << endl;
            if(p.pitcherBattingTuple.ratiosPopulated() ^ p.pitcherBattingTuple.pitchesPopulated())
                cout << "ERROR : " << p.getName() << " has incomplete batting data" << endl;
            else
                pitchers.push_back(makePitcher(p));
        }
        
        //just make sure that the structs know if they are empty
        // know when to add them to batter list based on what stats they have

    };
    Batter makeBatter(Player &p, bool hasVis)// this function will take a player created already with the file-read stats to make batter
    {
        //check to see what i actually do here and do i need that bool parameter
        
        if(hasVis && !p.tuple.teamPopulated())
            cout << "ERROR : player does not have visible stats";//this is ok to happen just keep for now
        //gets the string vectors from the player
        vector<string> teamStats = p.tuple.team;
        vector<string> ratioStats = p.tuple.ratios;
        vector<string> pitchesStats = p.tuple.pitches;
        //need to do these
        p.setPosition(teamStats[1]);
        p.checkName(teamStats[2]);
        p.checkAge(stoi(teamStats[3]));
        p.checkAge(stoi(ratioStats[1]));
        p.checkAge(stoi(pitchesStats[1]));
        // make the batter structs
        batter_visibleStats visStats(teamStats);
        batter_invisibleStats invisStats(ratioStats, pitchesStats);
        //check to see if there were any reading problems and how many stats weren't included
        if(visStats.check() > 0)
            p.complete = false;
        /*else */if(invisStats.check() > 0)
            p.complete = false;
        p.complete = true;
        //ready to make batter
        return Batter(p, visStats, invisStats);
    };
    Pitcher makePitcher(Player &p)
    {        bool hasBatStats = p.pitcherBattingTuple.hasInvis();
       
        vector<string> teamStats = p.tuple.team;
        vector<string> ratioStats = p.tuple.ratios;
        vector<string> pitchesStats = p.tuple.pitches;
        
        p.setPosition(teamStats[1]);
        p.checkName(teamStats[2]);
        p.checkAge(stoi(teamStats[3]));
        
        pitcher_visibleStats visStats(teamStats);
        pitcher_invisibleStats invisStats(ratioStats, pitchesStats);
        
//        if(visStats.check() > 0)
//            p.complete = false;
//        if(visStats.check() > 0)
//            p.complete = false;
//        p.omplete = true;
        
        if(hasBatStats)
        {
            batter_invisibleStats pitBatInvis(p.pitcherBattingTuple.ratios, p.pitcherBattingTuple.pitches);
//            if(pitBatInvis.check() > 0)
//                piper
            return Pitcher(p, visStats, invisStats, pitBatInvis);
        }
        return Pitcher(p, visStats, invisStats);
       // return Pitcher();
    };
    void printBatters()
    {
      for(Batter b: batters)
      {
          b.printInfo();
      }
    };
//    void printPitchersToFile(string path)
//    {
//        ofstream str(path);
//        
//    };
    void printInfo()
    {
        cout << "team : " << teamName << endl;
        cout << "manager : " << manager << endl;
        cout << "record : " << wins << "-" << losses << endl;
        cout << "batters : " << batters.size() << endl;
        cout << "pitchers : " << pitchers.size() << endl << "*\n" << endl;
    };
};
TeamFile makeTeamFile(pair<string,string> pathPairs, playerFile pf)
{
    ifstream str;
    string batPath = pathPairs.first;
    string pitchPath = pathPairs.second;
    str.open(batPath);
    string teamName, manager;
    vector<string> teamBattingStrings, teamBattingRatiosStrings, teamPitchesBattingStrings;
    vector<string> teamPitchingStrings, teamPitchingRatiosStrings, teamPitchingPitchesStrings;
    int wins, losses;
    //temp variables for reading
    string line;
    size_t pos;
    
    //the below code is made to read the text files correctly,
    //so it wont make any sense unless you have the text files pulled up
    
    //this will assign teamName
    while(line.substr(0,4) != "2019")
        getline(str, line);
    pos = line.find("Logo"); // position of extra text so i can get rid of it
    teamName = line.substr(5, pos-6);
    //this will assign the wins/losses
    while(line.substr(0,6) != "Record")
        getline(str, line);
    pos = line.find("-");
    wins = stoi(line.substr(pos-2,2));
    losses = stoi(line.substr(pos+1,2));
    //this will assign the manager
    while(line.substr(0,7) != "Manager")
        getline(str, line);
    pos = line.find("(");
    manager = line.substr(9, pos-10);
    //this will assign teamBatting string
    while(line.find("Rk") == string::npos)
        getline(str, line);
    while(getline(str, line) && line.find("\tP\t") == string::npos)
        if(line.find("Rk") == string::npos)
            teamBattingStrings.push_back(line);// this will populate teamBatting with all of the non pitcher batting stats
    //this will assign teamBattingRatios string
    while(line.find("Team Batting Ratios") == string::npos)
        getline(str, line);
    while(line.substr(0,4) != "Name")
        getline(str, line);
    while(getline(str, line) && line.find("League") == string::npos)
        teamBattingRatiosStrings.push_back(line);
    //this will assign teamPitchesBatting string
    while(line.find("Team Pitches Batting") == string::npos)
        getline(str, line);
    while(line.substr(0,4) != "Name" || line == "Name")
        getline(str, line);
    while(getline(str, line) && line.find("League") == string::npos)
        teamPitchesBattingStrings.push_back(line);
    //now that the batting strings have been initialized, now its time to do pitching
    str.close();
    str.open(pitchPath);
    while(line.substr(0,4) != "2019")
        getline(str, line);
    pos = line.find("Logo");
    if(line.substr(5, pos-6) != teamName)
        cout << "ERROR: non matching team files" << endl;
    //this will assign teamPitching string
    while(line.find("Rk") == string::npos)
        getline(str, line);
    while(getline(str, line) && line.find("Team Totals") == string::npos)
        if(line.find("Rk") == string::npos)
            teamPitchingStrings.push_back(line);
    //this will assign teamPitchingRatios string
    while(line.find("Team Pitching Ratios") == string::npos)
        getline(str, line);
    while(line.substr(0,4) != "Name")
        getline(str, line);
    while(getline(str, line) && line.find("League") == string::npos)
        teamPitchingRatiosStrings.push_back(line);
    //this will assign teamPitchingPitches string
    while(line.find("Team Pitching Pitches") == string::npos)
        getline(str, line);
    while(line.substr(0,4) != "Name" || line == "Name")
        getline(str, line);
    while(getline(str, line) && line.find("League") == string::npos)
        teamPitchingPitchesStrings.push_back(line);
    //now all strings are populated
    str.close();
    //makes the TeamFile
    TeamFile t(teamName, manager, wins, losses, teamBattingStrings, teamBattingRatiosStrings, teamPitchesBattingStrings, teamPitchingStrings, teamPitchingRatiosStrings, teamPitchingPitchesStrings, pf);
    cout << "*\tteam file for " << teamName << " successfully made" << endl;
    //usleep(200000);
    return t;
};
static vector<TeamFile> readAllFiles(string path)
{//makes all teams
    vector<TeamFile> teamFiles;//what will be returned
    playerFile pf = getPlayerFile(path);//playerfile used to make team files
    vector<pair<string,string>> pairs = getTeamPathPairs(path);
    ifstream str;
    
    for(pair<string,string> pair: pairs){
        teamFiles.push_back(makeTeamFile(pair, pf));
        usleep(90000);
    }
    
    return teamFiles;
};
TeamFile makeTeamFile(string path, string team)
{//just makes a team file from user entered team name
    pair<string,string> pair = getTeamPathPair(path, team);
    if(pair.first == "null"){
        cout << "ERROR : team not found" << endl;
        return TeamFile();
    }
    else
        return makeTeamFile(pair, getPlayerFile(path));
};
vector<TeamFile> makeFileFromPrompt(string path)
{
    vector<TeamFile> files;
    vector<pair<string, string>> pairs = getTeamPathPairs(path);
    playerFile pf = getPlayerFile(path);
    
    printTeams(path, pairs);
    //have it ask which teams it wants to create, maybe i could have then enter the team number seperated by commas?
    string userAnswer;
    cout << "\n Enter which team(s) you want to create, separated by commas (Ex. \"2,3,14\") : ";
    cin >> userAnswer;
    cout << endl;

    vector<int> teamsMade = makeTeamIntList(userAnswer);
    
    for(int i: teamsMade)
        files.push_back(makeTeamFile(pairs[i], pf));
    cout << "\nsuccessfully made " << teamsMade.size() << " team files" << endl << endl;
    return files;
};
vector<TeamFile> makeFileFromPrompt(string path, string userAnswer)
{
    vector<TeamFile> files;
    vector<pair<string, string>> pairs = getTeamPathPairs(path);
    playerFile pf = getPlayerFile(path);

    vector<int> teamsMade = makeTeamIntList(userAnswer);

    for(int i: teamsMade)
       files.push_back(makeTeamFile(pairs[i], pf));
    cout << "\nsuccessfully made " << teamsMade.size() << " team files" << endl << endl;
    return files;
};
vector<string> getTeamStringsVec(string path)
{
    vector<string> teamStrings;
    vector<pair<string,string>> pairs = getTeamPathPairs(path);
    for(pair<string,string> pair: pairs)
        teamStrings.push_back(toLower(getTeamNameFromPair(pair, path)));
    return teamStrings;
};
static void makingTeamsAnimation()
{
    cout << "\nMaking teams." << endl;
    usleep(1005000);
    cout << "\nMaking teams.." << endl;
    usleep(1005000);
    cout << "\nMaking teams..." << endl << endl;
    usleep(1005000);
};
//add a method to pick a team that has a vector<TeamFile> parameter
#endif /* teamFile_h */
