#include "Function3.h"

int Dif = 0; //Difficulty.

void changeTiming(Frame* a, Frame* b, int bot)
{
    int j = bot / (SCREEN_HEIGHT/8) ;
    static int count[16] = {-100,-100,-100,-100,
                            0,0,0,0,
                            0,0,0,0,
                            0,0,0,0};
    int changeTime = 150;
    for(int i=0;i<5;i++)
    {
        if((j+i)%16 < 8)
        {
            a[(j+i)%16].changeTiming1(count[(j+i)%16]);
            if(count[(j+i)%16] == changeTime)
            {
                a[(j+i)%16].changeTiming2();
                count[(j+i)%16] = 0;
            }


        }
        else
        {
            b[(j+i)%16-8].changeTiming1(count[(j+i)%16]);
            if(count[(j+i)%16] == changeTime)
            {
                b[(j+i)%16-8].changeTiming2();
                count[(j+i)%16] = 0;
            }

        }
    }
}

void Generate(int Count,Frame *a,Frame *b)
{
    int position=SCREEN_HEIGHT;
    if(Count%2!=0)
    {
        for(int i=0;i<8;i++)
        {
            position-=SCREEN_HEIGHT/8;
            a[i].changeContent();
            a[i].setFrame_y(position);
        }
    }
    else
    {
        for(int i=0;i<8;i++)
        {
            position-=SCREEN_HEIGHT/8;
            b[i].changeContent();
            b[i].setFrame_y(position);
        }
    }
}

void rollFrame(int &j,int &bottom,Frame* a,Frame* b)
{
    if(j%2 == 0)
    {
        for(int i=0;i<8;i++)
        {
            a[i].setFrame_y(SCREEN_HEIGHT + bottom%SCREEN_HEIGHT - SCREEN_HEIGHT/8*(i+1));
            b[i].setFrame_y( bottom%SCREEN_HEIGHT - SCREEN_HEIGHT/8*(i+1));
            a[i].showFrame();
            b[i].showFrame();
        }
    }
    else
    {
        for(int i=0;i<8;i++)
        {
            b[i].setFrame_y(SCREEN_HEIGHT + bottom%SCREEN_HEIGHT - SCREEN_HEIGHT/8*(i+1));
            a[i].setFrame_y( bottom%SCREEN_HEIGHT - SCREEN_HEIGHT/8*(i+1));
            a[i].showFrame();
            b[i].showFrame();
        }
    }
}

bool onStage(int x, int &y, int bot, Frame* a, Frame* b)
{
    int cnt = y / (SCREEN_HEIGHT/8) ;
    int yn = SCREEN_HEIGHT - y + bot;
    if(cnt%16 < 8)
    {
        for(int i=0;i<a[cnt%16].stairNumber;i++)
        {
            //std::cout<<"yes"<<std::endl;
            int &xx = a[cnt%16].StairInFrame[i]->x;
            int &yy = a[cnt%16].StairInFrame[i]->y;
            int &xw = a[cnt%16].StairInFrame[i]->width;
            int &fy = a[cnt%16].frame_y;
            if(x+50>=xx&&x<=xx+xw&&yn>=fy+yy&&yn<=fy+yy+10)
            {
                if(a[cnt%16].StairInFrame[i]->type == broken_stair)
                    return false;
                y = SCREEN_HEIGHT + bot - (fy+yy);
                return true;
            }
        }
    }
    else
    {
        for(int i=0;i<b[cnt%16-8].stairNumber;i++)
        {
            int &xx = b[cnt%16-8].StairInFrame[i]->x;
            int &yy = b[cnt%16-8].StairInFrame[i]->y;
            int &xw = b[cnt%16-8].StairInFrame[i]->width;
            int &fy = b[cnt%16-8].frame_y;
            if(x+50>=xx&&x<=xx+xw&&yn>=fy+yy&&yn<=fy+yy+10)
            {
                if(b[cnt%16-8].StairInFrame[i]->type == broken_stair)
                    return false;
                y = SCREEN_HEIGHT + bot - (fy+yy);
                return true;
            }
        }
    }
    return false;
}

stuffType meetTool(int x, int &y, int bot, Frame* a, Frame* b,bool exe)
{
    int cnt = y / (SCREEN_HEIGHT/8) ;
    int yn = SCREEN_HEIGHT - y + bot;
    if(cnt%16 < 8)
    {
        for(int i=0;i<a[cnt%16].stairNumber;i++)
        {
            if(a[cnt%16].StairInFrame[i]->stuffExist==true)
            {
                //std::cout<<"yes"<<std::endl;
                int &xx = a[cnt%16].StairInFrame[i]->StuffOnStair->x;
                int &yy = a[cnt%16].StairInFrame[i]->StuffOnStair->y;
                int &xw = a[cnt%16].StairInFrame[i]->StuffOnStair->width;
                int &fy = a[cnt%16].frame_y;
                int &xh = a[cnt%16].StairInFrame[i]->StuffOnStair->height;
                if(x+50>=xx&&x<=xx+xw&&yn>=fy+yy&&yn-50<=fy+yy+(xh))
                {
                    //y = SCREEN_HEIGHT + (SCREEN_HEIGHT*cnt/8) - (fy+yy);
                    stuffType typ = a[cnt%16].StairInFrame[i]->StuffOnStair->type;
                    if(typ < 4) a[cnt%16].StairInFrame[i]->deleteStuffOnStair();
                    else if(exe)
                    {
                        a[cnt%16].StairInFrame[i]->StuffOnStair->type = used_spring;
                        a[cnt%16].StairInFrame[i]->StuffOnStair->loadStuff();
                    }
                    return typ;
                }
            }
        }
    }
    else
    {
        for(int i=0;i<b[cnt%16-8].stairNumber;i++)
        {
            if(b[cnt%16-8].StairInFrame[i]->stuffExist==true)
            {
                //std::cout<<"yes"<<std::endl;
                int &xx = b[cnt%16-8].StairInFrame[i]->StuffOnStair->x;
                int &yy = b[cnt%16-8].StairInFrame[i]->StuffOnStair->y;
                int &xw = b[cnt%16-8].StairInFrame[i]->StuffOnStair->width;
                int &fy = b[cnt%16-8].frame_y;
                int &xh = b[cnt%16-8].StairInFrame[i]->StuffOnStair->height;
                if(x+50>=xx&&x<=xx+xw&&yn>=fy+yy&&yn-50<=fy+yy+xh)
                {
                    //y = SCREEN_HEIGHT + (SCREEN_HEIGHT*cnt/8) - (fy+yy);
                    stuffType typ = b[cnt%16-8].StairInFrame[i]->StuffOnStair->type;
                    if(typ < 4) b[cnt%16-8].StairInFrame[i]->deleteStuffOnStair();
                    else if(exe)
                    {
                        b[cnt%16-8].StairInFrame[i]->StuffOnStair->type = used_spring;
                        b[cnt%16-8].StairInFrame[i]->StuffOnStair->loadStuff();
                    }
                    return typ;
                }
            }
        }
    }
    return NoTool;
}

monsterType meetMonster(int x, int &y, int bot, Frame* a, Frame* b,bool exe)
{
    int cnt = y / (SCREEN_HEIGHT/8) ;
    int yn = SCREEN_HEIGHT - y + bot;
    if(cnt%16 < 8)
    {
        if(a[cnt%16].monsterExist==true)
        {
            int &xx = a[cnt%16].MonsterInFrame->x;
            int &yy = a[cnt%16].MonsterInFrame->y;
            int &xw = a[cnt%16].MonsterInFrame->width;
            int &fy = a[cnt%16].frame_y;
            int &xh = a[cnt%16].MonsterInFrame->height;
            if(x+50>=xx&&x<=xx+xw&&yn>=fy+yy&&yn-50<=fy+yy+xh)
            {
                //y = SCREEN_HEIGHT + (SCREEN_HEIGHT*cnt/8) - (fy+yy);
                monsterType typ = a[cnt%16].MonsterInFrame->type;
                if(exe&&typ)
                    a[cnt%16].deleteMonsterInFrame();
                return typ;
            }
        }
    }
    else
    {
        if(b[cnt%16-8].monsterExist==true)
        {
            int &xx = b[cnt%16-8].MonsterInFrame->x;
            int &yy = b[cnt%16-8].MonsterInFrame->y;
            int &xw = b[cnt%16-8].MonsterInFrame->width;
            int &fy = b[cnt%16-8].frame_y;
            int &xh = b[cnt%16-8].MonsterInFrame->height;
            if(x+50>=xx&&x<=xx+xw&&yn>=fy+yy&&yn-50<=fy+yy+xh)
            {
                //y = SCREEN_HEIGHT + (SCREEN_HEIGHT*cnt/8) - (fy+yy);
                monsterType typ = b[cnt%16-8].MonsterInFrame->type;
                if(exe&&typ)
                    b[cnt%16-8].deleteMonsterInFrame();
                return typ;
            }
        }
    }
    return NoMonster;
}

void buildToolKey(SDL_Surface** toolKey)
{
    SDL_Rect word_dst = {10,2};
    SDL_Rect img_dst = {40,0};
    toolKey[0] = SDL_CreateRGBSurface(0,100,50,32,0,0,0,0);
    SDL_FillRect(toolKey[0],NULL,0xFFFF00);
    SDL_Color color = {0,0,255,255};
    TTF_Font* font = TTF_OpenFont(_font, 40);
    SDL_Surface* word = TTF_RenderText_Solid(font,"A",color);
    SDL_Surface* img = IMG_Load("image/jumping_shoes.png");
    SDL_BlitSurface(word,NULL,toolKey[0],&word_dst);
    SDL_BlitSurface(img,NULL,toolKey[0],&img_dst);
    SDL_FreeSurface(word);
    SDL_FreeSurface(img);
    toolKey[1] = SDL_CreateRGBSurface(0,100,50,32,0,0,0,0);
    SDL_FillRect(toolKey[1],NULL,0xFFFF00);
    word = TTF_RenderText_Solid(font,"S",color);
    img = IMG_Load("image/flying_hat.png");
    SDL_BlitSurface(word,NULL,toolKey[1],&word_dst);
    SDL_BlitSurface(img,NULL,toolKey[1],&img_dst);
    SDL_FreeSurface(word);
    SDL_FreeSurface(img);
    toolKey[2] = SDL_CreateRGBSurface(0,100,50,32,0,0,0,0);
    SDL_FillRect(toolKey[2],NULL,0xFFFF00);
    word = TTF_RenderText_Solid(font,"D",color);
    img = IMG_Load("image/rocket.png");
    SDL_BlitSurface(word,NULL,toolKey[2],&word_dst);
    SDL_BlitSurface(img,NULL,toolKey[2],&img_dst);
    SDL_FreeSurface(word);
    SDL_FreeSurface(img);
}

void ShowToolKey(SDL_Surface** toolKey, const LiverMan& lm)
{
    for(int i=0;i<3;i++)
    {
        if(lm.savedTool[i])
        {
            SDL_Rect dstrect = {20+i*80,65,80,40};
            texture = SDL_CreateTextureFromSurface(renderer, toolKey[i]);
            if (texture == NULL) return;
            SDL_RenderCopy(renderer, texture, NULL, &dstrect);
            SDL_DestroyTexture(texture);
        }
    }
}

void adjustDifficulty(int bot)
{
    double tmp = log(bot)/log(5);
    int tmp2 = Dif;
    if(tmp>=10)
        Dif = 10;
    else if(tmp<=0)
    	Dif = 0;
    else
        Dif = (int)tmp;
    if(Dif != tmp2)
        std::cout<<"New difficulty: "<<Dif<<std::endl;
}

void bubble_sort(int arr[],std::string name[], int len) {
	int i, j;
	for (i = 0; i < len - 1; i++)
		for (j = 0; j < len - 1 - i; j++)
			if (arr[j] < arr[j + 1])
            {
				std::swap(arr[j], arr[j + 1]);
				std::swap(name[j], name[j + 1]);
            }
}

void showRanking()
{
    std::fstream file1;
    file1.open("obj/ranking.txt");
    int score[10];
    std::stringstream scorestr[10];
    std::string name[10];
    for(int i=0;i<10;i++)
    {
        file1>>score[i]>>name[i];
        scorestr[i]<<score[i];
    }
    file1.close();
    for(int i=0;i<10;i++)
    {
        showString(scorestr[i].str().c_str(),_font,30,0xFF,50,145+(35*i));
        showString(name[i].c_str(),_font,30,0xFF,150,145+(35*i));
    }
}
