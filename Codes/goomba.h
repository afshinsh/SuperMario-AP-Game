#ifndef GOOMBA
#define GOOMBA
#include "rsdl.hpp"
#include "my_map.h"
#include "mario.h"
#include "defines.h"
using namespace std;

class mario;

class my_map;

class goomba
{
  public:
    goomba(Window* _win,int _square_side,my_map* _game_map,mario* _super_mario);
    void draw();
    bool check_left_crash();
    bool check_right_crash();
    bool check_retetive(int i,int j,int direction,int side);
    void set_pos_goomba(int i,int j);
    void update_pos_x(int i);
    void fall();
    bool check_down_crash();
    bool check = false;
    void set_vx();
    bool crash_mario();
    void destory();
    bool get_vx();
    bool check_up_crash();
    void decrease_pos_x();
    bool change_visibelity(int checking);
    int counter = 5;
  private:
    Window* win;
    my_map* game_map;
    mario* super_mario;
    int square_side;
    int pos_x;
    int pos_y;
    int pos_y_copy;
    bool vx = false;
    bool visible = true;
};

#endif
