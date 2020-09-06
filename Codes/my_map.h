#ifndef MY_MAP
#define MY_MAP
#include "rsdl.hpp"
#include "mario.h"
#include "coin.h"
#include "mushroom.h"
#include "defines.h"
#include "goomba.h"
#include <vector>
#include <fstream>
using namespace std;

class coin;

class mario;

class mushroom;

class goomba;

class my_map
{
  public:
    my_map(string _file_name,Window* _win);
    void read_map();
    Point get_mario_pos();
    vector<string> get_map();
    int gain_square_side();
    void show_current_map(double pixel_counter);
    void update_current_map();
    void set_mario(mario* _super_mario);
    void increase_begin();
    void sync_goomba(goomba* Goomba);
    void check_goombas();
    void reset_map();
    void set_game_map(int i,int j,char temp);
    int get_begin();
    char** current_map;
    void bright_brick();
    void smash_brick(int i,int j);
    void set_coin_and_mushroom(coin* _Coin,mushroom* _Mushroom);
    void destory_brick(int i,int j);
    void show_status();
    void increase_coins();
    void increase_lives();
    int get_lives();
    void sync_mushroom();
    void set_goombas();
    void draw_stat_map(int i,int j,double width,int height,double replace);
    void show_you_lose();
    void show_you_win();
  private:
    string file_name;
    vector<string> map;
    Window* win;
    int specefier_question = 1;
    int n = 0;
    mario*  super_mario;
    int begin = 0;
    int coins = 0;
    coin* Coin;
    vector<goomba> goombas;
    int check = 10;
    mushroom* Mushroom;
    int lives = DEFAULT_LIVES;
};


#endif
