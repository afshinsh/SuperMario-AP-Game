#include "coin.h"

coin::coin(Window* _win,int _square_side,mario* _super_mario)
{
  win = _win;
  square_side = _square_side;
  super_mario = _super_mario;
}

void coin::draw()
{
  if(check == true)
    win->draw_img("assets/sprites/objects/coin.png",Rectangle(pos_x + square_side / 2,pos_y,square_side,square_side));
}

int coin::get_pos_x()
{
  return pos_x;
}

int coin::get_pos_y_copy()
{
  return pos_y_copy;
}

void coin::increase_pos()
{
  pos_y -= 3;
}

void coin::set_pos_coin(int i,int j)
{
  check = true;
  pos_x = j - square_side;
  pos_y = i;
  pos_y_copy = i;
  win->play_sound_effect("assets/sounds/sound_effects/coin.wav");
}

void coin::check_invisiblity()
{
  if(square_side_counter >= square_side )
  {
    check = false;
    square_side_counter = 0;
  }
}

void coin::increase_counter()
{
  square_side_counter += 2;
}

