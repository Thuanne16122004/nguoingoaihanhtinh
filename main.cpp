#include<iostream>
#include"commonfunc.h"
#include"baseobject.h"
#include"gamemap1.h"
#include"mainobject.h"
#include"Imptimer.h"
#include"bullerobject.h"
#include"theatsobject.h"
#include"textobject.h"

BaseObject g_background;
TTF_Font* font_time=NULL;
bool InitData()
{
    bool success =true;
    int ret =SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window =SDL_CreateWindow("MY GAME CPP SDL2",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);

    if (g_window == NULL)
    {
        success =false;
    }
    else
    {
        g_screen =SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if (g_screen == NULL)
            success ==false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }

        if (TTF_Init()==-1)
        {
            success=false;
        }
        font_time=TTF_OpenFont("dlxfont_.ttf",20);
        if(font_time == NULL)
        {
            success= false;
        }

    }
    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImageA("backgroundnen.png", g_screen);
    if (ret == false)
        return false;

    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen == NULL;

    SDL_DestroyWindow(g_window);
    g_window ==NULL;

    IMG_Quit();
    SDL_Quit();
}
std::vector<TheatsObject*> MakeTheatList()
{
    std::vector<TheatsObject*> list_theats;
    TheatsObject* theats_objs =new TheatsObject[20];
    for(int i=0;i<20;i++)
    {
        TheatsObject* p_theat =(theats_objs+i);
        if (p_theat != NULL)
        {
            p_theat->LoadImageA("phi_thuyen_.png", g_screen);
            p_theat->set_clips();
            p_theat->set_x_pos(500);
            p_theat->set_y_pos( 1500);

            list_theats.push_back(p_theat);
        }
    }
    return list_theats;
}

int main (int argc, char* argv[])
{
    ImpTimer fps_timer;


    if (InitData() == false)
        return -1;

    if (LoadBackground()== false)
        return -1;


    GameMap game_map;
    game_map.LoadMap("map.03.txt");
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImageA("player_right.png", g_screen);
    p_player.set_clips();


    std::vector<TheatsObject*> theats_list =MakeTheatList();


    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_COLOR);


    bool is_quit = false;
    while (!is_quit)
    {
        fps_timer.start();
        while(SDL_PollEvent(&g_event)!=0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit =true;
            }
            p_player.HandelInputAction(g_event, g_screen);
        }

    SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
    SDL_RenderClear(g_screen);

    g_background.Render(g_screen, NULL);
    game_map.DrawMap(g_screen);
    Map map_data= game_map.getMap();



    p_player.HandleBuller(g_screen);
    p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
    p_player.DoPlayer(map_data);
    p_player.Show(g_screen);

    for(int i=0; i<theats_list.size(); i++)
    {
        TheatsObject* p_theat = theats_list.at(i);
        if (p_theat!= NULL)
        {
            p_theat->SetMapXY(map_data.start_x_,map_data.start_y_);
            p_theat-> DoPlayer(map_data);
            p_theat->Show(g_screen);


            bool bColl2=false;
    bColl2 = SDLCommonFunc::CheckCollision(p_player.GetRectFrame(),p_theat->GetRectFrame());
if (bColl2==true)
{
    if (MessageBoxA(NULL,"You win ","Information",MB_OK|MB_ICONINFORMATION)==IDOK)
    {
        p_theat->Free();
        close();
        SDL_Quit();
        return 0;
    }

}
}
    }



    game_map.SetMap(map_data);
    game_map.DrawMap(g_screen);


    SDL_RenderPresent(g_screen);

    //show game time
    std::string str_time="Time: ";
    Uint32 time_val =SDL_GetTicks()/1000;
    Uint32 val_time =240- time_val;
    if(val_time<=0)
{
    if (MessageBoxA(NULL,"GAME OVER ","Information",MB_OK|MB_ICONSTOP)==IDOK)
    {
        is_quit=true;
        break;
    }

}
    else
    {
        std::string str_val = std::to_string (val_time);
        str_time+=str_val;

        time_game.SetText(str_time);
        time_game.LoadFromRenderText(font_time,g_screen);
        time_game.RenderText(g_screen,SCREEN_WIDTH-300,50);
    }

    SDL_RenderPresent(g_screen);


    int real_imp_time = fps_timer.get_ticks();
    int time_one_frame =1000/FPS;

    if (real_imp_time< time_one_frame)
    {
        int delay_time = time_one_frame -real_imp_time;
        if (delay_time>=0)
        SDL_Delay(delay_time);
    }
    }

    close();
    return 0;

}
