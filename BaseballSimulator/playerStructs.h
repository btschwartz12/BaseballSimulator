//
//  playerStructs.h
//  BaseballSimulator
//
//  Created by Ben Schwartz on 1/22/20.
//  Copyright © 2020 Ben Schwartz. All rights reserved.
//

#ifndef structs_h
#define structs_h
//#include <map>


using namespace std;

static double getDouble(vector<string> vec, int index)
{
    string s = vec[index];
    if(s == "")
        s = "-1";
    if(s.find("%") == string::npos)
        return stod(s);
    else
        return stod(s.substr(0, s.length()-1));
};


struct playerMiscInfo
{
    bool exists = false;
    string nationality;
    string height;
    string dateOfBirth;
    int yearStarted; // first year affiliated in MLB
    int age = -1;
    int weight = -1;//jersey number, age, weight
    
    playerMiscInfo() {};
    ~playerMiscInfo() {};
    
    playerMiscInfo(string nat, string ht, string dob, int ys, int ag, int wt) {
        nationality = nat;
        height = ht;
        dateOfBirth = dob;
        yearStarted = ys;
        age = ag;
        weight = wt;
        exists = true;
    }
};
struct playerStatTuple
{//this will be used after when they have been seperated
//    string name;
    vector<string> team, ratios, pitches;
    bool teamPopulated()
    {
        return team.size() > 0;
    }
    bool ratiosPopulated()
    {
        return ratios.size() > 0;
    }
    bool pitchesPopulated()
    {
        return pitches.size() > 0;
    }
    bool isComplete()
    {
        return teamPopulated() && ratiosPopulated() && pitchesPopulated();
    }
    bool hasInvis()
    {
        return ratiosPopulated() && pitchesPopulated();
    }
    bool isPartial()
    {
        int total = teamPopulated() + ratiosPopulated() + pitchesPopulated();
        return total < 3 && total != 0;
    }
};

struct batter_visibleStats
   {
       //so default constructor is cool make them 0?
       // these are the averages that may change with slumps
   public:
       bool exists;
       double avg; // hits / at bats
       double slg; // total bases / at bats
       double obp; // times reached base / plate apps
       int plateApps; // plate appearances
       int atBats;
       int hits;
       int singles;
       int doubles;
       int triples;
       int homeRuns;
       int strikeouts;
       int walks;
       int hbp; // hit by pitches
       int rbi; // runs batted in
       int sb; // stolen bases
       int cs; // caught stealing
       int gp; // games played
       int opsPlus; // from baseball reference, idk if ill use
       
      /* map<int, string> vars
       {
           { 1, "avg" },
           { 2, "slg" },
           { 3, "obp" },
           { 4, "plateApps" },
           { 5, "atBats" },
           { 6, "hits" },
           { 7, "singles" },
           { 8, "doubles" },
           { 9, "triples" },
           { 10, "homeRuns" },
           { 11, "strikeouts" },
           //maybe use this to check which ones are empty
       };*/
       
       //constructors
       batter_visibleStats() {};
       ~batter_visibleStats() {};
       batter_visibleStats(vector<string> teamStats)
       {
            if(teamStats.size() > 0){
                avg = stod(teamStats[17]);
                obp = stod(teamStats[18]);
                slg = stod(teamStats[19]);
                gp = stoi(teamStats[4]);
                plateApps = stoi(teamStats[5]);
                atBats = stoi(teamStats[6]);
                hits = stoi(teamStats[8]);
                doubles = stoi(teamStats[9]);
                triples = stoi(teamStats[10]);
                homeRuns = stoi(teamStats[11]);
                singles = hits - doubles - triples - homeRuns;
                rbi = stoi(teamStats[12]);
                sb = stoi(teamStats[13]);
                cs = stoi(teamStats[14]);
                walks = stoi(teamStats[15]);
                strikeouts = stoi(teamStats[16]);
                opsPlus = stod(teamStats[21]);
                hbp = stoi(teamStats[24]);
                exists = true;
            }
            else
            {
                cout << "ERROR : incorrect vector size" << endl;
                exists = false;
            }
       }
       //other methods
       int check()
       {
           int numEmpty = 0;
           vector<int> vec = {gp, plateApps, atBats, hits, doubles, triples, homeRuns, rbi, sb, cs, walks, strikeouts, opsPlus, hbp};
           for(int d: vec)
           {
               if(d == -1)
                   numEmpty++;
               else if(d < -1000 || d > 10000)
                   cout << "ERROR : data read improperly" << endl;
           }
           return numEmpty;
       };
   };
   struct batter_invisibleStats
   {//have the constructor for this take a string/vector
       //have constructor for batter just have one of these or a mutator method
      
       
       double trueAvg, trueSlg, trueOBP; // what theyre actual stats are; these dont change
       
       //from Team Batting Ratios
       
       double HR_pct; //home runs / plate apps
       double SO_pct; //strikeouts / plate apps
       double BB_pct; //walks / plate apps
       double XBH_pct; // (2B+3B+HR) / plate apps
       double XBH_per_H_pct; //(2B+3B+HR) / total hits
       double SO_per_W; // strikeouts / walks
       double AB_per_SO; // atbats / strikeouts
       double AB_per_HR; // atbats / home runs
       double AB_per_RBI; // atbats / rbis
       double GB_per_FB; // ground balls / fly balls
       double GO_per_AO; // ground outs / fly outs
       double inPlay_pct; // (AB-SO-HR+SF) / plate apps
       double lineDrive_pct; // all line drives (inc. HRs) / balls in play
       double HR_per_FB_pct; // home runs / fly balls
       double IF_per_FB_pct; // fly balls / fly balls
       
       //from Team Pitches Batting
       
       double strikeSeen_pct; // strikes / total pitches
       double L_per_Str_pct; // looking strikes / total strikes
       double SnM_per_Str_pct; // swing & miss strikes / total strikes
       double F_per_Str_pct; // pitches fouled off / total strikes
       double I_per_Str_pct; // balls in play / total strikes
       double S_per_Str_pct; // total pitches swung at (inplay+foul+swing&miss) / total strikes
       double S_per_Pit_pct; // total pitches swung at / total pitches
       double contact_pct; // (foul + inplayStrikes) / (foul + inplay + swingingStrikes)
       double fps_pct; // first pitch swings / total plate appearances
       double count30_pct; // 3-0 counts / plate apps
       double count20_pct; // 2-0 counts / plate apps
       double count31_pct; // 3-1 counts / plate apps
       double lookingK_pct; // looking strikeouts / all strikeouts
       //contructors
       batter_invisibleStats() {};
       ~batter_invisibleStats() {};
       
       //other methods
       int check()
       {
           int numEmpty = 0;
           vector<double> vec = {trueAvg, trueSlg, trueOBP, HR_pct, SO_pct, BB_pct, XBH_pct, XBH_per_H_pct, SO_per_W, AB_per_SO, AB_per_HR, AB_per_RBI, GB_per_FB, GO_per_AO, inPlay_pct, lineDrive_pct, HR_per_FB_pct, IF_per_FB_pct, strikeSeen_pct, L_per_Str_pct, SnM_per_Str_pct, F_per_Str_pct, I_per_Str_pct, S_per_Str_pct, S_per_Pit_pct, contact_pct, fps_pct, count30_pct, count20_pct, count31_pct, lookingK_pct};
           for(double d: vec)
           {
               if(d == -1 )
                   numEmpty++;
               else if(d < -10000 || d > 10000000)
                   cout << "ERROR : data read improperly" << endl;
           }
           return numEmpty;
       }
       batter_invisibleStats(vector<string> ratioStats, vector<string> pitchesStats)
       {
           //if( size
           //from Team Batting Ratios
            HR_pct = getDouble(ratioStats, 3);
            SO_pct = getDouble(ratioStats, 4);
            BB_pct = getDouble(ratioStats, 5);
            XBH_pct = getDouble(ratioStats, 6);
            XBH_per_H_pct = getDouble(ratioStats, 7);
            SO_per_W = getDouble(ratioStats, 8);
            AB_per_SO = getDouble(ratioStats, 9);
            AB_per_HR = getDouble(ratioStats, 10);
            AB_per_RBI = getDouble(ratioStats, 11);
            GB_per_FB = getDouble(ratioStats, 12);
            GO_per_AO = getDouble(ratioStats, 13);
            inPlay_pct = getDouble(ratioStats, 14);
            lineDrive_pct = getDouble(ratioStats, 15);
            HR_per_FB_pct = getDouble(ratioStats, 16);
            IF_per_FB_pct = getDouble(ratioStats, 17);
            //from Team Pitches Batting
            strikeSeen_pct = getDouble(pitchesStats, 6);
            L_per_Str_pct = getDouble(pitchesStats, 7);
            SnM_per_Str_pct = getDouble(pitchesStats, 8);
            F_per_Str_pct = getDouble(pitchesStats, 9);
            I_per_Str_pct = getDouble(pitchesStats, 10);
            S_per_Str_pct = getDouble(pitchesStats, 11);
            S_per_Pit_pct = getDouble(pitchesStats, 13);
            contact_pct = getDouble(pitchesStats, 14);
            fps_pct = getDouble(pitchesStats, 15);
            count30_pct = getDouble(pitchesStats, 16);
            count20_pct = getDouble(pitchesStats, 19);
            count31_pct = getDouble(pitchesStats, 22);
            lookingK_pct = getDouble(pitchesStats, 27);
//           else
//           {
//               cout << "ERROR : incorrect vector size" << endl;
//               exists = false;
//           }
       }
   };
   struct pitcher_visibleStats
   {
  // protected:
       bool exists;
       string position;
       int wins; // should look up how to calc
       int losses;
       double era; // 9 * earned runs / innings pitched
       int gamesPitched; // appeared in a game
       int gamesStarted; // was first pitcher
       int completeGames; // pitched all 9 innings
       int shutouts; // complete game with no runs
       double ip; // innings pitched (.1 is one out, .2 is two outs)
       int hits; // hits given up
       int runs; // runs surrendured
       int er; // earned runs surrendured
       int hr; // home runs given up
       int bb; // walks
       int so; // strikeouts
       int hbp; // hit by pitches
       int bf; // batters faced
       double fip; // fielding independant pitching ((13*HR+3*(HBP+BB)-2*K)/IP)
       double whip; // walks + hits per inning pitched
       double h9; // 9 * hits / innings pitched
       double hr9; // 9 * home runs / innings pitched
       double bb9; // 9 * walks / innings pitched
       double K_per_BB; // strikeouts / walks
       //constructors
       pitcher_visibleStats() {};
       ~pitcher_visibleStats() {};
       pitcher_visibleStats(vector<string> teamStats)
       {
           if(teamStats.size() == 34)
           {
               exists = true;
               wins = stoi(teamStats[4]);
               losses = stoi(teamStats[5]);
               era = stod(teamStats[7]);
               gamesPitched = stoi(teamStats[8]);
               gamesStarted = stoi(teamStats[9]);
               completeGames = stoi(teamStats[11]);
               shutouts = stoi(teamStats[12]);
               ip = stod(teamStats[14]);
               hits = stoi(teamStats[15]);
               runs = stoi(teamStats[16]);
               er = stoi(teamStats[17]);
               hr = stoi(teamStats[18]);
               bb = stoi(teamStats[19]);
               so = stoi(teamStats[21]);
               hbp = stoi(teamStats[22]);
               bf = stoi(teamStats[25]);
               fip = stod(teamStats[27]);
               whip = stod(teamStats[28]);
               h9 = stod(teamStats[29]);
               hr9 = stod(teamStats[30]);
               bb9 = stod(teamStats[31]);
               K_per_BB = stod(teamStats[33]);
           }
           else
           {
               cout << "ERROR : incorrect vector size" << endl;
               exists = false;
           }
       }
       int check()
       {
           int numEmpty = 0;
           vector<double> vec = {era, ip, fip, whip, h9, hr9, bb9, K_per_BB};
           for(double d: vec)
           {
               if(d == -1)
                   numEmpty++;
               else if(d < -1000 || d > 10000)
                   cout << "ERROR : data read improperly" << endl;
           }
           return numEmpty;
       };
   };
    
   struct pitcher_invisibleStats
   {
       bool exists;
       double trueWHIP, trueERA, trueK9;
       
       // from Team Pitching Ratios
       double platoon_pct; // pct of time pitcher faces same hand batter
       double hr_pct; // home runs / plate apps
       double so_pct; // strikeouts / plate apps
       double bb_pct; // walks / plate apps
       double xbh_pct; // extra base hits / plate apps
       double XperH_pct; // (2B + 3B + HR) / H
       double GB_per_FB; // ground balls / fly balls
       double GO_per_AO; // ground outs / fly outs
       double inPlay_pct; // (AB-SO-HR+SF) / plate apps
       double lineDrive_pct; // all line drives (inc. HRs) / balls in play
       double HR_per_FB_pct; // home runs / fly balls
       double IF_per_FB_pct; // fly balls / fly balls
       double gidp_pct; // when runner on first with <2 outs, how many times double play
       
       // from Team Pitching Pitches
       
       double p_per_pa; // tot pitches / plate apps
       double strikeSeen_pct; // strikes / total pitches
       double L_per_Str_pct; // looking strikes / total strikes
       double SnM_per_Str_pct; // swing & miss strikes / total strikes
       double F_per_Str_pct; // pitches fouled off / total strikes
       double I_per_Str_pct; // balls in play / total strikes
       double S_per_Str_pct; // total pitches swung at (inplay+foul+swing&miss) / total strikes
       double S_per_Pit_pct; // total pitches swung at / total pitches
       double contact_pct; // (foul + inplayStrikes) / (foul + inplay + swingingStrikes)
       double fps_pct; // first pitch strikes / total plate appearances
       double count30_pct; // 3-0 counts / plate apps
       double count02_pct; // 0-2 counts / plate apps
       double lookingK_pct; // looking strikeouts / all strikeouts
       
       double threePitchKs_pct;
       double fourPitchBBs_pct;
       
       //constructors
       pitcher_invisibleStats() {};
       ~pitcher_invisibleStats() {};
       
       pitcher_invisibleStats(vector<string> ratioStats, vector<string> pitchesStats)
       {
           if(ratioStats.size() == 20 && pitchesStats.size() == 32)
           {
               exists = true;
               // from Team Pitching Ratios
               platoon_pct = getDouble(ratioStats, 3);
               hr_pct = getDouble(ratioStats, 4);
               so_pct = getDouble(ratioStats, 5);
               bb_pct = getDouble(ratioStats, 6);
               xbh_pct = getDouble(ratioStats, 8);
               XperH_pct = getDouble(ratioStats, 9);
               GB_per_FB = getDouble(ratioStats, 10);
               GO_per_AO = getDouble(ratioStats, 11);
               inPlay_pct = getDouble(ratioStats, 12);
               lineDrive_pct = getDouble(ratioStats, 13);
               HR_per_FB_pct = getDouble(ratioStats, 14);
               IF_per_FB_pct = getDouble(ratioStats, 15);
               gidp_pct = getDouble(ratioStats, 18);
               
               // from Team Pitching Pitches
               
               p_per_pa = getDouble(pitchesStats, 5);
               strikeSeen_pct = getDouble(pitchesStats, 7);
               L_per_Str_pct = getDouble(pitchesStats, 8);
               SnM_per_Str_pct = getDouble(pitchesStats, 9);
               F_per_Str_pct = getDouble(pitchesStats, 10);
               I_per_Str_pct = getDouble(pitchesStats, 11);
               S_per_Str_pct = getDouble(pitchesStats, 12);
               S_per_Pit_pct = getDouble(pitchesStats, 14);
               contact_pct = getDouble(pitchesStats, 15);
               fps_pct = getDouble(pitchesStats, 16);
               count30_pct = getDouble(pitchesStats, 17);
               count02_pct = getDouble(pitchesStats, 20);
               lookingK_pct = getDouble(pitchesStats, 26);
               
               //threePitchKs_pct = getDouble(pitchesStats, <#int index#>);
              // fourPitchBBs_pct = getDouble(pitchesStats, <#int index#>);
           }
           else
           {
               cout << "ERROR : incorrect vector size" << endl;
               exists = false;
           }
       }

   };
#endif /* structs_h */
