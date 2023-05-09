#include<iostream>
#include"commonfunc.h"
#include"baseobject.h"
#include"gamemap1.h"
#include"mainobject.h"
#include"Imptimer.h"
#include"bullerobject.h"
#include"theatsobject.h"
#include"textobject.h"
#include"explosionobject.h"
#include"player_power.h"


BaseObject g_background;
TTF_Font* font_time=NULL;
TTF_Font* font_result=NULL;


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
        font_time=TTF_OpenFont("dlxfont_.ttf",30);
        font_result=TTF_OpenFont("dlxfont_.ttf",150);

        if(font_time == NULL)
        {
            success= false;
        }


         if (Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096)==-1)
        {
            success=false;
        }
        g_sound_buller[0]=Mix_LoadWAV("Laser.wav");
        g_sound_buller[1]=Mix_LoadWAV("Fire.wav");
        g_sound_buller[2]=Mix_LoadWAV("1.wav");
        g_sound_exp[0]=Mix_LoadWAV("Explosion+5.wav");
        g_sound_exp[1]=Mix_LoadWAV("Explosion+1.wav");
        g_sound_exp[2]=Mix_LoadWAV("11.wav");



        if(g_sound_buller[0] == NULL||g_sound_buller[1]==NULL||g_sound_exp[0]==NULL||g_sound_exp[1]==NULL)
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
    TheatsObject* dynamic_objs =new TheatsObject[20];
    for(int i=0;i<10;i++)
    {
        TheatsObject* p_theat =(dynamic_objs+i);
        if (p_theat != NULL)
        {
            p_theat->LoadImageA("ghost_left.png", g_screen);
            p_theat->set_clips();
            p_theat->set_type_move(TheatsObject::MOVE_IN_SPACE_THREAT);
            p_theat->set_x_pos(2000);
            p_theat->set_y_pos( 1500*i);

            int pos1=p_theat->get_x_pos()-500;
            int pos2=p_theat->get_x_pos()+500;
            p_theat->SetAnimationPos(pos1,pos2);

            list_theats.push_back(p_theat);
        }
    }

    TheatsObject* theats_objs =new TheatsObject[20];
    for(int i=0;i<5;i++)
    {
        TheatsObject* p_theat =(theats_objs+i);
        if (p_theat != NULL)
        {
            p_theat->LoadImage("khung_long_left.png", g_screen);
            p_theat->set_clips();
            p_theat->set_x_pos(1000+i*1000);
            p_theat->set_y_pos( 8300);
            p_theat->set_type_move(TheatsObject::STATIC_THREAT);
            p_theat->set_input_left(0);

            BullerObject* p_buller =new BullerObject();
            p_buller->set_buller_type(BullerObject::LASER);
            p_buller->LoadImgBuller( g_screen);
            p_theat->InitBuller(p_buller,g_screen);


            list_theats.push_back(p_theat);
        }
    }
    TheatsObject* theats_boss =new TheatsObject[20];
    for(int i=0;i<5;i++)
    {
        TheatsObject* p_theat =(theats_boss+i);
        if (p_theat != NULL)
        {
            p_theat->LoadImage("threat_level.png", g_screen);
            p_theat->set_clips();
            p_theat->set_x_pos(1000);
            p_theat->set_y_pos( 500);
            p_theat->set_type_move(TheatsObject::STATIC_THREAT);
            p_theat->set_input_left(0);

            BullerObject* p_buller =new BullerObject();
            p_buller->set_buller_type(BullerObject::DAN_TRON);
            p_buller->LoadImgBuller( g_screen);
            p_theat->InitBuller(p_buller,g_screen);


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
    p_player.LoadImageA("threat_right.png", g_screen);
    p_player.set_clips();

    PlayerPower player_power;
    player_power.Init(g_screen);


    std::vector<TheatsObject*> theats_list =MakeTheatList();


    ExplosionObject exp_theat;
    bool tRet= exp_theat.LoadImageA("exp3.png", g_screen);
    if(!tRet)return -1;
    exp_theat.set_clips();


    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_COLOR);


    TextObject mark_game;
    mark_game.SetColor(TextObject::BLACK_COLOR);
    UINT mark_value=0;

    int num_die=0;
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
            p_player.HandelInputAction(g_event, g_screen,g_sound_buller);
        }

    SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
    SDL_RenderClear(g_screen);

    g_background.Render(g_screen, NULL);
    game_map.DrawMap(g_screen);
    Map map_data= game_map.getMap();



    p_player.HandleBuller(g_screen,g_sound_buller);
    p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
    p_player.DoPlayer(map_data);
    p_player.Show(g_screen);

    player_power.Show(g_screen);

    for(int i=0; i<theats_list.size(); i++)
    {
        TheatsObject* p_theat = theats_list.at(i);
        if (p_theat!= NULL)
        {
            p_theat->SetMapXY(map_data.start_x_,map_data.start_y_);
            p_theat->ImpMoveType(g_screen);
            p_theat-> DoPlayer(map_data);

            p_theat->Show(g_screen);
            p_theat->MakeBuller(g_screen, SCREEN_WIDTH,SCREEN_HEIGHT);


    int frame_exp_width=exp_theat.get_frame_width();
    int frame_exp_height=exp_theat.get_frame_height();


  std::vector <BullerObject*> buller_arr =p_player.get_buller_list();
  for (int r=0; r< buller_arr.size();++r)
  {
      BullerObject* p_buller =buller_arr.at(r);
      if (p_buller != NULL)
      {
          for( int t=0; t< theats_list.size();++t)
          {
              TheatsObject* p_theat=theats_list.at(t);
              if (p_theat!= NULL)
              {
                  SDL_Rect tRect;
                  tRect.x= p_theat->GetRect().x;
                  tRect.y= p_theat->GetRect().y;
                  tRect.w= p_theat->get_width_frame();
                  tRect.h= p_theat->get_height_frame();

                  SDL_Rect bRect= p_buller->GetRect();

                  bool bCo1= SDLCommonFunc::CheckCollision(bRect,tRect);
                  if (bCo1)
                  {
                      mark_value+=100;
                      for (int ex=0; ex< NUM_FRAME_EXP; ++ex)
                      {
                          int x_pos =p_buller->GetRect().x - frame_exp_width*1/2;
                          int y_pos =p_buller->GetRect().y - frame_exp_height*1/2;

                          exp_theat.set_frame(ex);
                          exp_theat.SetRect(x_pos, y_pos);
                          exp_theat.Show(g_screen);
                      }

                      p_player.RemoveBuller(r);
                      p_theat->Free();
                      theats_list.erase(theats_list.begin()+t);
                      Mix_PlayChannel(-1,g_sound_exp[1],0);

                  }
              }
          }
      }

  }

  SDL_Rect rect_player =p_player.GetRectFrame();
  bool bCol1=false;
  std ::vector<BullerObject*> tBuller_list =p_theat->get_buller_list();
  for (int m=0;m<tBuller_list.size();++m)
  {
      BullerObject* pt_buller=tBuller_list.at(m);
      if (pt_buller)
      {
          bCol1=SDLCommonFunc::CheckCollision(pt_buller->GetRect(), rect_player);
          if (bCol1)
          {

              for (int ex=0; ex< NUM_FRAME_EXP; ++ex)
                      {
                          int x_pos =pt_buller->GetRect().x - frame_exp_width*1/2;
                          int y_pos =pt_buller->GetRect().y - frame_exp_height*1/2;

                          exp_theat.set_frame(ex);
                          exp_theat.SetRect(x_pos, y_pos);
                          exp_theat.Show(g_screen);
                      }
              p_theat->RemoveBuller(m);
              break;
          }
      }
  }
  SDL_Rect rect_theat= p_theat->GetRectFrame();
  bool bCol2=SDLCommonFunc::CheckCollision(rect_player, rect_theat);

if (bCol2)
          {

              for (int ex=0; ex< NUM_FRAME_EXP; ++ex)
                      {
                          int x_pos =p_theat->GetRect().x - frame_exp_width*1/2;
                          int y_pos =p_theat->GetRect().y - frame_exp_height*1/2;

                          exp_theat.set_frame(ex);
                          exp_theat.SetRect(x_pos, y_pos);
                          exp_theat.Show(g_screen);
                      }

          }


if (bCol2||bCol1)
{

    Mix_PlayChannel(-1,g_sound_exp[0],0);

    num_die++;

    if (num_die<3)
    {
        p_player.SetRect(0,0);
        p_player.set_come_back_time(10);
        player_power.Decrease();
        player_power.Render(g_screen);
        continue;
    }
    else
    {
    if (MessageBoxA(NULL,"Game Over ","Information",MB_OK|MB_ICONINFORMATION)==IDOK)
    {
        p_theat->Free();
        close();
        SDL_Quit();
        return 0;
    }
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
    Uint32 val_time =100- time_val;



    if(val_time<=10)
    {
        time_game.SetColor(TextObject::RED_COLOR);

    }

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

    std:: string val_str_mark = std::to_string(mark_value );
    std::string strMark("SCORES: ");
    strMark += val_str_mark;
    mark_game.SetText(strMark);
    mark_game.LoadFromRenderText(font_time, g_screen);
    mark_game.RenderText(g_screen, SCREEN_WIDTH*1/2-200,50);

    TextObject mark_need;
    mark_need.SetColor(TextObject::BLACK_COLOR);
    std::string MarkNeed("/1200");
    mark_need.SetText(MarkNeed);
    mark_need.LoadFromRenderText(font_time, g_screen);
    mark_need.RenderText(g_screen, SCREEN_WIDTH*1/2 +150,50);

    TextObject result;
    result.SetColor(TextObject::WHITE_COLOR);
    std::string Win("YOU WIN");
    if(mark_value==1200)
    {
    result.SetText(Win);
    result.LoadFromRenderText(font_result, g_screen);
    result.RenderText(g_screen, 300,100);
    SDL_RenderPresent(g_screen);
    SDL_Delay(1000);
    if (MessageBoxA(NULL,"YOU WIN","Information",MB_OK|MB_ICONINFORMATION)==IDOK)
    {

        close();
        SDL_Quit();
        return 0;
    }
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
