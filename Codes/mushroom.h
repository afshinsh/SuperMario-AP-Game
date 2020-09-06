#ifndef MUSHROOM
#define MUSHROOM
#include "rsdl.hpp"
#include "my_map.h"
#include "mario.h"
#include "defines.h"
using namespace std;

class mario;

class my_map;

class mushroom
{
  public:
    mushroom(Window* _win,int _square_side,my_map* _game_map,mario* _super_mario);
    void process_mushroom();
    void increase_pos();
    void increase_counter();
    void check_invisiblity();
    bool check_down_crash();
    bool main_check = false;
    bool crash_mario();
    int get_pos_x();
    int get_pos_y_copy();
    void draw();
    bool check = false;
    bool check_left_crash();
    bool check_right_crash();
    bool check_retetive(int i,int j,int direction,int side);
    bool fall_check = false;
    void set_pos_mushroom(int i,int j,char _type);
    void update_pos_x(int i);
    void set_vx();
    void destory();
    void increase_pos_y();
    bool get_vx();
    void decrease_pos_x();
  private:
    Window* win;
    my_map* game_map;
    mario* super_mario;
    int square_side;
    string type;
    int pos_x;
    int pos_y;
    int pos_y_copy;
    bool vx = true;
    int square_side_counter = 0;
};

#endif
