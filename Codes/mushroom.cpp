#include "mushroom.h"

mushroom::mushroom(Window* _win,int _square_side,my_map* _game_map,mario* _super_mario)
{
  win = _win;
  square_side = _square_side;
  game_map = _game_map;
  super_mario = _super_mario;
}

bool mushroom::get_vx()
{
  return vx;
}

void mushroom::decrease_pos_x()
{
  pos_x -= 2;
}

void mushroom::destory()
{
  main_check = false;
  check = false;
  fall_check = false;
  vx = true;
}

void mushroom::set_vx()
{
  vx = !vx;
  if(vx)
    pos_x += square_side + 1;
  else 
    pos_x -= square_side + 1;
}

void mushroom::increase_pos_y()
{
  pos_y += 5;
}

void mushroom::update_pos_x(int i)
{
  if(vx)
    pos_x += i;
  else 
    pos_x -= i;
}

void mushroom::set_pos_mushroom(int i,int j,char _type)
{
  if(_type == 'h')
    type = "health";
  else 
    type = "red";
  win->play_sound_effect("assets/sounds/sound_effects/powerup-appears.wav");
  check = true;
  pos_x = j - square_side;
  pos_y = i;
  pos_y_copy = i;
}

bool mushroom::crash_mario()
{
  if(abs(pos_x - super_mario->get_pos().x) <= square_side
     && abs(pos_y - super_mario->get_pos().y) <= square_side )
  {
    if(type == "red")
      super_mario->change_size(ONE);
    win->play_sound_effect("assets/sounds/sound_effects/powerup.wav");
    return true;
  }
    
  return false;
}

bool mushroom::check_retetive(int i,int j,int direction,int side) 
{
  return (game_map->current_map[i+direction][j+side] == 'b' || game_map->current_map[i+direction][j+side] == '@'
   || game_map->current_map[i+direction][j+side] == '?' || game_map->current_map[i+direction][j+side] == 'x'
  || game_map->current_map[i+direction][j+side] == '#' || game_map->current_map[i+direction][j+side] == 'm' 
  || game_map->current_map[i+direction][j+side] == 'h' || game_map->current_map[i+direction][j+side] == '|');
}

bool mushroom::check_down_crash()
{
  if(pos_y > WINDOW_HEIGHT - 2 * square_side)
    destory();
  int i = pos_y / square_side;
  int j = pos_x /square_side;
  if(check_retetive(i,j+1,ONE,ZERO))
    return true;
  return false;
}

bool mushroom::check_right_crash()
{
  int i = pos_y / square_side;
  int j = pos_x /square_side;
  if(check_retetive(i,j,ZERO,ONE))
    return true;
  return false;  
}

bool mushroom::check_left_crash()
{
  int i = pos_y / square_side;
  int j = pos_x /square_side;
  if(check_retetive(i,j+1,ZERO,-ONE))
    return true;
  return false;  
}

void mario::set_stat(int stat)
{
  status = stat;
}

void mushroom::draw()
{
  if(check || main_check)
    win->draw_img("assets/sprites/objects/mushroom/" + type +".png",Rectangle(pos_x,pos_y,square_side,square_side));
}

void mushroom::increase_counter()
{
  square_side_counter += 2;
}

void mushroom::check_invisiblity()
{
  if(square_side_counter >= square_side )
  {
    check = false;
    main_check = true;
    delay(50);
    square_side_counter = 0;
  }
}

void mushroom::increase_pos()
{
  pos_y -= 2;
}

int mushroom::get_pos_x()
{
  return pos_x;
}

int mushroom::get_pos_y_copy()
{
  return pos_y_copy;
}




my_map::my_map(string _file_name,Window* _win)
{
  file_name = _file_name;
  win = _win;
}
