#include "Function4.hpp"
#include "Function5.hpp"
SDL_Texture* loadTexture( std::string path );

SDL_Texture* gTexture =NULL;
SDL_Rect gSpriteClips[ START_TOTAL ];
LTexture gButtonSpriteSheetTexture;

SDL_Texture* scoreTexture =NULL;
SDL_Rect scoreSpriteClips[ SCORE_TOTAL ];
ScoreTexture sButtonSpriteSheetTexture;
ScoreButton sButtons[ SCORE_BUTTONS ];

LButton gButtons[ START_BUTTONS ];
int START=0;
int SCORE=0;
bool init(){

    bool success = true;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else{
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )printf( "Warning: Linear texture filtering not enabled!" );
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL ){
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if( renderer == NULL ){
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else{
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ){
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    
    return success;
}


LTexture::LTexture(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture(){
    free();
}

bool LTexture::loadFromFile( std::string path ){
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
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

void LTexture::free(){
    if( mTexture != NULL ){
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ){
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending ){
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha ){

    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ){
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    if( clip != NULL ){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth(){
    return mWidth;
}

int LTexture::getHeight(){
    return mHeight;
}

LButton::LButton(){
    mPosition.x = 0;
    mPosition.y = 0;
    
    mCurrentSprite = START_OUT;
}

void LButton::setPositionstart( int x, int y ){
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::handleEvent( SDL_Event* e ){
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
        
        int x, y;
        SDL_GetMouseState( &x, &y );
        bool inside = true;
        if( x < mPosition.x || x > mPosition.x + START_BUTTON_WIDTH || y < mPosition.y ||y > mPosition.y + START_BUTTON_HEIGHT){
            inside = false;
        }
        if( !inside )
            mCurrentSprite = START_OUT;
        else{
            switch( e->type ){
                case SDL_MOUSEMOTION:
                    mCurrentSprite = START_OVER_MOTION;
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    mCurrentSprite = START_DOWN;
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                    START=1;
                    break;
            }
        }
    }
}

void LButton::render(){
    gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
}



bool loadMedia(){
    bool success = true;
    gTexture = loadTexture( "image/initial.png" );
    if( gTexture == NULL ){
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    if( !gButtonSpriteSheetTexture.loadFromFile( "image/start_button.png" ) ){
        printf( "Failed to load button sprite texture!\n" );
        success = false;
    }
    else if( !sButtonSpriteSheetTexture.loadFromFile( "image/score_button.png" ) ){
        printf( "Failed to load button sprite texture!\n" );
        success = false;
    }
    else if( !boliButtonSpriteSheetTexture.loadFromFile( "image/boli_button.png" ) ){
        printf( "Failed to load button sprite texture!\n" );
        success = false;
    }
    else if( !mingdaButtonSpriteSheetTexture.loadFromFile( "image/mingda_button.png" ) ){
        printf( "Failed to load button sprite texture!\n" );
        success = false;
    }
    else{
        for( int i = 0; i < START_TOTAL; ++i ){
            gSpriteClips[ i ].x = 0;
            gSpriteClips[ i ].y = i * 60;
            gSpriteClips[ i ].w = START_BUTTON_WIDTH;
            gSpriteClips[ i ].h = START_BUTTON_HEIGHT;
        }
        gButtons[ 0 ].setPositionstart( 192, 303 );

        for( int i = 0; i < SCORE_TOTAL; ++i ){
            gSpriteClips[ i ].x = 0;
            gSpriteClips[ i ].y = i * 60;
            gSpriteClips[ i ].w = SCORE_BUTTON_WIDTH;
            gSpriteClips[ i ].h = SCORE_BUTTON_HEIGHT;
        }
        sButtons[ 0 ].setPositionscore( 192, 368 );
        
        for( int i = 0; i < MINGDA_TOTAL; ++i ){
            mingdaSpriteClips[ i ].x = 0;
            mingdaSpriteClips[ i ].y = i * 60;
            mingdaSpriteClips[ i ].w = MINGDA_BUTTON_WIDTH;
            mingdaSpriteClips[ i ].h = MINGDA_BUTTON_HEIGHT;
        }
        mingdaButtons[ 0 ].setPositionMINGDA( 35, 550 );
        
        for( int i = 0; i < BOLI_TOTAL; ++i ){
            mingdaSpriteClips[ i ].x = 0;
            mingdaSpriteClips[ i ].y = i * 60;
            mingdaSpriteClips[ i ].w = BOLI_BUTTON_WIDTH;
            mingdaSpriteClips[ i ].h = BOLI_BUTTON_HEIGHT;
        }
        boliButtons[ 0 ].setPositionBOLI( 145, 550 );
    }
    return success;
}

void close(){
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture( std::string path ){

    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ){
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else{
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL ){
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

ScoreTexture::ScoreTexture(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

ScoreTexture::~ScoreTexture(){
    free();
}

bool ScoreTexture::loadFromFile( std::string path ){
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );

    else{
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        else{
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void ScoreTexture::free(){
    if( mTexture != NULL ){
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void ScoreTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ){
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void ScoreTexture::setBlendMode( SDL_BlendMode blending ){
    SDL_SetTextureBlendMode( mTexture, blending );
}

void ScoreTexture::setAlpha( Uint8 alpha ){
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void ScoreTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ){
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    if( clip != NULL ){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int ScoreTexture::getWidth(){
    return mWidth;
}

int ScoreTexture::getHeight(){
    return mHeight;
}

ScoreButton::ScoreButton(){
    mPosition.x = 0;
    mPosition.y = 0;
    
    mCurrentSprite = SCORE_OUT;
}

void ScoreButton::setPositionscore( int x, int y ){
    mPosition.x = x;
    mPosition.y = y;
}

void ScoreButton::handleEvent( SDL_Event* e ){
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
        
        int x, y;
        SDL_GetMouseState( &x, &y );
        bool inside = true;
        if( x < mPosition.x || x > mPosition.x + SCORE_BUTTON_WIDTH || y < mPosition.y ||y > mPosition.y + SCORE_BUTTON_HEIGHT){
            inside = false;
        }
        if( !inside )mCurrentSprite = SCORE_OUT;
        else{
            switch( e->type ){
                case SDL_MOUSEMOTION:
                    mCurrentSprite = SCORE_OVER_MOTION;
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    mCurrentSprite = SCORE_DOWN;
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                    SCORE=1;
                    break;
            }
        }
    }
}

void ScoreButton::render(){
    sButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
}

