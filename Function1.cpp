#include "Function3.h"

Stuff::Stuff(){
    setType();
    setWidth();
    setHeight();
    x=0;
    y=0;
    loadStuff();
}

Stuff::~Stuff()
{
    SDL_FreeSurface(stuffSurface);
}

void Stuff::setType(){
    int index=rand()%11;
    switch(index){
        case 0:
        case 6:
            type =jumping_bed;
            break;
        case 1:
            type= rocket;
            break;
        case 2:
        case 7:
            type= spring;
            break;
        case 3:
        case 8:
            type= flying_hat;
            break;
        case 4:
        case 9:
            type= protecting_mask;
            break;
        case 5:
        case 10:
            type= jumping_shoes;

    }
}

void Stuff::setHeight()
{
    if(type == jumping_bed ) height=20;
    else if(type == rocket ) height=50;
    else if(type == spring ) height=20;
    else if(type == flying_hat ) height=25;
    else if(type == protecting_mask ) height=50;
    else if(type == jumping_shoes ) height=25;
    else if(type == used_spring) height=40;
}

void Stuff::setWidth()
{
    if(type == jumping_bed ) width=50;
    else if(type == rocket ) width=50;
    else if(type == spring ) width=30;
    else if(type == flying_hat ) width=50;
    else if(type == protecting_mask ) width=50;
    else if(type == jumping_shoes ) width=25;
    else if(type == used_spring) width=50;
}

void Stuff::loadStuff()
{
    if(type == jumping_bed ) stuffSurface = IMG_Load("image/jumping_bed.png");
    else if(type == rocket ) stuffSurface = IMG_Load("image/rocket.png");
    else if(type == spring ) stuffSurface = IMG_Load("image/spring_tight.png");
    else if(type == flying_hat ) stuffSurface = IMG_Load("image/flying_hat.png");
    else if(type == protecting_mask ) stuffSurface = IMG_Load("image/protecting_mask.png");
    else if(type == jumping_shoes ) stuffSurface = IMG_Load("image/jumping_shoes.png");
    else if(type == used_spring) stuffSurface = IMG_Load("image/spring_loose.png");
    if(stuffSurface==NULL) std::cout<<"Load stuff image failed"<<std::endl;
}

void Stuff::showStuff(int framePosition)
{
    SDL_Rect tmpRect = {x,y+framePosition,width,height};
    texture = SDL_CreateTextureFromSurface(renderer, stuffSurface);
    if (texture == NULL) return;
    SDL_RenderCopy(renderer, texture, NULL, &tmpRect);
    SDL_DestroyTexture(texture);
}


Stair::Stair() :STAIR_HEIGHT(15),STAIR_WIDTH(80)
{
    setType();
    width=STAIR_WIDTH;
    height=STAIR_HEIGHT;
    x=rand()%(SCREEN_WIDTH-width);
    y=rand()%(SCREEN_HEIGHT/8-height);
    loadStair();
    stuffExist = stuffOnStair();
}

Stair::~Stair()
{
    SDL_FreeSurface(stairSurface);
}

void Stair::setType()
{
    int index=rand()%(15-Dif);//usual stair has 70% probability
    switch(index)
    {
        case 1:
        case 2:
        case 3:
            type= stair_timing1;
            break;
        default:
            type =stair;
            break;
    }
}

void Stair::loadStair()
{
    if(type == stair ) stairSurface = IMG_Load("image/stair.png");
    else if(type == broken_stair ) stairSurface = IMG_Load("image/broken_stair.png");
    else if(type == stair_timing1 ) stairSurface = IMG_Load("image/stair_timing1.png");
    else if(type == stair_timing2 ) stairSurface = IMG_Load("image/stair_timing2.png");
    if(stairSurface==NULL) std::cout<<"Load stair image failed"<<std::endl;
}

void Stair::showStair(int framePosition)
{
    SDL_Rect tmpRect = {x,y+framePosition,width,height};
    texture = SDL_CreateTextureFromSurface(renderer, stairSurface);
    if (texture == NULL) return;
    SDL_RenderCopy(renderer, texture, NULL, &tmpRect);
    if(stuffExist==true) StuffOnStair->showStuff(framePosition);
    SDL_DestroyTexture(texture);
}

bool Stair::stuffOnStair()// has 1/8 probability to have a stuff on stair
{
    if(type!=stair) return false;
    else if(rand()%(8+Dif)!=0)
    {
        StuffOnStair=NULL;
        return false;
    }
    else
    {
        StuffOnStair = new Stuff;
        StuffOnStair->x = x+rand()%(STAIR_WIDTH-StuffOnStair->width);
        if(StuffOnStair->height>y) y=StuffOnStair->height;
        StuffOnStair->y = y-StuffOnStair->height;
        return true;
    }
}

void Stair::deleteStuffOnStair()
{
    if(stuffExist==true) delete StuffOnStair;
    stuffExist = false;
}


Monster::Monster() : MONSTER_HEIGHT(50),MONSTER_WIDTH(50)
{
    //srand(time(0));
    setType();
    width=MONSTER_WIDTH;
    height=MONSTER_HEIGHT;
    x=rand()%(SCREEN_WIDTH-width);
    y=rand()%(SCREEN_HEIGHT/8-height);
    loadMonster();
}

Monster::~Monster()
{
    SDL_FreeSurface(monsterSurface);
}

void Monster::setType()
{
    int index=rand()%10;//usual stair has 70% probability
    switch(index)
    {
        case 0:
        case 1:
        case 2:
            type= mon_cplusplus;
            break;
        case 3:
        case 4:
        case 5:
            type= mon_quartusii;
            break;
        case 6:
        case 7:
        case 8:
            type= mon_xor;
            break;
        case 9:
            type= black_hole;
            break;
    }
}

void Monster::loadMonster()
{
    if(type == mon_cplusplus ) monsterSurface = IMG_Load("image/monster_cplusplus.png");
    else if(type == mon_quartusii ) monsterSurface = IMG_Load("image/monster_quartusii.png");
    else if(type == mon_xor ) monsterSurface = IMG_Load("image/monster_xor.png");
    else if(type == black_hole) monsterSurface = IMG_Load("image/black_hole.png");
    if(monsterSurface==NULL) std::cout<<"Load monster image failed"<<std::endl;
}

void Monster::showMonster(int framePosition)
{
    SDL_Rect tmpRect = {x,y+framePosition,width,height};
    texture = SDL_CreateTextureFromSurface(renderer, monsterSurface);
    if (texture == NULL) return;
    SDL_RenderCopy(renderer, texture, NULL, &tmpRect);
    SDL_DestroyTexture(texture);
}


Frame::Frame() :FRAME_HEIGHT(SCREEN_HEIGHT/8),FRAME_WIDTH(SCREEN_WIDTH)
{
    setStairs();
    setMonster();
    adjustStair();
    setFrame_y(0);
}

void Frame::setStairs(bool setOne)
{
    if(setOne==false)
    {
        int index=rand()%100;//index: probability of stairNumber
        if(index<50+((double)Dif*3.7)) stairNumber=1;
        else if(index<75+((double)Dif*3.7)) stairNumber=2;
        else if(index<95+((double)Dif*3.7)) stairNumber=3;
        else stairNumber=4;
    }
    else//only one stair
    {
        stairNumber=1;
    }
    for(int i=0;i<stairNumber;i++) StairInFrame[i]=new Stair;
}

void Frame::setMonster()
{
    if(Dif&&rand()%(22-2*Dif)==0)// 1/20 probability to have a monster
    {
        MonsterInFrame=new Monster;
        monsterExist=true;
    }
    else
    {
        MonsterInFrame=NULL;
        monsterExist=false;
    }
}

void Frame::adjustStair()//adjust stair and monster
{
    SDL_Rect stairRect[stairNumber];
    for(int i=0;i<stairNumber;i++)
    {
        if(StairInFrame[i]->stuffExist==false)
        {
            stairRect[i].x=StairInFrame[i]->x;
            stairRect[i].y=StairInFrame[i]->y;
            stairRect[i].w=StairInFrame[i]->width;
            stairRect[i].h=StairInFrame[i]->height;
        }
        else
        {
            stairRect[i].x=StairInFrame[i]->x;
            stairRect[i].y=StairInFrame[i]->y-StairInFrame[i]->StuffOnStair->y;
            stairRect[i].w=StairInFrame[i]->width;
            stairRect[i].h=StairInFrame[i]->height+StairInFrame[i]->StuffOnStair->height;
        }
    }
    bool checkOverlap=false;
    SDL_Rect tmpRect;
    int area_tmpRect;
    for(int i=0;i<stairNumber;i++)
    {
        int area_stairRect=stairRect[i].w * stairRect[i].h;
        for(int j=0;j<i;j++)
        {
            if(SDL_IntersectRect(&stairRect[i],&stairRect[j],&tmpRect)==SDL_TRUE)
            {
                area_tmpRect = tmpRect.w * tmpRect.h;
                if(area_tmpRect > (1/4)*area_stairRect)//area overlaps more than 1/4
                {
                    checkOverlap=true;
                }
            }
        }
        if(monsterExist==true)
        {
            SDL_Rect monsterRect;
            monsterRect.x = MonsterInFrame->x;
            monsterRect.y = MonsterInFrame->y;
            monsterRect.w = MonsterInFrame->width;
            monsterRect.h = MonsterInFrame->height;
            if(SDL_IntersectRect(&stairRect[i],&monsterRect,&tmpRect)==SDL_TRUE)
            {
                area_tmpRect = tmpRect.w * tmpRect.h;
                if(area_tmpRect > (1/4)*area_stairRect)//area overlaps more than 1/4
                {
                    checkOverlap=true;
                }
            }
        }
    }
    if( checkOverlap==true )//Can be modified
    {

        deleteStairInFrame();
        if(monsterExist==true)deleteMonsterInFrame();
        setStairs(1);
    }
}

void Frame::showFrame()
{
    for(int i=0;i<stairNumber;i++) StairInFrame[i]->showStair(frame_y);
    if(monsterExist==true) MonsterInFrame->showMonster(frame_y);
}

void Frame::setFrame_y(int tmp)
{
    frame_y=tmp;
}

void Frame::changeContent()
{
    deleteStairInFrame();
    if(monsterExist==true) deleteMonsterInFrame();
    setStairs();
    setMonster();
    adjustStair();
}

void Frame::deleteStairInFrame()
{

    for(int i=0;i<stairNumber;i++)
    {
        StairInFrame[i]->deleteStuffOnStair();
        delete StairInFrame[i];
    }
}

void Frame::deleteMonsterInFrame()
{
    delete MonsterInFrame;
    monsterExist=false;
}

void Frame::changeTiming1(int& cnt)
{
    for(int i=0;i<stairNumber;i++)
    {
        if(StairInFrame[i]->type == stair_timing1)
        {
            StairInFrame[i]->type = stair_timing2;
            StairInFrame[i]->loadStair();
        }
    }
    cnt++;
}

void Frame::changeTiming2()
{
    for(int i=0;i<stairNumber;i++)
    {
        if(StairInFrame[i]->type == stair_timing2)
        {
                StairInFrame[i]->type = broken_stair;
                StairInFrame[i]->loadStair();


        }
    }
}
