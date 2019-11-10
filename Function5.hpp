#ifndef Function5_hpp
#define Function5_hpp

#include <stdio.h>

#endif /* Function5_hpp */
#ifndef Function4_hpp
#define Function4_hpp
#include "Initialization.hpp"
#include <stdio.h>
#endif /* Function4_hpp */
#include <string>
#include <iostream>
using namespace std;


const int MINGDA_BUTTON_WIDTH = 112;
const int MINGDA_BUTTON_HEIGHT = 60;
const int MINGDA_BUTTONS = 1;

const int BOLI_BUTTON_WIDTH = 112;
const int BOLI_BUTTON_HEIGHT = 60;
const int BOLI_BUTTONS = 1;

extern int MINGDA;
extern int BOLI;

enum MINGDAButtonSprite{
    MINGDA_OUT = 0,
    MINGDA_OVER_MOTION = 1,
    MINGDA_DOWN = 2,
    MINGDA_UP = 3,
    MINGDA_TOTAL = 4
};

enum BOLIButtonSprite{
    BOLI_OUT = 0,
    BOLI_OVER_MOTION = 1,
    BOLI_DOWN = 2,
    BOLI_UP = 3,
    BOLI_TOTAL = 4
};

class MINGDATexture{
public:
    MINGDATexture();
    ~MINGDATexture();
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


class MINGDAButton{
public:
    MINGDAButton();
    void setPositionMINGDA( int x, int y );
    void handleEvent( SDL_Event* e );
    void render();
private:
    SDL_Point mPosition;
    MINGDAButtonSprite mCurrentSprite;
};

class BOLITexture{
public:
    BOLITexture();
    ~BOLITexture();
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

class BOLIButton{
public:
    BOLIButton();
    void setPositionBOLI( int x, int y );
    void handleEvent( SDL_Event* e );
    void render();
private:
    SDL_Point mPosition;
    BOLIButtonSprite mCurrentSprite;
};

bool init();
bool loadMedia();
void close();



extern SDL_Texture* mingdaTexture ;
extern SDL_Rect mingdaSpriteClips[ MINGDA_TOTAL ];
extern MINGDATexture mingdaButtonSpriteSheetTexture;
extern MINGDAButton mingdaButtons[ MINGDA_BUTTONS ];

extern SDL_Texture* boliTexture ;
extern SDL_Rect boliSpriteClips[ BOLI_TOTAL ];
extern BOLITexture boliButtonSpriteSheetTexture;
extern BOLIButton boliButtons[ BOLI_BUTTONS ];
















