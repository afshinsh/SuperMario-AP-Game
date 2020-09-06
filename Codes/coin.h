#ifndef COIN
#define COIN
#include "rsdl.hpp"
#include "my_map.h"
#include "mario.h"
#include "defines.h"
using namespace std;

class mario;

class my_map;

class coin
{
  public:
    coin(Window* _win,int _square_side,mario* _super_mario);
    void increase_counter();
    void check_invisiblity();
    void set_pos_coin(int i,int j);
    void increase_pos();
    int get_pos_x();
    int get_pos_y_copy();
    bool check = false;
    void draw();
  private:
    Window* win;
    mario* super_mario;
    int pos_x;
    int pos_y;
    int pos_y_copy;
    int square_side;
    int square_side_counter = 0;
};
#endif
