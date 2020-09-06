#ifndef MARIO
#define MARIO
#include "rsdl.hpp"
#include "my_map.h"
#include "mushroom.h"
#include "coin.h"
#include "defines.h"
using namespace std;

class mushroom;

class coin;

class my_map;

class mario
{
  public:
    mario(Window *_win,my_map* _game_map,double _velocity_x,Point _pos,int _square_side,int _max_jump);
    bool game_is_not_finished();
    Point get_pos();
    void move_right();
    void move_left();
    void jump();
    void set_status_left();
    void set_status_right();
    void reset_mario_stat();
    double get_distance_x();
    void set_position_x(int side);
    void draw_mario();
    void set_status(int side);
    double get_velocity_x();
    void set_status_standing();
    void reset_specefier();
    double get_pixel_counter();
    void set_position_y_x(int before_jump,int specefier_befor);
    void set_status_jump(int side);
    double get_distance_y();
    void update_velocity_y();
    void jump_status();
    void process_event(const Event &event,Point &temp,int w_processing);
    void reset_velocity_y();
    void status_standing(Point temp);
    void set_velocity_y();
    void process_jump();
    void sync_camera();
    bool check_down_crash();
    bool check_up_crash();
    bool check_right_crash();
    bool check_left_crash();
    bool check_retetive(int i,int j,int direction,int side);
    void func_delay(int i);
    void process_falling();
    void reset_mario_position();
    void set_coin_and_mushroom(coin* _Coin,mushroom* _Mushroom);
    void process_coin();
    void process_mushroom();
    void change_size(int checking);
    int get_status();
    void set_stat(int stat);
    string get_type();
  private:
    Window *win;
    int square_side;
    bool winer = false;
    Point pos;
    bool fall = false;
    bool is_dead = false;
    int status = STANDING_RIGHT;
    int max_jump;
    double velocity_x;
    int specefier = 0;
    int specefier1;
    int height;
    coin* Coin;
    mushroom* Mushroom;
    string size = "normal";
    my_map* game_map;
    double pixel_counter = 0;
    double velocity_y = -VELOCITY_Y;
    int last_event;
};
#endif
