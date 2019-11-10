#include "Function3.h"
#include "Function5.hpp"
#include "Function4.hpp"

int main(int argc, char* argv[]){

    if(!openWindow("EE JUMP!","image/logo.png")) return 1;

    BackGround boli("image/background_boli.png");
    BackGround mingda("image/background_mingda.png");


    BackGround esc("image/esc_background.png");
    Button Quit("QUIT",120,290,0);
    Button Retry("RETRY",273,290,0);
    srand(time(0));
    Frame a[8];
    Frame b[8];
    SDL_Surface* toolKey[3];
    bool quit = false;
    SDL_Event e;

    buildToolKey(toolKey);

    if( !loadMedia() ) printf( "Failed to load media!\n" );
    else{
        if( !loadMedia() ) printf( "Failed to load media!\n" );
        else{
initial:
            while( !quit ){
                while( SDL_PollEvent( &e ) != 0 ){
                    if( e.type == SDL_QUIT ) quit = true;
                    for( int i = 0; i < START_BUTTONS; ++i ) gButtons[ i ].handleEvent( &e );
                    for( int i = 0; i < SCORE_BUTTONS; ++i ) sButtons[ i ].handleEvent( &e );
                    for( int i = 0; i < MINGDA_BUTTONS; ++i ) mingdaButtons[ i ].handleEvent( &e );
                    for( int i = 0; i < BOLI_BUTTONS; ++i ) boliButtons[ i ].handleEvent( &e );
                }

                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( renderer );
                SDL_RenderCopy( renderer, gTexture, NULL, NULL );
                for( int i = 0; i < START_BUTTONS; ++i ) gButtons[ i ].render();
                for( int i = 0; i < SCORE_BUTTONS; ++i ) sButtons[ i ].render();
                for( int i = 0; i < MINGDA_BUTTONS; ++i ) mingdaButtons[ i ].render();
                for( int i = 0; i < BOLI_BUTTONS; ++i ) boliButtons[ i ].render();
                SDL_RenderPresent( renderer );
                if (START==1) goto start;
                if (SCORE==1) goto ranking;
            }
        }
    }
ranking:

    while(!quit){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) quit = true;
            if(e.type == SDL_MOUSEBUTTONDOWN){
                SCORE = 0;
                goto initial;
            }
            if(e.type == SDL_KEYUP){
                SCORE = 0;
                goto initial;
            }
        }

        SDL_RenderClear(renderer);
        SDL_Rect dstrect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
        showImage("image/score_background.png",NULL,&dstrect);
        showRanking();
        showString("BACK",_font,40,0x00,50,580);

        SDL_RenderPresent(renderer);
    }

start:
    LiverMan lm;
    std::string player_name("NONAME");

    int vx = 0;
    int dropBot;
    int &bottom = lm.bot;

    bool regenerate = true;

    Dif = 0;
    Generate(1,a,b);

    while(!quit){

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) quit = true;
            if(e.type == SDL_MOUSEMOTION)
            {
                vx = (e.motion.x - 230)/10;
            }
            if(e.type == SDL_KEYUP)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_a:
                        lm += jumping_shoes; break;
                    case SDLK_s:
                        lm += flying_hat; break;
                    case SDLK_d:
                        lm += rocket; break;
                    case SDLK_SPACE:
                        lm.newBullet(vx); break;
                }
            }
        }


        if(bottom%SCREEN_HEIGHT < 14 &&regenerate)
        {
            Generate(bottom/SCREEN_HEIGHT,a,b);

            regenerate = false;
        }
        else if(bottom%SCREEN_HEIGHT > 14) regenerate = true;



        if(!lm.moveLoc(vx,a,b))
        {
            dropBot = bottom;
            goto drop;
        }

        lm.ifBounce(a,b);
        lm.ifRollScreen();

        changeTiming(a,b,bottom);
        adjustDifficulty(bottom);

        SDL_RenderClear(renderer);

        if (BOLI==0 &&MINGDA==1) mingda.load(bottom);
        else boli.load(bottom);

        int j = bottom/SCREEN_HEIGHT;
        rollFrame(j,bottom,a,b);

        lm.Score.print(bottom);
        lm.loadHealthy();

        ShowToolKey(toolKey,lm);

        SDL_RenderPresent(renderer);
        //SDL_Delay(5);
    }

    goto close;

drop:


    while(!quit)
    {
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) quit = true;
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(Quit.click(e.button))
                    quit = true;
                else if(Retry.click(e.button))
                    goto start;
            }
            if(e.type == SDL_KEYDOWN)
            {
                SDL_Keycode& input = e.key.keysym.sym;
                if(player_name.length() <= 20);
                if(input >= 'a' && input <= 'z')
                {
                    player_name += input;
                }
                if(player_name.length() > 0)
                    if(input == '\b')
                    {
                        player_name.erase(player_name.size()-1, 1);
                    }
                lm.name = player_name;
                if(player_name.length() == 0)
                    lm.name = "NONAME";
            }
        }
        SDL_RenderClear(renderer);
        esc.load(0);
        Quit.display();
        Retry.display();
        showString("NAME:", _font, 40,  0x00, 100, 150);
        showString(player_name.c_str(), _font, 40, 0, 200, 150);
        lm.Score.print(dropBot);
        lm.loadHurt();
        SDL_RenderPresent(renderer);
    }

close:
    closeWindow();

    return 0;

}

