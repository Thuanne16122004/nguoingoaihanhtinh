#ifndef COMMONFUNC_H_INCLUDED
#define COMMONFUNC_H_INCLUDED

#include <vector>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include<iostream>
#include<winuser.h>

static SDL_Window* g_window =NULL;
static SDL_Renderer* g_screen =NULL;
static SDL_Event g_event;


//screen
const int FPS =144;
const int SCREEN_WIDTH =1500;
const int SCREEN_HEIGHT =750;
const int SCREEN_BPP =32;

const int COLOR_KEY_R =167;
const int COLOR_KEY_G =175;
const int COLOR_KEY_B =180;

const int RENDER_DRAW_COLOR = 0Xff;

#define BLANK_TILE 0
#define TILE_SIZE 75

#define MAX_MAP_X 60
#define MAX_MAP_Y 120


typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};

typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1,const SDL_Rect& object2);

}

#endif // COMMONFUNC_H_INCLUDED
