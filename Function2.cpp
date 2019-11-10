#include "Function3.h"

extern SDL_Renderer* renderer;
extern SDL_Texture* texture;
int highScore = 0;
const int high = 370;
const char* _font = "obj/impact.ttf";

LiverMan::LiverMan():bullet(NULL),name("NONAME")
{
    fLoc = {215,50,50,50};
    vy = v0;
    grav = 1;
    y = 0;
    bot = 0;
    for(int i=0;i<3;i++)
        savedTool[i] = 0;
    healthy = IMG_Load("image/liver_man.png");
    hurt = IMG_Load("image/liver_man_hurt.png");
    inShoes = IMG_Load("image/liver_man_jumping_shoes.png");
    inHat = IMG_Load("image/liver_man_flying_hat.png");
    inRocket = IMG_Load("image/rocket_liverman.png");
    inMask = IMG_Load("image/liver_man_protecting_mask.png");
    current = NoTool;
}

LiverMan::~LiverMan()
{
    std::cout<<"Score:  "<<Score.getScore()<<std::endl;
    Score.saveScore(name);
    std::cout<<"Record: "<<highScore<<std::endl;
    SDL_FreeSurface(healthy);
    SDL_FreeSurface(hurt);
    SDL_FreeSurface(inShoes);
    SDL_FreeSurface(inHat);
    SDL_FreeSurface(inRocket);
    SDL_FreeSurface(inMask);
    std::cout<<"Liver Man reloaded."<<std::endl;
}

void LiverMan::loadHealthy(void)
{
    SDL_Surface* currentSurface;
    SDL_Rect cLoc = fLoc;
    switch(current)
    {
        case jumping_shoes:
            currentSurface = inShoes;
            cLoc.h = 60; break;
        case flying_hat:
            currentSurface = inHat;
            cLoc.h = 60;
            cLoc.y -= 10; break;
        case rocket:
            currentSurface = inRocket; break;
        case protecting_mask:
            currentSurface = inMask;
            cLoc.h = 80; cLoc.w = 80;
            cLoc.y -= 15; cLoc.x -= 15; break;
        default:
            currentSurface = healthy; break;
    }
    texture = SDL_CreateTextureFromSurface(renderer, currentSurface);
    if (texture == NULL) return;
    SDL_RenderCopy(renderer, texture, NULL, &cLoc);
    SDL_DestroyTexture(texture);
    if(bullet != NULL)
    {
        bullet->show();
    }
}

void LiverMan::loadHurt(void)
{
    texture = SDL_CreateTextureFromSurface(renderer, hurt);
    if (texture == NULL) return;
    SDL_RenderCopy(renderer, texture, NULL, &fLoc);
    SDL_DestroyTexture(texture);
}

bool LiverMan::moveLoc(int vx,Frame* a, Frame* b)
{
    vy-= grav;
    fLoc.x += vx;
    y += (vy/10);
    if(fLoc.x < 0)
        fLoc.x += SCREEN_WIDTH;
    else if(fLoc.x > SCREEN_WIDTH)
        fLoc.x -= SCREEN_WIDTH;
    fLoc.y = SCREEN_HEIGHT-y+bot-fLoc.h;
    if(bullet != NULL)
    {
        bullet->moveLoc();
        deleteBulletifOut(a,b);
    }
    if(y < bot)
    {
        std::cout<<"Dropped down."<<std::endl;
        return false;
    }
    else
    {
        monsterType res = meetMonster(fLoc.x,y,bot,a,b,0);
        if(res == NoMonster)
            return true;
        else if(res == black_hole)
        {
            fLoc.y = SCREEN_HEIGHT-fLoc.h;
            vy = 0 - v0;
            std::cout<<"Jumped into a black hole."<<std::endl;
            return false;
        }
        else if(current == protecting_mask||current == rocket)
            return true;
        else if(vy > 0)
        {
            vy = 0 - v0;
            std::cout<<"Monster type "<<(int)res<<" met."<<std::endl;
            return false;
        }
        else
            return true;
    }
}

void LiverMan::drop(void)
{
    y += (vy/10);
    bot= y;
}

void LiverMan::ifBounce(Frame* a, Frame* b)
{
    stuffType res1 = meetTool(fLoc.x,y,bot,a,b);
    monsterType res2 = meetMonster(fLoc.x,y,bot,a,b,1);
    static int shoesCount = 0;
    static int maskCount = 0;
    if(current == protecting_mask)
    {
        maskCount++;
        if(maskCount == 600)
            current = NoTool;
    }
    else maskCount = 0;
    if(vy < 0)
    {
        if(current == 1||current == 2)
            current = NoTool;
        if(res1 == spring)
        {
            vy = 1.75*v0;
            meetTool(fLoc.x,y,bot,a,b,1);
            std::cout<<"Jumped on a spring."<<std::endl;
        }
        else if(res1 == jumping_bed)
        {
            vy = 2.5*v0;
            std::cout<<"Jumped on a jumping bed."<<std::endl;
        }
        else if(onStage(fLoc.x, y, bot, a, b))
        {
            if(current == 0)
            {
                vy = 1.75*v0;
                shoesCount++;
                std::cout<<"Jumped with jumping shoes"<<std::endl;
                if(shoesCount == 5)
                {
                    shoesCount = 0;
                    current = NoTool;
                }
            }
            else
            {
                vy = v0;
                shoesCount = 0;
            }
        }
        if(res2 != black_hole&&res2 != NoMonster)
        {
            vy = v0;
            std::cout<<"Jumped on a monster type "<<(int)res2<<"."<<std::endl;
        }
    }
    if(res1 < 3)
    {
        savedTool[res1]++;
        std::cout<<"Tool type "<<(int)res1<<" saved."<<std::endl;
    }
    else if(res1 == protecting_mask)
    {
        (*this) += protecting_mask;
        std::cout<<"A Protecting mask worn."<<std::endl;
        maskCount = 0;
    }
}

void LiverMan::ifRollScreen(void)
{
    if(y>=(bot+high))
        bot=y-high;
}

void LiverMan::fly(void)
{
    if(current == 1) vy = 4*v0;
    else if(current == 2) vy = 6*v0;
}

LiverMan& LiverMan::operator+=(stuffType newType)
{
    if(newType == NoTool)
    {
        current = newType;
        return (*this);
    }
    else if(current == 1||current == 2)
    {
        return (*this);
    }
    else if(newType < 3&&!savedTool[newType])
    {
        return (*this);
    }
    else
    {
        current = newType;
        if(newType < 3)
        {
            savedTool[newType] --;
            std::cout<<"Tool type "<<(int)newType<<" used."<<std::endl;
            if(newType > 0)
                fly();
        }
        return (*this);
    }
}

void LiverMan::newBullet(int vx)
{
    if(bullet == NULL)
    {
        bullet = new Bullet(vx,fLoc);
    }
}

void LiverMan::deleteBulletifOut(Frame* a, Frame* b)
{
    if(bullet->ifOut(bot,a,b))
    {
        delete bullet;
        bullet = NULL;
    }
}




BackGround::BackGround(Uint32 color)
{
    bg = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT/4, 32, 0, 0, 0, 0);
    SDL_FillRect(bg,NULL,color);
}

BackGround::BackGround(const char* file)
{
    bg = SDL_LoadBMP(file);
    if(bg == NULL)
    {
        SDL_RWops* rwop = SDL_RWFromFile(file,"rb");
        bg = IMG_Load_RW(rwop,1);
    }
}

void BackGround::load(int bottom, int mov)
{
    SDL_Rect a = {0,bottom%SCREEN_HEIGHT-SCREEN_HEIGHT+mov,SCREEN_WIDTH,SCREEN_HEIGHT};
    texture = SDL_CreateTextureFromSurface(renderer, bg);
    if (texture == NULL) return;
    SDL_RenderCopy(renderer, texture, NULL, &a);
    SDL_DestroyTexture(texture);
    a = {0,bottom%SCREEN_HEIGHT+mov,SCREEN_WIDTH,SCREEN_HEIGHT};
    texture = SDL_CreateTextureFromSurface(renderer, bg);
    if (texture == NULL) return;
    SDL_RenderCopy(renderer, texture, NULL, &a);
    SDL_DestroyTexture(texture);
}



_Score::_Score()
{

    sc = 0;
}

void _Score::saveScore(std::string _name)
{
    std::fstream file1;
    file1.open("obj/ranking.txt");
    int score[11];
    std::string name[11];
    for(int i=0;i<10;i++)
    {
        file1>>score[i]>>name[i];
    }
    file1>>highScore;
    file1.close();
    score[10] = sc;
    name[10] = _name;
    bubble_sort(score,name,11);
    file1.open("obj/ranking.txt",std::ios::trunc|std::ios::out);
    for(int i=0;i<10;i++)
    {
        file1<<score[i]<<" "<<name[i]<<'\n';
    }
    highScore = (score[0]<highScore) ? highScore : score[0];
    file1<<highScore<<'\n';
    file1.close();
}

void _Score::print(int bottom)
{
    sc = bottom;
    showString("SCORE:",_font,40,0x0000FF,20,20);
    std::stringstream score;
    score.str("");
    score<<bottom;
    showString(score.str().c_str(),_font,40,0x0000FF,140,20);
}

int _Score::getScore()
{
    return sc;
}



Button::Button(const char* _string,int x,int y,int type)
{
    if(type == 0){
        int font_size = 38;
        str_color = {0xff,0xff,0xff,0xff};
        int len = (double)strlen(_string)/2*font_size;
        fLoc={x,y,len,font_size};
        TTF_Font* font = TTF_OpenFont(_font, font_size);
        button = TTF_RenderText_Solid(font, _string, str_color);
        TTF_CloseFont(font);
    }
    else{
        const char* file = _string;
        SDL_Surface* tmpImage = SDL_LoadBMP(file);
        if(tmpImage == NULL)
        {
            SDL_RWops* rwop = SDL_RWFromFile(file,"rb");
            tmpImage = IMG_Load_RW(rwop,1);
        }
        fLoc={x,y,40,40};
        button = SDL_CreateRGBSurface(0, 40, 40, 32, 0, 0, 0, 0);
        SDL_BlitSurface(tmpImage,NULL,button,NULL);
        SDL_FreeSurface(tmpImage);
    }
}

bool Button::click(const SDL_MouseButtonEvent& e)
{
    if(e.x>(fLoc.x)&&((e.x)<(fLoc.x+fLoc.w))&&(e.y)>(fLoc.y)&&((e.y)<(fLoc.y+fLoc.h)))
        return true;
    else return false;
}

void Button::display(void)
{
    texture = SDL_CreateTextureFromSurface(renderer, button);
    if (texture == NULL) return;
    SDL_RenderCopy(renderer, texture, NULL, &fLoc);
    SDL_DestroyTexture(texture);
}



const int Bullet::vy = 15;

Bullet::Bullet(int v,const SDL_Rect& fLoc)
{
    vx = v;
    bLoc.x = fLoc.x + 20;
    bLoc.y = fLoc.y;
    bLoc.w = 10;
    bLoc.h = 10;
}

void Bullet::moveLoc()
{
    bLoc.x += vx;
    bLoc.y -= vy;
}

void Bullet::show()
{
    showImage("image/bullet.png",NULL,&bLoc);
}

bool Bullet::ifOut(int bot,Frame* a,Frame* b)
{
    int& xx = bLoc.x;
    int& yy = bLoc.y;
    int y = SCREEN_HEIGHT + bot - yy;
    if(xx>=SCREEN_WIDTH||xx<=0||yy<=0)
    {
        return true;
    }
    else if(meetMonster(xx,y,bot,a,b,1) != NoMonster)
    {
        return true;
    }
    else
    {
        return false;
    }
}
