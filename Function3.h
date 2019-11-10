#ifndef _FUNCTION3_H_
#define _FUNCTION3_H_

#include "Initialization.hpp"

extern const char* _font;

enum stuffType
{
    jumping_bed=5,
    rocket=2,
    spring=4,
    flying_hat=1,
    protecting_mask=3,
    jumping_shoes=0,
    NoTool=6,
    used_spring=7
};

enum stairType
{
    stair=0,
    broken_stair,
    stair_timing1,
    stair_timing2,
};

enum monsterType
{
    black_hole=0,
    mon_cplusplus,
    mon_quartusii,
    mon_xor,
    NoMonster
};

extern int Dif;
class Frame;
class LiverMan;

void changeTiming(Frame* a, Frame* b, int bot);

void Generate(int Count,Frame *a,Frame *b);
void rollFrame(int &j,int &bottom,Frame* a,Frame* b);

bool onStage(int x, int &y, int bot, Frame* a, Frame* b);
stuffType meetTool(int x, int &y, int bot, Frame* a, Frame* b,bool exe=0);
monsterType meetMonster(int x, int &y, int bot, Frame* a, Frame* b,bool exe=0);

void buildToolKey(SDL_Surface**);
void ShowToolKey(SDL_Surface**,const LiverMan&);

void adjustDifficulty(int bot);

void bubble_sort(int arr[],std::string name[], int len);

void showRanking();

#include "Function1.h"
#include "Function2.h"
#include <cmath>

#endif // _FUNCTION3_H_
