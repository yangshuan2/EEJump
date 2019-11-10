#ifndef _INITIALIZATION_HPP_
#define _INITIALIZATION_HPP_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cstring>
#include <string>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;
extern Mix_Music* music;

bool setIconPNG(const char* icon);

//Use functions below
bool initWindow(const char* title);
bool openWindow(const char* title, const char* icon);

void fillColor(Uint32 color);
void showString(const char* _string, const char* _font, int font_size, Uint32 _color, int x, int y);
void showImage(const char* file, int screen_x, int screen_y);
void showImage(const char* file, SDL_Rect *srcrect, SDL_Rect *dstrect);
void playMusic(const char* file); //In WAV or MP3 format.
void closeWindow(void);

#endif
