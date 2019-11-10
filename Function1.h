#ifndef _FUNCTION1_H_
#define _FUNCTION1_H_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Function3.h"

#define v0 70.0

class LiverMan;
class Frame;

class Stuff
{
    friend class Stair;
    friend class Frame;
    friend stuffType meetTool(int x, int &y, int bot, Frame* a, Frame* b,bool exe);
private:
    int width,height;
    int x,y;
    SDL_Surface * stuffSurface;
    void loadStuff();
    void setType();
public:
    stuffType type;
    Stuff();
    ~Stuff();
    void showStuff(int frameHeight);
    void setHeight();
    void setWidth();
};

class Monster
{
    friend class Frame;
    friend monsterType meetMonster(int x, int &y, int bot, Frame* a, Frame* b,bool exe);
private:
    int width,height;
    int x,y;
    SDL_Surface * monsterSurface;
    void loadMonster();
    void setType();
    const int MONSTER_WIDTH,MONSTER_HEIGHT;
public:
    monsterType type;
    Monster();
    ~Monster();
    void showMonster(int frameHeight);
};

class Stair
{
    friend class Frame;
    friend bool onStage(int x, int &y, int bot, Frame* a, Frame* b);
    friend stuffType meetTool(int x, int &y, int bot, Frame* a, Frame* b,bool exe);
private:
    int x,y;
    int width,height;
    SDL_Surface * stairSurface;
    void loadStair();
    void setType();
    const int STAIR_WIDTH,STAIR_HEIGHT;
public:

    stairType type;
    Stair();
    ~Stair();
    void showStair(int frameHeight);
    Stuff* StuffOnStair;
    bool stuffOnStair();
    bool stuffExist;
    void deleteStuffOnStair();
};

class Frame
{
    friend bool onStage(int x, int &y, int bot, Frame* a, Frame* b);
    friend stuffType meetTool(int x, int &y, int bot, Frame* a, Frame* b,bool exe);
    friend monsterType meetMonster(int x, int &y, int bot, Frame* a, Frame* b,bool exe);
private:
    const int FRAME_HEIGHT,FRAME_WIDTH;
    int stairNumber;
    bool monsterExist;
    int frame_y;
    Stair * StairInFrame[4];
    Monster * MonsterInFrame;
    void setStairs(bool setOne=false);
    void setMonster();
    void adjustStair();//avoid stairs overlapping
public:
    Frame();
    //~Frame();
    void showFrame();
    void setFrame_y(int tmp);
    void changeContent();
    void deleteStairInFrame();
    void deleteMonsterInFrame();
    void changeTiming1(int&);
    void changeTiming2();
};


#endif // _FUNCTION1_H_
