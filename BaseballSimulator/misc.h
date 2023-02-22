//
//  misc.h
//  BaseballSimulator
//
//  Created by Ben Schwartz on 12/30/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//

#ifndef misc_h
#define misc_h

#include <string>
#include <vector>
#include <map>
#include "Player.h"



using namespace std;

static int get_month_index( string name );
int getPlayerIndex(string name, vector<Player> ps);
string getTeamNameFromPair(pair<string, string> pair, string path);
string toLower(string s);
vector<string> getSystemTeams();
vector<string> getTeamNameFromString(vector<string> userTeams);
string getTeamNameFromString(string s);
bool isIntInVec(int n, vector<int>);
bool isIntInVec(int n, vector<int>, int limit);
vector<Player> operator +(vector<Player> vec1, vector<Player> vec2);
#endif /* misc_h */
