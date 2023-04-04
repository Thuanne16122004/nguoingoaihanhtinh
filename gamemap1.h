#ifndef GAMEMAP1_H_INCLUDED
#define GAMEMAP1_H_INCLUDED

#include"commonfunc.h"
#include"baseobject.h"


#define MAX_TILES 20
class TileMat: public BaseObject
{
public:
    TileMat(){;}
    ~TileMat(){;}
};


class GameMap
{
    public:
    GameMap(){;}
    ~GameMap(){;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return game_map_;};
    void SetMap(Map& map_data){game_map_=map_data;};

private:
    Map game_map_;
    TileMat tile_mat[MAX_TILES];
};

#endif // GAMEMAP1_H_INCLUDED
