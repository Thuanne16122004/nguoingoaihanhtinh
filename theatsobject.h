#ifndef THEATSOBJECT_H_INCLUDED
#define THEATSOBJECT_H_INCLUDED

#define THEAT_FRAME_NUM 8
#define GRAVITY_SPEED 20
#define MAX_FALL_SPEED 20
#define THREAT_SPEED 10

#include"bullerobject.h"
#include"commonfunc.h"
#include "baseobject.h"
#include"mainobject.h"

class TheatsObject : public BaseObject
{
public:
    TheatsObject();
    ~TheatsObject();

    enum TypeMove
    {
        STATIC_THREAT =0,
        MOVE_IN_SPACE_THREAT=1,
    };


    void set_x_val(const float& xVal){x_val_=xVal;}
    void set_y_val(const float& yVal){y_val_=yVal;}
    void set_x_pos(const float& xp){x_pos_=xp;}
    void set_y_pos(const float& yp){y_pos_=yp;}
    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}
    void SetMapXY(const int& mp_x, const int& mp_y){map_x_=mp_x;map_y_=mp_y;}

    SDL_Rect GetRectFrame();

    void set_clips();
    bool LoadImageA(std::string path,SDL_Renderer* screen );
    void Show(SDL_Renderer* des);
    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}
    void DoPlayer(Map& gMap);
    void CheckToMap(Map& gMap);

    void set_type_move(const int& typeMove){type_move_=typeMove;}
    void SetAnimationPos(const& pos_a, const int& pos_b){animation_a_=pos_a,animation_b_=pos_b;}
    void set_input_left(const int& ipLeft){input_type_.left_=ipLeft;}
    void ImpMoveType(SDL_Renderer* screen);

    std::vector<BullerObject*>get_buller_list() const {return buller_list_;}
    void set_buller_list(const std::vector< BullerObject*>& bl_list){buller_list_=bl_list;}

    void InitBuller(BullerObject* p_buller,SDL_Renderer* screen);
    void MakeBuller(SDL_Renderer* screen, const int& x_limit,const int& y_limit);
    void RemoveBuller(const int& idx);



private:

    int map_x_;
    int map_y_;
    float x_pos_;
    float y_pos_;
    float x_val_;
    float y_val_;
    bool on_ground_;
    int come_back_time_;
    SDL_Rect frame_clip_[THEAT_FRAME_NUM];
    int width_frame_;
    int height_frame_;
    int frame_;
    int so_anh;

    int type_move_;
    int animation_a_;
    int animation_b_;
    Input input_type_;

    std::vector<BullerObject*>buller_list_;


};

#endif // THEATSOBJECT_H_INCLUDED
