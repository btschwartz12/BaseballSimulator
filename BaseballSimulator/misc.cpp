//
//  misc.cpp
//  BaseballSimulator
//
//  Created by Ben Schwartz on 1/28/20.
//  Copyright © 2020 Ben Schwartz. All rights reserved.
//

#ifndef misc_cpp
#define misc_cpp

#include <string>
#include <vector>
#include <map>
#include "Player.h"
#include "misc.h"
#include <sstream>



using namespace std;

static int get_month_index( string name )
{
    map<string, int> months
    {
        { "Jan", 1 },
        { "Feb", 2 },
        { "Mar", 3 },
        { "Apr", 4 },
        { "May", 5 },
        { "Jun", 6 },
        { "Jul", 7 },
        { "Aug", 8 },
        { "Sep", 9 },
        { "Oct", 10 },
        { "Nov", 11 },
        { "Dec", 12 }
    };

    const auto iter = months.find( name );

    if( iter != months.cend() )
        return iter->second;
    return -1;
};
int getPlayerIndex(string name, vector<Player> ps)
{//just for finding a player in a list
    for(int i = 0; i < ps.size(); i++)
        if(ps[i].getName() == name)
            return i;
    return -1;
}
string getTeamNameFromPair(pair<string, string> pair, string path)
{// just gets the team name from the file path
    int pathLength = (int) path.size();
    string bat = pair.first, pit = pair.second;
    bat = bat.substr(pathLength+1);
    size_t index = bat.find("_batting");
    if(index == string::npos)
        cout << "ERROR : incorrect files" << endl;
    bat = bat.substr(0,index);
    //find da team name from pitching file
    pit = pit.substr(pathLength+1);
    index = pit.find("_pitching");
    if(index == string::npos)
        cout << "ERROR : incorrect files" << endl;
    pit = pit.substr(0,index);
    //check to make sure team names are the same
    if(bat != pit)
        cout << "ERROR : pair contains different teams" << endl;
    string s = bat;
    //this will put it into the good team form
    for(char &c: s)
    {// makes all lower case and replaces _ with space
        if(c >= 65 && c <= 90)
            c = tolower(c);
        else if(c == '_')
            c = ' ';
        else if(c < 97 || c > 122)
            cout << "ERROR" << endl;
    }
    //makes capital letters
    index = s.find(' ');
    if(index != string::npos)
        s[index+1] = toupper(s[index+1]);
    index = s.find(' ', index + 1);
    if(index != string::npos)
        s[index+1] = toupper(s[index+1]);
    s[0] = toupper(s[0]);
    //now we have teamname
    return s;
};
string toLower(string s)
{
    for(char &c: s)
        c = tolower(c);
    return s;
};
vector<string> getSystemTeams()
{
    return {"Arizona", "Atlanta", "Baltimore", "Boston", "Chicago A", "Chicago N", "Cincinnati", "Cleveland", "Colorodo", "Detroit", "Houston", "Kansas City", "Los Angeles A", "Los Angeles N", "Miami", "Milwaukee", "Minnesota", "New York A", "New York N", "Oakland", "Philadelphia", "Pittsburgh", "San Diego", "San Francisco", "Seattle", "St Louis", "Tampa Bay", "Texas", "Toronto", "Washington"};
};
vector<string> getTeamNameFromString(vector<string> userTeams)
{
    vector<string> systemTeams = getSystemTeams();
    vector<string> results;
    for(string s: userTeams)
    {
        string fullName = toLower(s);
        vector<string> vec;
        stringstream stream(fullName);
        while (stream.good()) {
            string substr;
            getline(stream, substr, ' ');
            vec.push_back(substr);
        }
        if(fullName.find("chicago") != string::npos)
        {
            if(fullName.find(" n", fullName.length()-2) != string::npos || fullName.find("cubs") != string::npos)
                results.push_back("Chicago N");
            else if(fullName.find(" a", fullName.length()-2) != string::npos || fullName.find("sox") != string::npos)
                results.push_back("Chicago A");
            else
                cout << "ERROR : incorrect team name entered" << endl;
        }
        else if(fullName.find("los") != string::npos || fullName.find("la ") != string::npos)
        {
            if(fullName.find(" n", fullName.length()-2) != string::npos || fullName.find("dodgers") != string::npos)
                results.push_back("Los Angeles N");
            else if(fullName.find(" a", fullName.length()-2) != string::npos || fullName.find("angels") != string::npos)
                results.push_back("Los Angeles A");
            else
                cout << "ERROR : incorrect team name entered" << endl;
        }
        else if(fullName.find("york") != string::npos || fullName.find("ny") != string::npos)
        {
            if(fullName.find(" n", fullName.length()-2) != string::npos || fullName.find("mets") != string::npos)
                results.push_back("New York N");
            else if(fullName.find(" a", fullName.length()-2) != string::npos || fullName.find("yankees") != string::npos)
                results.push_back("New York A");
            else
                cout << "ERROR : incorrect team name entered" << endl;
        }
        else
        {  // must do team name too?
            for(string s: systemTeams)
            {
                if(fullName.find(toLower(s)) != string::npos)
                    results.push_back(s);
            }
        }
        if(results.size() != userTeams.size())
            cout << "ERROR : some teams not found";
    }
    return results;
};
string getTeamNameFromString(string s)
{
    vector<string> systemTeams = getSystemTeams();
    string result;
    string fullName = toLower(s);
    vector<string> vec;
    stringstream stream(fullName);
    while (stream.good()) {
        string substr;
        getline(stream, substr, ' ');
        vec.push_back(substr);
    }
        if(fullName.find("chicago") != string::npos)
        {
            if(fullName.find(" n", fullName.length()-2) != string::npos || fullName.find("cubs") != string::npos)
                return "Chicago N";
            else if(fullName.find(" a", fullName.length()-2) != string::npos || fullName.find("sox") != string::npos)
                return "Chicago A";
            else
                cout << "ERROR : incorrect team name entered" << endl;
        }
        else if(fullName.find("los") != string::npos || fullName.find("la ") != string::npos)
        {
            if(fullName.find(" n", fullName.length()-2) != string::npos || fullName.find("dodgers") != string::npos)
                return "Los Angeles N";
            else if(fullName.find(" a", fullName.length()-2) != string::npos || fullName.find("angels") != string::npos)
                return "Los Angeles A";
            else
                cout << "ERROR : incorrect team name entered" << endl;
        }
        else if(fullName.find("york") != string::npos || fullName.find("ny") != string::npos)
        {
            if(fullName.find(" n", fullName.length()-2) != string::npos || fullName.find("mets") != string::npos)
                return "New York N";
            else if(fullName.find(" a", fullName.length()-2) != string::npos || fullName.find("yankees") != string::npos)
                return "New York A";
            else
                cout << "ERROR : incorrect team name entered" << endl;
        }
        else
        {  // must do team name too?
            for(string s: systemTeams)
            {
                if(fullName.find(toLower(s)) != string::npos)
                    return s;
            }
        }
    cout << "ERROR : some teams not found";
    return NULL;
};
bool isIntInVec(int n, vector<int> vec)
{
    vector<int>::iterator it = find(vec.begin(), vec.end(), n);;
    return !(it == vec.end());
};
bool isIntInVec(int n, vector<int> vec, int limit)
{
    vector<int>::iterator it = find(vec.begin(), vec.end(), n);
    return (n <= limit) && !(it == vec.end());
};
vector<Player> operator +(vector<Player> vec1, vector<Player> vec2)
{
    vector<Player> full;
    for(Player &p: vec1)
        full.push_back(p);
    for(Player &p: vec2)
        full.push_back(p);
    return full;
};
#endif /* misc_h */
