#ifndef _FUNCTION2_H_
#define _FUNCTION2_H_

#include <sstream>
#include <fstream>
#include <algorithm>
#include "Function3.h"

class Frame;
class Bullet;

class _Score
{
private:
    int sc;

public:
    _Score();
    void saveScore(std::string);
    int getScore();
    void print(int);
};

class LiverMan
{
    friend class Frame;
private:
    SDL_Rect fLoc;
    SDL_Surface* healthy;
    SDL_Surface* hurt;
    SDL_Surface* inShoes;
    SDL_Surface* inHat;
    SDL_Surface* inRocket;
    SDL_Surface* inMask;
    stuffType current;
    Bullet* bullet;
    double vy;
    int grav,y;
public:
    int savedTool[3];
    int bot;
    _Score Score;
    std::string name;
    LiverMan();
    ~LiverMan();
    void loadHealthy(void);
    void loadHurt(void);
    bool moveLoc(int,Frame*,Frame*);
    void ifBounce(Frame*,Frame*);
    void ifRollScreen(void);
    void drop(void);
    void fly(void);
    void newBullet(int);
    void deleteBulletifOut(Frame*, Frame*);
    LiverMan& operator+=(stuffType);
};

class BackGround
{
private:
    SDL_Surface* bg;
public:
    BackGround(Uint32 color);
    BackGround(const char* file);
    //void loadShort(int);
    //void loadLong(int);
    void load(int,int=0);
    void loadFixed(void);
};

class Button
{
private:
    SDL_Rect fLoc;
    SDL_Surface* button;
    SDL_Color str_color;
    SDL_Color bg_color;
    int type;
public:
    Button(const char*,int,int,int);
    bool click(const SDL_MouseButtonEvent&);
    void display(void);
};

class Bullet
{
private:
    SDL_Rect bLoc;
    int vx;
    const static int vy;
public:
    Bullet(int,const SDL_Rect&);
    void moveLoc();
    void show();
    bool ifOut(int,Frame*,Frame*);
};



#endif // _FUNCTION2_H_
