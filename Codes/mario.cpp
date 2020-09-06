#include "mario.h"

mario::mario(Window *_win,my_map* _game_map,double _velocity_x,Point _pos,int _square_side,int _max_jump):
win(_win),game_map(_game_map),velocity_x(_velocity_x),pos(_pos),square_side(_square_side),max_jump(_max_jump){}

void mario::set_coin_and_mushroom(coin* _Coin,mushroom* _Mushroom)
{
  Coin = _Coin;
  Mushroom = _Mushroom;
}

void mario::process_coin()
{
  if(Coin->check == true)
  {
    Coin->increase_counter();
    Coin->increase_pos();
    Coin->check_invisiblity();
  }
}

void mario::reset_mario_position()
{
  for(int i = 0;i < WINDOW_HEIGHT/square_side;i++)
    for(int j = 0;j < WINDOW_WIDTH/square_side;j++)
    {
      if(game_map->current_map[i][j] == 'M')
      {
        pos.x = j * square_side;
        pos.y = i * square_side;
      }
    }
  set_status_standing();
  fall = false;
}

double mario::get_distance_y()
{
  return (velocity_y + GRAVITY/2) * DEFAULT_DELAY / 1000; 
}

string mario::get_type()
{
  return size;
}

void mario::reset_velocity_y()
{
  velocity_y = -VELOCITY_Y;
}

void mario::process_mushroom()
{
  if(Mushroom->check == true)
  {
    Mushroom->increase_counter();
    Mushroom->increase_pos();
    Mushroom->check_invisiblity();
  }
}

void mario::set_velocity_y()
{
  velocity_y = VELOCITY_Y;
}

void mario::sync_camera()
{
  if(pos.x >= WINDOW_WIDTH/2)
  {
    pixel_counter += 1;
    if(pixel_counter > square_side)
    {
      pixel_counter = 0;
      game_map->increase_begin();
      game_map->update_current_map();
    }
  }
}

bool mario::check_retetive(int i,int j,int direction,int side)
{
  return (game_map->current_map[i+direction][j+side] == 'b' || game_map->current_map[i+direction][j+side] == '@'
   || game_map->current_map[i+direction][j+side] == '?' || game_map->current_map[i+direction][j+side] == 'x'
  || game_map->current_map[i+direction][j+side] == '#'|| game_map->current_map[i+direction][j+side] == 'm' 
  || game_map->current_map[i+direction][j+side] == 'h' || game_map->current_map[i+direction][j+side] == '|');
}

bool mario::check_down_crash()
{
  int i = pos.y / square_side;
  int j = pos.x /square_side;
  if(size == "big")
    i++;
  if(check_retetive(i,j+1,ONE,ZERO))
    return true;
  return false;
}



bool mario::check_up_crash()
{
  int i = pos.y / square_side;
  int j = pos.x /square_side;
  if(check_retetive(i,j + 1,ZERO,ZERO))
  {
    char up_char = game_map->current_map[i][j + 1];
    if(up_char == '?')
    {
      Coin->set_pos_coin(i * square_side,(j + 1) * square_side);
      game_map->set_game_map(i,j + 1 + game_map->get_begin(),'x');
      game_map->current_map[i][j+1] = 'x';
      game_map->increase_coins();
    } 
    if(up_char == 'h' || up_char == 'm')
    {
      Mushroom->set_pos_mushroom(i * square_side,(j + 1) * square_side,up_char);
      game_map->set_game_map(i,j + 1 + game_map->get_begin(),'x');
      game_map->current_map[i][j+1] = 'x';
      if(up_char == 'h')
        game_map->increase_lives();
    }
    if(up_char == 'b' && size == "big")
      game_map->destory_brick(i,j);
   
    return true;
  }
  return false;
}

bool mario::check_right_crash()
{
  int i = pos.y / square_side;
  int j = pos.x /square_side;
  if(game_map->current_map[i][j+2] == 'f')
  {
    winer = true;
    return true;
  }   
  if(check_retetive(i,j+1,ZERO,ONE))
    return true;
  return false;  
}

bool mario::check_left_crash()
{
  int i = pos.y / square_side;
  int j = pos.x /square_side;
  if(check_retetive(i,j+1,ZERO,-ONE))
    return true;
  return false;  
}

void mario::func_delay(int i)
{
  if(i == 0)
    return;
  func_delay(i-1);
}

void mario::set_position_y_x(int before_jump,int specefier_befor)
{
  if(before_jump - pos.y >= max_jump || check_up_crash() || pos.y <= 0)
    set_velocity_y();
  func_delay(10000);
  if(check_down_crash() && velocity_y != -VELOCITY_Y)
  {
    reset_velocity_y();
    throw "finish";
  }
  pos.y += 1.5 * get_distance_y();
  process_coin();
  process_mushroom();
  if(pos.y > WINDOW_HEIGHT - 2 * square_side)
    throw "reset";
  if(last_event == WALKING_RIGHT1 && specefier_befor > 0 && !check_right_crash())
  {
    sync_camera();
    if(pos.x < WINDOW_WIDTH/2)
      pos.x += 1;
  }
  else if(last_event == WALKING_LEFT1 && specefier_befor > 0 && pos.x>0 && !check_left_crash())
    pos.x -= 1;
}

void mario::process_jump()
{
  Point tempetur(20,20);
  int before_jump = pos.y;
  int specefier_befor = specefier1;
  pos.y--;
  win->play_sound_effect("assets/sounds/sound_effects/jump-super.wav");
  while(true)
  {
    process_event(win->poll_for_event(),tempetur,ZERO);
    set_position_y_x(before_jump,specefier_befor);
    update_velocity_y();
    jump_status();
    game_map->sync_mushroom();
    game_map->show_current_map(get_pixel_counter());
    win->update_screen();
  }
}

void mario::jump()
{
  try
  {
    process_jump();
    
  }
  catch(const char* exeption)
  {
    if(exeption == "finish")
    {
      game_map->show_current_map(get_pixel_counter());
      win->update_screen();
    }
    else if(exeption == "reset")
      throw;
  }
}

double mario::get_pixel_counter()
{
  return pixel_counter;
}

void mario::set_status_standing()
{
  if(status % 2 == 0)
    status = STANDING_RIGHT;
  else
    status = STANDING_LEFT;
}

void mario::reset_specefier()
{
  specefier = 0;
}

double mario::get_velocity_x()
{
  return velocity_x;
}

void mario::set_status_right()
{
  if(specefier%3 == 1)
    status = WALKING_RIGHT1;
  else if(specefier%3 == 2)
    status = WALKING_RIGHT2;
  else
    status = WALKING_RIGHT3;
  last_event = WALKING_RIGHT1;
}

void mario::set_status_left()
{
  if(specefier%3 == 1)
    status = WALKING_LEFT1;
  else if(specefier%3 == 2)
    status = WALKING_LEFT2;
  else
    status = WALKING_LEFT3;
  last_event = WALKING_LEFT1;
}

void mario::set_status_jump(int side)
{
  if(side)
    status = JUMPING_RIGHT;
  else
    status = JUMPING_LEFT;
}

int mario::get_status()
{
  return status;
}

void mario::update_velocity_y()
{
  velocity_y += GRAVITY  / 100;
}

void mario::change_size(int checking)
{
  if(checking)
  { 
    size = "big";
    pos.y -= square_side;
  }
  else
  {
    size = "normal";
    pos.y += square_side;
  }
}

void mario::set_status(int side)
{
  specefier++;
  specefier1 = SPECEFIER_FOR_JUMP;
  if(side)
    set_status_right();
  else
    set_status_left();
}

void mario::draw_mario()
{
  if(size == "normal")
    height = square_side;
  else
    height = 2 * square_side;
  string folder = "assets/sprites/mario/" ;
  switch(status)
  {
    case STANDING_RIGHT:
      win->draw_img(folder + size + "/standing-right.png",Rectangle(pos,square_side,height));
    break;
    case WALKING_RIGHT1:
      win->draw_img(folder + size + "/walking-right-1.png",Rectangle(pos,square_side,height));
    break;
    case WALKING_RIGHT2:
      win->draw_img(folder + size + "/walking-right-2.png",Rectangle(pos,square_side,height));
    break;
    case WALKING_RIGHT3:
      win->draw_img(folder + size + "/walking-right-3.png",Rectangle(pos,square_side,height));
    break;
    case STANDING_LEFT:
      win->draw_img(folder + size + "/standing-left.png",Rectangle(pos,square_side,height));
    break;
    case WALKING_LEFT1:
      win->draw_img(folder + size + "/walking-left-1.png",Rectangle(pos,square_side,height));
    break;
    case WALKING_LEFT2:
      win->draw_img(folder + size + "/walking-left-2.png",Rectangle(pos,square_side,height));
    break;
    case WALKING_LEFT3:
      win->draw_img(folder + size + "/walking-left-3.png",Rectangle(pos,square_side,height));
    break;
    case JUMPING_RIGHT:
      win->draw_img(folder + size + "/jumping-right.png",Rectangle(pos,square_side,height));
    break;
    case JUMPING_LEFT:
      win->draw_img(folder + size + "/jumping-left.png",Rectangle(pos,square_side,height));
    break;
    case DEAD:
      win->draw_img(folder + size + "/dead.png",Rectangle(pos,square_side,height));   
    break;   
  }
}







void mario::set_position_x(int side)
{
  if(side == ZERO)
    pos -= Point(get_distance_x(),ZERO);
  else
    pos += Point(get_distance_x(),ZERO);
}

double mario::get_distance_x()
{
  return (velocity_x)*DEFAULT_DELAY;
}

void mario::reset_mario_stat()
{
  size = "normal";
  height = square_side;
  pixel_counter = 0;
  specefier = 0;
  win->resume_music();
  reset_mario_position();
}

void mario::move_left()
{
  if(pos.x > 0 && !check_left_crash())
    set_position_x(ZERO);
}

void mario::move_right()
{
  if(pos.x < WINDOW_WIDTH/2 && !check_right_crash())
    set_position_x(ONE);
  else if(!check_right_crash())
  {
    int square_side = game_map->gain_square_side();
    pixel_counter += 8;
    if(pixel_counter > square_side)
    {
      pixel_counter = 0;
      game_map->increase_begin();
      game_map->update_current_map();
    }
  }
}

bool mario::game_is_not_finished()
{
  if(game_map->get_lives() == 0)
  {
    game_map->show_you_lose();
    return true;
  }
  else if(winer)
  {
    game_map->show_you_win();
    return true;
  }
  return false; 
}

Point mario::get_pos()
{
  return pos;
}

void mario::jump_status()
{
  if(status % 2 == ZERO)
    set_status_jump(ONE);
  else
    set_status_jump(ZERO);
}

void mario::status_standing(Point temp)
{
  if(temp.x == pos.x && temp.y == pos.y)
  {
    set_status_standing();
    reset_specefier();
  }
}

void mario::process_falling()
{
  pos.y += 8;
  fall = true;
  if(pos.y >= WINDOW_HEIGHT - height)
    throw "reset";
  jump_status();
  if(specefier1 > 0 && last_event == WALKING_RIGHT1)
    pos.x += 3;
  else if(specefier1 > 0 && last_event == WALKING_LEFT1)
    pos.x -= 3;
  if(check_down_crash())
  {
    pos.y -= 5;
    fall = false;
    set_status_standing();
  }
}

void mario::process_event(const Event &event,Point &temp,int w_processing) 
{
  switch(event.get_type())
  {
    case Event::QUIT:
      exit(ZERO);
    case Event::KEY_PRESS:
      if(event.get_pressed_key() == 'd' && !fall)
      {
        move_right();
        set_status(ONE);
        temp = get_pos();
      }
      else if(event.get_pressed_key() == 'a' && !fall)
      {
        move_left();
        set_status(ZERO);
        temp = get_pos();
      } 
      else if(event.get_pressed_key() == 'w' && w_processing && !fall)
      {
        try {
          jump();
          set_status_standing();
        } catch(const char* reset) {
          throw;
        }
      }
      else if(event.get_pressed_key() == 'e')
        exit(ZERO);
    break;
    default:
      if(w_processing && !check_down_crash())
        process_falling();
      else if(w_processing)
        status_standing(temp);
      specefier1--;
    break;
  }
}
