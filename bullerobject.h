#ifndef BULLEROBJECT_H_INCLUDED
#define BULLEROBJECT_H_INCLUDED

#include "baseobject.h"
#include "commonfunc.h"

class BullerObject : public BaseObject
{

public:
    BullerObject();
    ~BullerObject();

    enum BULLER_DIR
    {
        DIR_RIGHT= 3,
        DIR_LEFT=4,
    };

    void set_x_val(const int& xVal){x_val_ =xVal;}
    void set_y_val(const int& yVal){y_val_ =yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void set_is_move(const bool& isMove){is_move_ =isMove;}
    bool get_is_move() const {return is_move_;}

    void set_buller_dir(const unsigned int& bullerDir){buller_dir_ =bullerDir;}
    int get_buller_dir()const {return buller_dir_;}

    void HandleMove(const int& x_border, const int& y_border);
private:
    int x_val_;
    int y_val_;
    bool is_move_;
    unsigned int buller_dir_;



};


#endif // BULLEROBJECT_H_INCLUDED
