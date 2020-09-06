#include "goomba.h"

using namespace std;

goomba::goomba(Window* _win,int _square_side,my_map* _game_map,mario* _super_mario)
{
  win = _win;
  square_side = _square_side;
  game_map = _game_map;
  super_mario = _super_mario;
}

bool goomba::check_up_crash()
{
  int i = pos_y / square_side;
  int j = pos_x /square_side;
  if(check_retetive(i,j + 1,ZERO,ZERO))
    return true;
  return false;
}

bool goomba::change_visibelity(int checking)
{
  visible = checking;
  counter = 5;
}

bool goomba::get_vx()
{
  return vx;
}

void goomba::fall()
{
  while(!check_down_crash())
    pos_y += 2;
  if(pos_y >= WINDOW_HEIGHT - 2 || pos_x <= 2)
    throw ZERO;
}

void goomba::decrease_pos_x()
{
  pos_x -= 2;
}

void goomba::destory()
{
  check = false;
  vx = true;
}

void goomba::set_vx()
{
  vx = !vx;
  if(vx)
    pos_x += square_side + 1;
  else 
    pos_x -= square_side + 1;
}

void goomba::update_pos_x(int i)
{
  if(vx)
    pos_x += i;
  else 
    pos_x -= i;
}

void goomba::set_pos_goomba(int i,int j)
{
  check = true;
  pos_x = j;
  pos_y = i;
}

bool goomba::crash_mario()
{
  counter--;
  if(abs(pos_x - super_mario->get_pos().x) <= square_side && pos_y >= super_mario->get_pos().y - 3 &&
  pos_y <= super_mario->get_pos().y && visible)
  {
    if(super_mario->get_type() == "normal")
    {
      super_mario->set_stat(DEAD);
      super_mario->draw_mario();
      throw "restart";
    }
    else
    {
      super_mario->change_size(ZERO);
      change_visibelity(ZERO);
    }
  }
  else if(abs(pos_x - super_mario->get_pos().x) < square_side && visible && super_mario->get_pos().y <= pos_y && super_mario->get_pos().y - pos_y <= square_side)
  {
    win->play_sound_effect("assets/sounds/sound_effects/enemy-stomp.wav");
    win->clear();
    game_map->show_current_map(super_mario->get_pixel_counter());
    win->draw_img("assets/sprites/enemies/little_goomba/dead.png");
    return true;
  }
  if(counter == ZERO)
    change_visibelity(ONE);
  return false;
}

bool goomba::check_retetive(int i,int j,int direction,int side) 
{
  return (game_map->current_map[i+direction][j+side] == 'b' || game_map->current_map[i+direction][j+side] == '@'
   || game_map->current_map[i+direction][j+side] == '?' || game_map->current_map[i+direction][j+side] == 'x'
  || game_map->current_map[i+direction][j+side] == '#' || game_map->current_map[i+direction][j+side] == 'm' 
  || game_map->current_map[i+direction][j+side] == 'h' || game_map->current_map[i+direction][j+side] == '|');
}

bool goomba::check_down_crash()
{
  if(pos_y > WINDOW_HEIGHT - 2 * square_side)
    throw ZERO;
  int i = pos_y / square_side;
  int j = pos_x /square_side;
  if(check_retetive(i,j+1,ONE,ZERO))
    return true;
  return false;
}

bool goomba::check_right_crash()
{
  cout<<"line143\n";
  cout<<"pos_y "<<pos_y<<endl;
  int i = pos_y / square_side;
  cout<<"line318\n";
  int j = pos_x /square_side;
  if(check_retetive(i,j,ZERO,ONE))
    return true;
  return false;  
}

bool goomba::check_left_crash()
{
  int i = pos_y / square_side;
  int j = pos_x /square_side;
  if(check_retetive(i,j+1,ZERO,-ONE))
    return true;
  return false;  
}

void goomba::draw()
{
  if(counter % 2)
    win->draw_img("assets/sprites/enemies/little_goomba/walking-1.png",Rectangle(pos_x,pos_y,square_side,square_side));
  else
    win->draw_img("assets/sprites/enemies/little_goomba/walking-2.png",Rectangle(pos_x,pos_y,square_side,square_side));
}
