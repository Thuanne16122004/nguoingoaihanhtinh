#include"mainobject.h"
#include<string>

MainObject::MainObject()
{
    frame_ =0;
    x_pos_ =500;
    y_pos_ =8500;
    x_val_ =0;
    y_val_ =0;
    width_frame_ =0;
    height_frame_ =0;
    status_ =-1;
    input_type_.left_ =0;
    input_type_.right_ =0;
    input_type_.down_ =0;
    input_type_.up_ =0;
    input_type_.jump_ =0;
    on_ground_ = false;
    map_x_ =0;
    map_y_ =0;
    come_back_time_=0;
}




MainObject::~MainObject()
{

}

bool MainObject::LoadImageA(std::string path,SDL_Renderer* screen)
 {
    bool ret = BaseObject::LoadImageA(path, screen);

    if (ret == true)
    {
        width_frame_ = rect_.w/8;
        height_frame_ =rect_.h;
    }
    return ret;
}

SDL_Rect MainObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x=rect_.x;
    rect.y=rect_.y;
    rect.w=width_frame_;
    rect.h=height_frame_;

    return rect;
}

void MainObject::set_clips()
{
    if (width_frame_ >0 && height_frame_ >0)
    {
        frame_clip_[0].x =0;
        frame_clip_[0].y=0;
        frame_clip_[0].w =width_frame_;
        frame_clip_[0].h =height_frame_;

        frame_clip_[1].x =width_frame_;
        frame_clip_[1].y=0;
        frame_clip_[1].w =width_frame_;
        frame_clip_[1].h =height_frame_;

        frame_clip_[2].x =2*width_frame_;
        frame_clip_[2].y=0;
        frame_clip_[2].w =width_frame_;
        frame_clip_[2].h =height_frame_;

        frame_clip_[3].x =3*width_frame_;
        frame_clip_[3].y=0;
        frame_clip_[3].w =width_frame_;
        frame_clip_[3].h =height_frame_;

        frame_clip_[4].x =4*width_frame_;
        frame_clip_[4].y=0;
        frame_clip_[4].w =width_frame_;
        frame_clip_[4].h =height_frame_;

        frame_clip_[5].x =5*width_frame_;
        frame_clip_[5].y=0;
        frame_clip_[5].w =width_frame_;
        frame_clip_[5].h =height_frame_;

        frame_clip_[6].x =6*width_frame_;
        frame_clip_[6].y=0;
        frame_clip_[6].w =width_frame_;
        frame_clip_[6].h =height_frame_;

        frame_clip_[7].x =7*width_frame_;
        frame_clip_[7].y=0;
        frame_clip_[7].w =width_frame_;
        frame_clip_[7].h =height_frame_;

    }
}

void MainObject::Show(SDL_Renderer* des)
{
    if (status_ == WALK_LEFT)
    {
        LoadImageA("player_left.png",des);
    }
    else
    {
        LoadImageA("player_right.png",des);
    }

    if (input_type_.left_ ==1||
        input_type_.right_ ==1)
    {
        frame_++;
    }
    else
    {
        frame_ =0;
    }

    if (frame_ >=8 *4)
    {
        frame_ =0;
    }

    rect_.x =x_pos_ - map_x_;
    rect_.y =y_pos_ - map_y_;

    SDL_Rect* current_clip =&frame_clip_[frame_ / 4];
    SDL_Rect renderQuad ={rect_.x,rect_.y,width_frame_,height_frame_};

    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_d:
            {
                status_ =WALK_RIGHT;
                input_type_.right_ =1;
                input_type_.left_ =0;

            }
            break;
            case SDLK_a:
            {
                status_ =WALK_LEFT;
                input_type_.left_ =1;
                input_type_.right_ =0;

            }
            break;
            case SDLK_w:
                {

                    input_type_.jump_ =1;
                }
                break;
                case SDLK_s:
                {

                    input_type_.down_ =1;
                }
                break;

        }
    }
    else if (events.type == SDL_KEYUP)
    {
      switch (events.key.keysym.sym)
        {
        case SDLK_d :
            {

                input_type_.right_ =0;

            }
            break;
            case SDLK_a:
            {

                input_type_.left_ =0;

            }
            break;

        }
    }

    if (events.type == SDL_MOUSEBUTTONDOWN)
    {
        if (events.button.button == SDL_BUTTON_RIGHT)
        {
              input_type_.jump_ =1;
        }
        else if (events.button.button == SDL_BUTTON_LEFT)
        {
            BullerObject* p_buller =new BullerObject();
            p_buller->LoadImageA("lazer.png", screen);

            if(status_== WALK_LEFT)
            {
               p_buller ->set_buller_dir(BullerObject::DIR_LEFT);
               p_buller->SetRect(this->rect_.x-24,rect_.y+20);
            }
            else
            {
                p_buller->set_buller_dir(BullerObject::DIR_RIGHT);
                p_buller->SetRect(this->rect_.x+24,rect_.y+20);
            }

            p_buller->SetRect(this->rect_.x+24,rect_.y+20);
            p_buller->set_x_val(10);
            p_buller->set_is_move(true);
            p_buller_list_.push_back(p_buller);

        }
    }
}

void MainObject::HandleBuller(SDL_Renderer*  des)
{
   for(int i=0; i<p_buller_list_.size();i++)
   {
       BullerObject* p_buller = p_buller_list_.at(i);
       if(p_buller != NULL)
       {
           if (p_buller->get_is_move()==true)
           {
               p_buller->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
               p_buller->Render(des);
           }
           else
           {
               p_buller_list_.erase(p_buller_list_.begin()+i);
               if(p_buller!= NULL)
               {
                   delete p_buller;
                   p_buller =NULL;
               }
           }
       }
   }
}

void MainObject::DoPlayer(Map& map_data)
{
    if(come_back_time_==0)
    {
        x_val_ =0;
    y_val_ +=GRAVITY_SPEED;

    if(y_val_>= MAX_FALL_SPEED)
    {
        y_val_ =MAX_FALL_SPEED;
    }
    if (input_type_.left_ ==1)
    {
        x_val_ -=PLAYER_SPEED;
    }
    if (input_type_.right_ ==1)
    {
        x_val_ +=PLAYER_SPEED;
    }
    if (  input_type_.jump_ ==1)
    {
        if(on_ground_ == true)
        {

        y_val_-=PLAYER_JUMP_VAL;


        }
        on_ground_ =false;
        input_type_.jump_=0;
    }
    if (  input_type_.down_ ==1)
    {
        if(on_ground_ == true)
        {

        y_val_+=PLAYER_DOWN_VAL;


        }
        on_ground_ =false;
        input_type_.down_=0;
    }

    CheckToMap(map_data);
    CenterEntityOnMap(map_data);

    }
    if(come_back_time_>0)
    {
        come_back_time_--;
        if (come_back_time_==0)
        {
            y_pos_=8500;
            x_pos_=500;
        }
    }

}

void MainObject::CenterEntityOnMap(Map& map_data)
{
    map_data.start_x_= x_pos_ -(SCREEN_WIDTH/2);
    if(map_data.start_x_ <0)
    {
        map_data.start_x_ =0;
    }
    else if (map_data.start_x_ +SCREEN_WIDTH >= map_data.max_x_)
    {
        map_data.start_x_ =map_data.max_x_ -SCREEN_WIDTH;
    }
    map_data.start_y_= y_pos_ -(SCREEN_HEIGHT/2);
    if(map_data.start_y_ <0)
    {
        map_data.start_y_ =0;
    }
    else if (map_data.start_y_ +SCREEN_HEIGHT >= map_data.max_y_)
    {
        map_data.start_y_ =map_data.max_y_ -SCREEN_HEIGHT;
    }
}
void MainObject::CheckToMap(Map& map_data)
{
    int x1 =0;
    int x2 =0;

    int y1 =0;
    int y2 =0;

     on_ground_ =false;

    //check horizontal
    int height_min =height_frame_<TILE_SIZE ? height_frame_ :TILE_SIZE;

    x1 =(x_pos_ +x_val_)/TILE_SIZE;
    x2 = (x_pos_+x_val_+width_frame_ -10)/TILE_SIZE;

    y1 =(y_pos_)/TILE_SIZE;
    y2 =(y_pos_+height_min -10)/TILE_SIZE;

    if (x1>=0 && x2< MAX_MAP_X && y1>=0 && y2< MAX_MAP_Y)
    {
        if(x_val_ >0)// main object is moving to right
        {

            if (map_data.tile[y1][x2]!= BLANK_TILE ||map_data.tile[y2][x2] != BLANK_TILE)
            {
                x_pos_ = x2*TILE_SIZE;
                x_pos_ -=width_frame_ +1;
                x_val_ =0;
            }
            if (map_data.tile[y1][x2]== BOMS_TILE ||map_data.tile[y2][x2] == BOMS_TILE)
            {
                SDL_Delay(1000);
                y_pos_ =8500;
                x_pos_ = 500;


            }

        }
        else if(x_val_ <0)
        {

            if (map_data.tile[y1][x1]!= BLANK_TILE ||map_data.tile[y2][x1 != BLANK_TILE])
            {
                x_pos_ =(x1+1)*TILE_SIZE;
                x_val_ =0;
            }
            if (map_data.tile[y1][x1]== BOMS_TILE ||map_data.tile[y2][x1] == BOMS_TILE)
            {
                SDL_Delay(1000);
               y_pos_ =8500;
                x_pos_ = 500;


            }
        }

    }
    //check vertical
    int width_min =width_frame_<TILE_SIZE ? width_frame_ :TILE_SIZE;
    x1 =(x_pos_ )/TILE_SIZE;
    x2 = (x_pos_+ width_min )/TILE_SIZE;

    y1 =(y_pos_ +y_val_)/TILE_SIZE;
    y2 =(y_pos_+y_val_+height_frame_ -1)/TILE_SIZE;

    if (x1>=0 && x2< MAX_MAP_X && y1>=0 && y2< MAX_MAP_Y)
    {
        if(y_val_ >0)// main object is moving to right
        {

            if (map_data.tile[y2][x1]!= BLANK_TILE ||map_data.tile[y2][x2] != BLANK_TILE)
            {
                y_pos_ = y2*TILE_SIZE;
                y_pos_ -=(height_frame_ +1);
                y_val_ =0;
                on_ground_ =true;
            }
             if (map_data.tile[y2][x1]== BOMS_TILE ||map_data.tile[y2][x2] == BOMS_TILE)
            {
                SDL_Delay(1000);
                y_pos_ =8500;
                x_pos_ = 500;

            }

        }
        else if(y_val_ <0)
        {

            if (map_data.tile[y1][x1]!= BLANK_TILE ||map_data.tile[y1][x2] != BLANK_TILE)
            {
                y_pos_ =(y1+1)*TILE_SIZE;
                y_val_ =0;
            }
            if (map_data.tile[y1][x1]== BOMS_TILE ||map_data.tile[y1][x2] == BOMS_TILE)
            {
                SDL_Delay(1000);
                y_pos_ =8500;
                x_pos_ = 500;


            }
        }
    }

    x_pos_ +=x_val_;
    y_pos_ +=y_val_;

    if (x_pos_<0)
    {
        x_pos_=0;
    }
    else if (x_pos_ + width_frame_ >map_data.max_x_ )
    {
        x_pos_ =map_data.max_x_ - width_frame_ -1;
    }



    if(y_pos_> map_data.max_y_)
    {
        come_back_time_=10;
    }



}
