#ifndef Function4_hpp
#define Function4_hpp
#include <stdio.h>
#endif /* Function4_hpp */
#include "Initialization.hpp"
#include <string>
#include <iostream>
using namespace std;

const int START_BUTTON_WIDTH = 112;
const int START_BUTTON_HEIGHT = 60;
const int START_BUTTONS = 1;

const int SCORE_BUTTON_WIDTH = 112;
const int SCORE_BUTTON_HEIGHT = 60;
const int SCORE_BUTTONS = 1;

extern int START;
extern int SCORE;

enum STARTButtonSprite{
    START_OUT = 0,
    START_OVER_MOTION = 1,
    START_DOWN = 2,
    START_UP = 3,
    START_TOTAL = 4
};

enum SCOREButtonSprite{
    SCORE_OUT = 0,
    SCORE_OVER_MOTION = 1,
    SCORE_DOWN = 2,
    SCORE_UP = 3,
    SCORE_TOTAL = 4
};

class LTexture{
public:
    LTexture();
    ~LTexture();
    bool loadFromFile( std::string path );
#ifdef _SDL_TTF_H
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
#endif
    void free();
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    int getWidth();
    int getHeight();
private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};


class LButton{
public:
    LButton();
    void setPositionstart( int x, int y );
    void handleEvent( SDL_Event* e );
    void render();
private:
    SDL_Point mPosition;
    STARTButtonSprite mCurrentSprite;
    int tmp=0;
};

class ScoreTexture{
public:
    ScoreTexture();
    ~ScoreTexture();
    bool loadFromFile( std::string path );
#ifdef _SDL_TTF_H
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
#endif
    void free();
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    int getWidth();
    int getHeight();
private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};

class ScoreButton{
public:
    ScoreButton();
    void setPositionscore( int x, int y );
    void handleEvent( SDL_Event* e );
    void render();
private:
    SDL_Point mPosition;
    SCOREButtonSprite mCurrentSprite;
};

bool init();
bool loadMedia();
void close();

extern SDL_Texture* loadTexture( std::string path );

extern SDL_Texture* gTexture ;
extern SDL_Rect gSpriteClips[ START_TOTAL ];
extern LTexture gButtonSpriteSheetTexture;
extern LButton gButtons[ START_BUTTONS ];

extern SDL_Texture* scoreTexture ;
extern SDL_Rect scoreSpriteClips[ SCORE_TOTAL ];
extern ScoreTexture sButtonSpriteSheetTexture;
extern ScoreButton sButtons[ SCORE_BUTTONS ];
