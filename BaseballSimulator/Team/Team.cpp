//
//  Team.cpp
//  BaseballSimulator
//
//  Created by Ben Schwartz on 11/26/19.
//  Copyright © 2019 Ben Schwartz. All rights reserved.
//
#include "Team.h"
#include "Batter.h"
#include "Pitcher.h"
#include "Game.h"

#include <vector>

using namespace std;

Team::Team(string name1, vector<Batter> bs, vector<Pitcher> ps)
{
    name = name1;
    

    

    
    //need to be added to list before checked
    for(Batter &b: bs)
    {
        batters.push_back(b);
        players.push_back(b);
    }
    for(Pitcher &p: ps)
    {
        pitchers.push_back(p);
        players.push_back(p);
    }
    //now we start checking positions
    posMap["DH"] = 0;
    posMap["C"] = 0;
    posMap["1B"] = 0;
    posMap["2B"] = 0;
    posMap["3B"] = 0;
    posMap["SS"] = 0;
    posMap["LF"] = 0;
    posMap["CF"] = 0;
    posMap["RF"] = 0;
    posMap["SP"] = 0;
    posMap["RP"] = 0;
    posMap["CL"] = 0;
    map<string,int>::iterator it;//create map iterator
    for(Player &p: players)
    {
        string position = p.getPosition();
        //iterates through and adds 1 to the value of the certain position key
        it = posMap.find(position);
        if (it == posMap.end())
            cout << "ERROR : incorrect position of player";
        else
            posMap[position]++;
        it = posMap.begin();//resets to beginning
    }
    //this will iterate the map and heck the value of every key to make sure its not 0
    for (it = posMap.begin(); it != posMap.end(); ++it)
        if (it->second == 0)
            cout << "ERROR : insufficient " << it->first << "s." << endl;
    //at this point the team shoulf be valid
    for(int i = 0; i < ps.size(); i++)
    {//this correctly sets the team
        players.push_back(ps[i]);
        players[i].setTeam(*this);
    }
   //CHECK BOTTOM OF FILE

    
    srand(static_cast<int>(time(0)));
    for(int i = 0; i < players.size(); i++)
    {//goes through and assigns numbers, makes sure no two plaers have the same one
        int n = rand() % 100 + 1;
        players[i].setNumber(n);
       
//        for(int j = 0; j < i; j++)
//        {
//            bool good = false;
//            while(!good){
//                if(players[i].getNumber == players[j].getNumber())
//
//            }
//        }
    }
};
void Team::addGame(Game g)
{
    gameList->push_back(g);
};
void Team::printTeam()
{
    for(Player p : players)
        cout << p.getPosition() << " = " << p.getName() << endl;
};
void Team::printTeamStats()
{

};



    //i want this to work, but i might have to use above code
    
//    for(Player &p: ps)//adds players to private list, does this need to be a reference?
//    {
//        Player *pp = &p;
//        players.push_back(*pp);
//        p.setTeam(*this);//this makes a different team constrcuctor
//    }
    
    //https://www.codementor.io/mentorship/new?request_type=one-on-one
    
//    for(int i = 0; i < 11; i++)//adds players to private list, does this need to be a reference?
//    {
//        Player * p = &ps[i];
//        //Player *pp = &p;
//        players.push_back(*p);
//
//        //the pointers team is correct but the one in array is still null
//
//        p->setTeam(*this);//this makes a different team constrcuctor
//    }
