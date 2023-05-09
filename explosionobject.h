#ifndef EXPLOSIONOBJECT_H_INCLUDED
#define EXPLOSIONOBJECT_H_INCLUDED

#include"commonfunc.h"
#include"baseobject.h"
#include"bullerobject.h"

#define  NUM_FRAME_EXP 8

class ExplosionObject : public BaseObject
{
public:
  ExplosionObject(void);
  ~ExplosionObject(void);

public:
  void set_clips();
  void set_frame(const int& fr) {frame_ = fr;}
  virtual bool LoadImageA(std::string path, SDL_Renderer* screen);
  void Show(SDL_Renderer* screen);
  int get_frame_width() const {return frame_width_;}
  int get_frame_height() const {return frame_height_;}
private:
  int frame_width_;
  int frame_height_;
  unsigned int frame_;
  SDL_Rect frame_clip_[8];
};


#endif // EXPLOSIONOBJECT_H_INCLUDED
