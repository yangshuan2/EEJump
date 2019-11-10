#include "Function4.hpp"
#include "Function5.hpp"

SDL_Texture* mingdaTexture =NULL;
SDL_Rect mingdaSpriteClips[ MINGDA_TOTAL ];
MINGDATexture mingdaButtonSpriteSheetTexture;
MINGDAButton mingdaButtons[ MINGDA_BUTTONS ];

SDL_Texture* boliTexture =NULL;
SDL_Rect boliSpriteClips[ BOLI_TOTAL ];
BOLITexture boliButtonSpriteSheetTexture;
BOLIButton boliButtons[ BOLI_BUTTONS ];

int MINGDA=0;
int BOLI=0;

MINGDATexture::MINGDATexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

MINGDATexture::~MINGDATexture()
{
    free();
}

bool MINGDATexture::loadFromFile( std::string path )
{
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    
    else{
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL ){
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else{
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void MINGDATexture::free(){
    if( mTexture != NULL ){
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void MINGDATexture::setColor( Uint8 red, Uint8 green, Uint8 blue ){
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void MINGDATexture::setBlendMode( SDL_BlendMode blending ){
    SDL_SetTextureBlendMode( mTexture, blending );
}

void MINGDATexture::setAlpha( Uint8 alpha ){
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void MINGDATexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ){
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    if( clip != NULL ){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int MINGDATexture::getWidth(){
    return mWidth;
}

int MINGDATexture::getHeight(){
    return mHeight;
}

MINGDAButton::MINGDAButton(){
    mPosition.x = 0;
    mPosition.y = 0;
    
    mCurrentSprite = MINGDA_OUT;
}

void MINGDAButton::setPositionMINGDA( int x, int y ){
    mPosition.x = x;
    mPosition.y = y;
}

void MINGDAButton::handleEvent( SDL_Event* e ){
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
        int x, y;
        SDL_GetMouseState( &x, &y );
        bool inside = true;
        if( x < mPosition.x || x > mPosition.x + MINGDA_BUTTON_WIDTH || y < mPosition.y ||y > mPosition.y + MINGDA_BUTTON_HEIGHT){
            inside = false;
        }
        if( !inside ) mCurrentSprite = MINGDA_OUT;
        else{
            switch( e->type ){
                case SDL_MOUSEMOTION:
                    mCurrentSprite = MINGDA_OVER_MOTION;
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    mCurrentSprite = MINGDA_DOWN;
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                    MINGDA=1;BOLI=0;
                    mCurrentSprite = MINGDA_DOWN;
                    break;
            }
        }
    }
}

void MINGDAButton::render(){
    mingdaButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &mingdaSpriteClips[ mCurrentSprite ] );
}


BOLITexture::BOLITexture(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

BOLITexture::~BOLITexture(){
    free();
}

bool BOLITexture::loadFromFile( std::string path ){
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ){
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else{
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else{
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void BOLITexture::free(){
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void BOLITexture::setColor( Uint8 red, Uint8 green, Uint8 blue ){
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void BOLITexture::setBlendMode( SDL_BlendMode blending ){
    SDL_SetTextureBlendMode( mTexture, blending );
}

void BOLITexture::setAlpha( Uint8 alpha ){
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void BOLITexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ){
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    if( clip != NULL ){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int BOLITexture::getWidth(){
    return mWidth;
}

int BOLITexture::getHeight(){
    return mHeight;
}

BOLIButton::BOLIButton(){
    mPosition.x = 0;
    mPosition.y = 0;
    
    mCurrentSprite = BOLI_OUT;
}

void BOLIButton::setPositionBOLI( int x, int y ){
    mPosition.x = x;
    mPosition.y = y;
}

void BOLIButton::handleEvent( SDL_Event* e ){
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
        
        int x, y;
        SDL_GetMouseState( &x, &y );
        bool inside = true;
        if( x < mPosition.x || x > mPosition.x + BOLI_BUTTON_WIDTH || y < mPosition.y ||y > mPosition.y + BOLI_BUTTON_HEIGHT){
            inside = false;
        }
        if( !inside ){
            mCurrentSprite = BOLI_OUT;
        }
        else{
            switch( e->type ){
                case SDL_MOUSEMOTION:
                    mCurrentSprite = BOLI_OVER_MOTION;
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    mCurrentSprite = BOLI_DOWN;
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                    MINGDA=0;BOLI=1;
                    mCurrentSprite = BOLI_DOWN;
                    break;
            }
        }
    }
}

void BOLIButton::render(){
    boliButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &mingdaSpriteClips[ mCurrentSprite ] );
}









