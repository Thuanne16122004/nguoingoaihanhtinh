#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED

#include <vector>
#include"commonfunc.h"
#include"baseobject.h"
#include"bullerobject.h"

#define GRAVITY_SPEED 15
#define MAX_FALL_SPEED 15
#define PLAYER_SPEED 120
#define PLAYER_JUMP_VAL 120
#define PLAYER_DOWN_VAL 150
class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum WalkType
    {
        WALK_RIGHT =0,
        WALK_LEFT =1,
        JUMP =2,
    };


    bool LoadImageA (std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
    void set_clips();

    void DoPlayer(Map& map_data);
    void CheckToMap(Map& map_data);
    void SetMapXY(const int map_x, int const map_y){map_x_ =map_x; map_y_=map_y;}
    void CenterEntityOnMap(Map& map_data);
    SDL_Rect GetRectFrame();


    void set_buller_list(std::vector<BullerObject*>buller_list)
    {
        p_buller_list_=buller_list;


     }
    std::vector<BullerObject*> get_buller_list() const {return p_buller_list_;}
    void HandleBuller(SDL_Renderer*  des);

private:

    std::vector<BullerObject*> p_buller_list_;
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[8];//so anh
    Input input_type_;
    int frame_;
    int status_;
    bool on_ground_;

    int map_x_;
    int map_y_;

    int come_back_time_;
};

#endif // MAINOBJECT_H_INCLUDED
