#ifndef DRAWER_H
#define DRAWER_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window *gwin;
extern SDL_Renderer *grend;

void update();

bool init();

// bool loadMedia();

void hang();

void close();

// SDL_Texture* loadTexture( std::string path );

#endif
