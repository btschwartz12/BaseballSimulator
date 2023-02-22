//
//  playerFile.h
//  BaseballSimulator
//
//  Created by Ben Schwartz on 12/20/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//
// basically the purpose of this is to read info from all the 40-man rosters of the teams that will be used
// this cant be done in the other reading file because this information is located on a different webpage
// all this will do is make one big vector of type Player that stores all players on the 40-man rosters.
// some of these players will not be used in game, and some players read in from the team file will not be on this list.
// this is just to get useful and nice information about players that I cant list elsewhere
// i will prob use weight for calculations and number for games but this is mostly for aesthetic

#ifndef playerFile_h
#define playerFile_h



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
#include <sstream>
#include <filesystem>

#include <map>
#include "misc.h"
//#include <bits/stdc++.h>

namespace fs = std::__fs::filesystem;

struct playerFile
{
    vector<Player> players;
    playerFile() {}; //so that it will build TeamFile
    playerFile(vector<pair<string, vector<Player>>> pairs)
    {
        for(pair<string, vector<Player>> pair: pairs)
        {
            for(Player &p: pair.second)
            {
                p.setTeamName(pair.first);
                players.push_back(p);
            }
        }
    };
    Player getPlayer(string name)
    {
        Player p(name);
        for(Player pl: players)
            if(pl.getName() == name)
                p = pl;
        return p;
    }
    Player getPlayer(string name, string teamName)
    {
        Player p(name);
        Player *ppt = &p;
        for(Player &pl: players)
            if(pl.getName() == name && pl.getTeamName() == teamName)
                ppt = &pl;
        return *ppt;
    }
    //other functions?
};
vector<string> getUseableFiles(string path)
{//this just makes a string vector of all the files there are
    vector<string> files;
    for (const auto & entry : fs::directory_iterator(path))
    {
        string s = entry.path().string();
        size_t found = s.find(".DS_Store");
        if(found == string::npos)
            files.push_back(s);
    }
    return files;
};
vector<pair<string,string>> getTeamPathPairs(string path)
{
    vector<string> files = getUseableFiles(path);
    vector<pair<string,string>> pairs;
    
    for(int i = 0; i < files.size(); i++)
    {//get rid of player string
        string s = files[i];
        if(s.find("player") != string::npos){
            files.erase(files.begin()+i);
            break;
        }
    }
    sort(files.begin(), files.end()); // this will sort in alphebetical order
    for(int i = 0; i < files.size() - 1; i+=2)
    {
        string first = files[i];
        string second = files[i+1];
        if(first.find("batting") == string::npos || second.find("pitching") == string::npos || first.substr(0,3) != second.substr(0,3))
            cout << "ERROR : insufficient files";
        pairs.push_back(make_pair(first,second));
    }
    return pairs;
};
pair<string,string> getTeamPathPair(string path, string team_name)
{//this will take a user entered team name and get the pair for it
    vector<pair<string,string>> pairs =  getTeamPathPairs(path);//all the pairs
    string teamName = getTeamNameFromString(team_name);//puts team name into a readable form
    
    for(pair<string, string> pair: pairs)
        if(getTeamNameFromPair(pair, path) == teamName)
            return pair;//loops through until team is found
    cout << "ERROR : " << team_name << " not found" << endl;
    return make_pair("null", "null");
};
string getPlayerDataPath(string path)
{
    vector<string> files = getUseableFiles(path);
    string loc;//location of player file
    for(int i = 0; i < files.size(); i++)
    {
        string s = files[i];
        if(s.find("player") != string::npos){
            loc = s;
            break;
        }
    }
    return loc;
};
Player makePlayerFromString(string s)
{
    vector<string> info;
    stringstream stream(s);
    //makes an vector of info separated by tabs
    while (stream.good()) {
        string substr;
        getline(stream, substr, '\t');
        if(substr == "")
            substr = "-1";
        info.push_back(substr);
    }
    //will get all data to make a player
    int num = stoi(info[1]);
    string name = info[2];
    string nationality = info[3].substr(info[3].length()-2);
    string position = info[4];
    int age = stoi(info[7]);
    char batsO = info[8][0];
    char throwsO = info[9][0];
    string height = info[10].substr(0, info[10].length()-1);
    int weight = stoi(info[11]);
    string dob = info[12];
    int yearOne = stoi(info[13]);
    //this will construct a player with all info
    return Player(num, name, position, batsO, throwsO, playerMiscInfo(nationality, height, dob, yearOne, age, weight));
}
static playerFile getPlayerFile(string path)
{//this just reads a plsyer file and gets players with team name and makes playerfile out of it
    string fileName = getPlayerDataPath(path);
    ifstream str;
    str.open(fileName);
    vector<pair<string, vector<Player>>> pairs;
    string line;
    while(!str.eof())
    {
        while(line[0] != '@')
            getline(str, line);
        pair<string, vector<Player>> pair;
        pair.first = line.substr(1);//name
        while(getline(str, line) && line[0] != '@')
            pair.second.push_back(makePlayerFromString(line));// adds a player for each on the team
        pairs.push_back(pair);//i literallt forgot this line
    }
    str.close();
    playerFile pFile(pairs);
    //cout << "player file successfully made" << endl;
    return pFile;
};
pair<string, char> getPlayerPair(string &s)
{ // gets name and orientation from baseball refs syntax
    char o;
    char lastChar = s[s.length()-1];
    if(lastChar == '*'){
        o = 'L';
        s.pop_back();
    }//thanks baseball reference
    else if(lastChar == '#'){
        o = 'S';
        s.pop_back();
    }
    else
        o = 'R';
    return make_pair(s, o);
};
pair<vector<Player>, vector<Player>> makePlayerLists(string teamName, vector<string> teamBattingStrings, vector<string> teamBattingRatiosStrings, vector<string> teamPitchesBattingStrings, vector<string> teamPitchingStrings, vector<string> teamPitchingRatiosStrings, vector<string> teamPitchingPitchesStrings, playerFile &playersFile)
{
    //i am making these so that I can populate each player's stat vectors without duplicating
    vector<Player> batterList;
    vector<Player> pitcherList;
    
    //have to do this one first bc some batters are pitchers
    for(string s: teamBattingStrings){
        vector<string> stats;
        stringstream stream(s);
        while (stream.good()) {
            string substr;
            getline(stream, substr, '\t');
            if(substr == "")
                substr = "-1.0";
            stats.push_back(substr);
        }
        pair<string, char> pair = getPlayerPair(stats[2]);
        string name = pair.first;
        char batsO = pair.second;
        Player p = playersFile.getPlayer(pair.first, teamName);
        p.setBatsO(batsO);
        p.tuple.team = stats;
        batterList.push_back(p);
    }
    //other pitcher strings will be read first because more pitchers can be batters than vice versa
    for(string s: teamPitchingStrings){
        vector<string> stats;
        stringstream stream(s);
        //this will separate the string into a vector, deliminated by tabs
        while (stream.good()) {
        string substr;
        getline(stream, substr, '\t');
        if(substr == "")
            substr = "-1.0";
        stats.push_back(substr);
        }
        //this will take the name and orientation and put it in a pair
        pair<string, char> pair = getPlayerPair(stats[2]);
        string name = pair.first;
        char throwsO = pair.second;
        //if it is a batter
        int index = getPlayerIndex(name, batterList);
        if(index == -1)
        {// i only want to make it a pitcher if he isnt already a batter
            Player p = playersFile.getPlayer(name, teamName);
            p.setThrowsO(throwsO);
            p.tuple.team = stats;
            pitcherList.push_back(p);
        }
    }
    for(string s: teamPitchingRatiosStrings){
        vector<string> stats;
        stringstream stream(s);
        while (stream.good()) {
           string substr;
           getline(stream, substr, '\t');
            if(substr == "")
                substr = "-1.0";
           stats.push_back(substr);
        }
        pair<string, char> pair = getPlayerPair(stats[0]);
        string name = pair.first;
        char throwsO = pair.second;
        //this will check to see if the player has had data read already)
        if(getPlayerIndex(name, batterList) != -1)
            continue;//if it is a batter, will go to next string
        int index = getPlayerIndex(name, pitcherList);
        if(index == -1)
        { //not found amoung previously made pitchers
           Player p = playersFile.getPlayer(name, teamName);
           p.tuple.ratios = stats;
           p.setThrowsO(throwsO);
           pitcherList.push_back(p);
        }
        else
        { // if it has been read already
           Player &p = pitcherList[index];
           p.setThrowsO(throwsO);
           p.tuple.ratios = stats;
        }
    }
    for(string s: teamPitchingPitchesStrings){
        vector<string> stats;
        stringstream stream(s);
        while (stream.good()) {
           string substr;
           getline(stream, substr, '\t');
            if(substr == "")
                substr = "-1.0";
           stats.push_back(substr);
        }
        pair<string, char> pair = getPlayerPair(stats[0]);
        string name = pair.first;
        char throwsO = pair.second;
        if(getPlayerIndex(name, batterList) != -1)
            continue;//if it is a batter, will go to next string
        int index = getPlayerIndex(name, pitcherList);
        if(index == -1)
        {//not found amoung previously made pitchers
           Player p = playersFile.getPlayer(name, teamName);
           p.tuple.pitches = stats;
           p.setThrowsO(throwsO);
           pitcherList.push_back(p);
        }
        else
        {
           Player &p = pitcherList[index];
           p.setThrowsO(throwsO);
           p.tuple.pitches = stats;
        }
    }
    //now batter players will start being created
    for(string s: teamBattingRatiosStrings){
        vector<string> stats;
        stringstream stream(s);
        while (stream.good()) {
            string substr;
            getline(stream, substr, '\t');
            if(substr == "")
                substr = "-1.0";
            stats.push_back(substr);
        }
        pair<string, char> pair = getPlayerPair(stats[0]);
        string name = pair.first;
        char batsO = pair.second;
        int batIndex = getPlayerIndex(name, batterList);
        int pitchIndex = getPlayerIndex(name, pitcherList);
        if(batIndex == -1)
        {// if the current player is a pitcher or not read yet
            if(pitchIndex == -1)
            {// not pitcher and not read yet
                Player p = playersFile.getPlayer(name, teamName);
                p.tuple.ratios = stats;
                p.setBatsO(batsO);
                batterList.push_back(p);
            }
            else
            {// is a pitcher
                Player &p = pitcherList[pitchIndex];
                p.setBatsO(batsO);
                p.pitcherBattingTuple.ratios = stats;
            }
        }
        else
        {// if it is a batter
            Player &p = batterList[batIndex];
            p.setBatsO(batsO);
            p.tuple.ratios = stats;
        }
    }
    for(string s: teamPitchesBattingStrings){
        vector<string> stats;
        stringstream stream(s);
        while (stream.good()) {
            string substr;
            getline(stream, substr, '\t');
            if(substr == "")
                substr = "-1.0";
            stats.push_back(substr);
        }
        pair<string, char> pair = getPlayerPair(stats[0]);
        string name = pair.first;
        char batsO = pair.second;
        int batIndex = getPlayerIndex(name, batterList);
        int pitchIndex = getPlayerIndex(name, pitcherList);
        if(batIndex == -1)
        {// if the batter is a pitcher or not read yet
            if(pitchIndex == -1)
            {// not pitcher and not read yet
                Player p = playersFile.getPlayer(name, teamName);
                p.tuple.pitches = stats;
                p.setBatsO(batsO);
                batterList.push_back(p);
            }
            else
            {// is a pitcher
                Player &p = pitcherList[pitchIndex];
                p.setBatsO(batsO);
                p.pitcherBattingTuple.pitches = stats;
            }
        }
        else
        {// if it is a batter
            Player &p = batterList[batIndex];
            p.setBatsO(batsO);
            p.tuple.pitches = stats;
        }
    }
    return make_pair(batterList, pitcherList);
};
void printTeams(string path, vector<pair<string, string>> pairs)
{
    int count = 0;
    cout << "\nMLB team(s) with data : " << endl << endl;
    for(pair<string, string> pair: pairs)
        cout << "*\t" << ++count << ". " << getTeamNameFromPair(pair, path) << endl;
};
vector<int> makeTeamIntList(string userAnswer)
{//will take a user input and generate the indexes of teams to be made
    vector<string> teamsToMake;
    stringstream stream(userAnswer);
    while (stream.good()) {
      string substr;
      getline(stream, substr, ',');
      substr.erase(remove(substr.begin(), substr.end(), ' '), substr.end());
      teamsToMake.push_back(substr);
    }
    for(string s: teamsToMake)
        for(char c: s)//nice loop to check
            if(c != 44 && c != 45 && c != 32 && (c < 48 || c > 57))
                cout << "ERROR : incorrect syntax entered" << endl;
    
    vector<int> teamsMade;
    for(string s: teamsToMake)
    {
        size_t found = s.find("-");
        if(found != string::npos)
        {//if its a range
            int lower = stoi(s.substr(0, found));
            int higher = stoi(s.substr(found+1));
            lower = min(lower, higher);
            higher = max(lower, higher);
            for(int i = lower; i <= higher; i++)
                if(isIntInVec(i, teamsMade, 30))
                    teamsMade.push_back(i-1);
        }
        else
        {//if its just a single num
            int i = stoi(s);
            if(isIntInVec(i, teamsMade, 30))
                teamsMade.push_back(i-1);
        }
    }
    return teamsMade;
};


#endif /* playerFile_h */


//fricken jean carlos mejia fucking me up
