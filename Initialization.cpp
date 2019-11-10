#include "Initialization.hpp"

SDL_Window* window;
static SDL_Surface* tmpImage;
SDL_Renderer* renderer;
SDL_Texture* texture;
Mix_Music* music = NULL;

bool initWindow(const char* title){
    if(SDL_Init(SDL_INIT_VIDEO) != 0) return 0;
    window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL) return 0;
	if(!IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG|IMG_INIT_TIF|IMG_INIT_WEBP)) return 0;
	if(TTF_Init() != 0) return 0;
	if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) != 0) return 0;
	renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) return 0;
    SDL_RenderClear(renderer);
	return 1;
}

bool setIconPNG(const char* icon){
	SDL_Surface *ico = IMG_Load(icon);
	if (ico == NULL) return 0;
    SDL_SetWindowIcon(window, ico);
    SDL_FreeSurface(ico);
    return 1;
}

bool openWindow(const char* title, const char* icon){
    if(!initWindow(title)) return 0;
	if(!setIconPNG(icon)) return 0;
    return 1;
}

void fillColor(Uint32 color)
{
    SDL_Surface* tmpBlock = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect(tmpBlock,NULL,color);
    texture = SDL_CreateTextureFromSurface(renderer, tmpBlock);
    SDL_FreeSurface(tmpBlock);
    if (texture == NULL) return;
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_DestroyTexture(texture);
}

void showString(const char* _string, const char* _font, int font_size, Uint32 _color, int x, int y){
    SDL_Color color;
    color.r = _color/0x10000; color.g = (_color/0x100-color.r*0x10000); color.b = (_color-color.r*0x10000-color.g*0x100); color.a = 255;
    int len = (double)strlen(_string)/2*font_size;
    SDL_Rect strrect={x,y,len,font_size};
    TTF_Font* font = TTF_OpenFont(_font, font_size);
    tmpImage = TTF_RenderText_Blended(font, _string, color);
    TTF_CloseFont(font);
    texture = SDL_CreateTextureFromSurface(renderer, tmpImage);
    SDL_FreeSurface(tmpImage);
    SDL_RenderCopy(renderer, texture, NULL, &strrect);
    SDL_DestroyTexture(texture);
}

void showImage(const char* file, SDL_Rect *srcrect, SDL_Rect *dstrect){
    tmpImage = SDL_LoadBMP(file);
    if(tmpImage == NULL)
    {
        SDL_RWops* rwop = SDL_RWFromFile(file,"rb");
        tmpImage = IMG_Load_RW(rwop,1);
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmpImage);
    SDL_FreeSurface(tmpImage);
    if (texture == NULL) return;
    SDL_RenderCopy(renderer, texture, srcrect, dstrect);
    SDL_DestroyTexture(texture);
}

void showImage(const char* file, int screen_x, int screen_y)
{
    tmpImage = SDL_LoadBMP(file);
    if(tmpImage == NULL)
    {
        SDL_RWops* rwop = SDL_RWFromFile(file,"rb");
        tmpImage = IMG_Load_RW(rwop,1);
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmpImage);
    if (texture == NULL) return;
    SDL_Rect tmpRect= {screen_x,screen_y,tmpImage->w,tmpImage->h};
    SDL_FreeSurface(tmpImage);
    SDL_RenderCopy(renderer, texture, NULL, &tmpRect);
    SDL_DestroyTexture(texture);
}

void playMusic(const char* file){
    music = Mix_LoadMUS( file );
    Mix_PlayMusic( music, -1 );
}

void closeWindow(void){
    if(music) {
        if(Mix_PausedMusic()||Mix_PlayingMusic())
            Mix_HaltMusic();
        Mix_FreeMusic( music );
    }
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();
}

