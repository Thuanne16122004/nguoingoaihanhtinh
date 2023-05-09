#include "bullerobject.h"

BullerObject::BullerObject()
{
    x_val_=0;
    y_val_=0;
    is_move_=false;
    buller_type_=DAN_TRON;
}

BullerObject::~BullerObject()
{

}

void BullerObject::LoadImgBuller(SDL_Renderer* des)
{
  if (buller_type_==DAN_TRON)
  {
      LoadImage("lazer2.png", des);

  }
  else
  {
      LoadImage("lazer.png", des);

  }
}

void BullerObject::HandleMove(const int& x_border,const int& y_border)
{
    if (buller_dir_==DIR_RIGHT)
    {

    rect_.x += x_val_;


    if (rect_.x> x_border)
    {
        is_move_=false;
    }
    }
    if (buller_dir_==DIR_LEFT)
    {

    rect_.x -= x_val_;
    if (rect_.x<0)
    {
        is_move_=false;
    }
    }
}
