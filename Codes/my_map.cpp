#include "my_map.h"

void my_map::sync_mushroom()
{
  if(Mushroom->main_check && !Mushroom->fall_check)
  {
    if(!Mushroom->check_down_crash())
      Mushroom->fall_check = true;
    if(Mushroom->check_right_crash() || Mushroom->check_left_crash())
      Mushroom->set_vx();
    if(Mushroom->check_down_crash() && super_mario->get_pos().x >= WINDOW_WIDTH/2 && (super_mario->get_status() == WALKING_RIGHT1 || super_mario->get_status() == WALKING_RIGHT2) && Mushroom->get_vx())
      Mushroom->update_pos_x(-1);
    else if(Mushroom->check_down_crash() && super_mario->get_pos().x >= WINDOW_WIDTH/2 && (super_mario->get_status() == WALKING_RIGHT1 || super_mario->get_status() == WALKING_RIGHT2) && !Mushroom->get_vx())
      Mushroom->update_pos_x(2);
    else if(Mushroom->check_down_crash() && ( super_mario->get_status() == ONE || super_mario->get_status() == ZERO) )
      Mushroom->update_pos_x(2);
    else if(Mushroom->check_down_crash() && super_mario->get_pos().x < WINDOW_WIDTH/2)
      Mushroom->update_pos_x(2);
    else if(Mushroom->check_down_crash() && super_mario->get_pos().x >= WINDOW_WIDTH/2 && (super_mario->get_status() == JUMPING_RIGHT) && !Mushroom->get_vx())
      Mushroom->update_pos_x(1);
    else if(Mushroom->check_down_crash() && super_mario->get_pos().x >= WINDOW_WIDTH/2 && (super_mario->get_status() == JUMPING_RIGHT) && Mushroom->get_vx())
      Mushroom->update_pos_x(0);
    if(Mushroom->crash_mario())
      Mushroom->destory();
  }
  else if(Mushroom->fall_check)  
  {
    if(!Mushroom->check_down_crash())
      Mushroom->increase_pos_y();
    if(Mushroom->check_down_crash())
      Mushroom->fall_check = false;
  }
}

void my_map::show_status()
{
  string str_coins = to_string(coins);
  string str_lives = to_string(lives);
  win->draw_rect(Rectangle(170,30,460,2 * gain_square_side()),RGB(100,150,200));
  win->fill_rect(Rectangle(170,30,460,2 * gain_square_side()),RGB(100,120,200));
  win->show_text("COINS",Point(200,32),WHITE);
  win->show_text("LIVES",Point(520,32),WHITE);
  win->show_text(str_coins,Point(230,60),WHITE);
  win->show_text(str_lives,Point(550,60),WHITE);
}

void my_map::increase_coins()
{
  coins++;
}

int my_map::get_begin()
{
  return begin;
}

void my_map::set_goombas()
{
  for(int i = 0;i < map.size();i++)
    for(int j = 0;j < WINDOW_WIDTH/gain_square_side() + 1;j++)
    {
      if(current_map[i][j] == 'l')
      {
        goomba my_goomba(win,gain_square_side(),this,super_mario);
        my_goomba.set_pos_goomba(i * gain_square_side(),j * gain_square_side());
        goombas.push_back(my_goomba);
        current_map[i][j] = '.';
      }
    }
}

void my_map::check_goombas()
{
  for(int i = 0;i < goombas.size();i++)
  {
    try {
      sync_goomba(&goombas[i]);
      goombas[i].draw();
    } catch(int ex) {
      goombas.erase(goombas.begin() + i);
    }
  }
}

void my_map::sync_goomba(goomba* Goomba)
{   
  if(Goomba->check_right_crash() || Goomba->check_left_crash())
    Goomba->set_vx();
  if(Goomba->check_down_crash() && super_mario->get_pos().x >= WINDOW_WIDTH/2 
  && (super_mario->get_status() == WALKING_RIGHT1 || super_mario->get_status() == WALKING_RIGHT2) && Goomba->get_vx())
  {
    Goomba->update_pos_x(-1);
  }
  else if(Goomba->check_down_crash() && super_mario->get_pos().x >= WINDOW_WIDTH/2 
  && (super_mario->get_status() == WALKING_RIGHT1 || super_mario->get_status() == WALKING_RIGHT2) && !Goomba->get_vx())
    Goomba->update_pos_x(2);
  else if(Goomba->check_down_crash() && ( super_mario->get_status() == ONE || super_mario->get_status() == ZERO) )
    Goomba->update_pos_x(2);
  else if(Goomba->check_down_crash() && super_mario->get_pos().x < WINDOW_WIDTH/2)
    Goomba->update_pos_x(2);
  else if(Goomba->check_down_crash() && super_mario->get_pos().x >= WINDOW_WIDTH/2 && (super_mario->get_status() == JUMPING_RIGHT) && !Goomba->get_vx())
    Goomba->update_pos_x(1);
  else if(Goomba->check_down_crash() && super_mario->get_pos().x >= WINDOW_WIDTH/2 && (super_mario->get_status() == JUMPING_RIGHT) && Goomba->get_vx())
    Goomba->update_pos_x(0);
  if(Goomba->crash_mario())
    throw ZERO;
  Goomba->fall();
}

void my_map::bright_brick()
{
  specefier_question++;
  if(specefier_question % 8 == 1)
    n++;
}

void my_map::draw_stat_map(int i,int j,double width,int height,double replace)
{
  string pipe = "assets/sprites/objects/pipe";
  string brick = "assets/sprites/objects/bricks_blocks";
  string flag = "assets/sprites/objects/flag/";
  if(current_map[i][j] == 'b')
    win->draw_img(brick + "/brick.png",Rectangle(replace,height,gain_square_side(),gain_square_side()));
  if(current_map[i][j] == '?'||current_map[i][j] == 'm'||current_map[i][j] == 'h')
    win->draw_img(brick + "/question-" + to_string(n % 3 + 1) + ".png",Rectangle(replace,height,gain_square_side(),gain_square_side()));
  if(current_map[i][j] == 'x')
    win->draw_img(brick + "/question-empty.png",Rectangle(replace,height,gain_square_side(),gain_square_side()));
  if(current_map[i][j] == '@')
    win->draw_img(brick + "/block.png",Rectangle(replace,height,gain_square_side(),gain_square_side()));
  if(current_map[i][j] == '*')
    win->draw_img(brick + "/brick-debris.png",Rectangle(replace,height, gain_square_side(), gain_square_side()));
  if(current_map[i][j] == '#')
    win->draw_img(brick + "/clay.png",Rectangle(replace,height,gain_square_side(),gain_square_side()));
  if(current_map[i][j] == '|' && current_map[i-1][j] == '.' && current_map[i][j+1] == '.') 
    win->draw_img(pipe + "/head-right.png",Rectangle(replace,height,gain_square_side(),gain_square_side()));
  if(current_map[i][j] == '|' && current_map[i-1][j] == '.' && current_map[i][j-1] == '.') 
    win->draw_img(pipe + "/head-left.png",Rectangle(replace,height,gain_square_side(),gain_square_side()));
  if(current_map[i][j] == '|' && current_map[i-1][j] == '|' && current_map[i][j+1] == '|') 
    win->draw_img(pipe + "/left.png",Rectangle(replace,height,gain_square_side(),gain_square_side()));
  if(current_map[i][j] == '|' && current_map[i-1][j] == '|' && current_map[i][j-1] == '|') 
    win->draw_img(pipe + "/right.png",Rectangle(replace,height,gain_square_side(),gain_square_side()));
  if(current_map[i][j] == 'f' && current_map[i-1][j] == 'f')
    win->draw_img(flag + "body.png",Rectangle(replace,height,gain_square_side(),gain_square_side()));
  if(current_map[i][j] == 'f' && current_map[i-1][j] == '.')
    win->draw_img(flag + "head.png",Rectangle(replace,height,gain_square_side(),gain_square_side()));
}



void my_map::smash_brick(int i,int j)
{
  if(current_map[i][j] == '*')
  {
    check--;
    if(check == 0)
    {
      current_map[i][j] = '.';
      check = 10;
    } 
  }
}

void my_map::show_current_map(double pixel_counter)
{
  bright_brick();
  win->clear();
  win->draw_img("assets/background_image.png");
  Coin->draw();
  Mushroom->draw();
  show_status();
  for(int i = 0;i < map.size();i++)
    for(int j = 0;j < WINDOW_WIDTH/gain_square_side()+2;j++)
    {
      double width = j*gain_square_side();
      int height = i*gain_square_side();
      double replace = width - pixel_counter;
      super_mario->draw_mario();
      draw_stat_map(i,j,width,height,replace); 
      smash_brick(i,j);
    }
}

void my_map::show_you_win()
{
  win->pause_music();
  win->play_sound_effect("assets/sounds/sound_effects/level-clear.wav");
  delay(2000);
  win->clear();
  win->show_text("YOU WIN!",Point(200,WINDOW_HEIGHT/2 - 80),WHITE,"FreeSans.ttf",80);
  win->update_screen();
  delay(5000);
}

void my_map::show_you_lose()
{
  win->pause_music();
  win->clear();
  win->play_sound_effect("assets/sounds/sound_effects/gameover.wav");
  win->show_text("YOU LOSE!",Point(200,WINDOW_HEIGHT/2 - 80),WHITE,"FreeSans.ttf",80);
  win->update_screen();
  delay(5000);
}

void my_map::set_game_map(int i,int j,char temp)
{
  map[i][j] = temp;
}

void my_map::destory_brick(int i,int j)
{
  win->play_sound_effect("assets/sounds/sound_effects/brick-smash.wav");
  set_game_map(i,j + 1 + get_begin(),'.');
  current_map[i][j+1] = '*';
}

void my_map::increase_begin()
{
  begin++;
}

int my_map::get_lives()
{
  return lives;
}

void my_map::set_mario(mario* _super_mario)
{
    super_mario = _super_mario; 
}

int my_map::gain_square_side()
{
  return (WINDOW_HEIGHT/(map.size()));
}

void my_map::update_current_map()
{
  char** _current_map = (char**)malloc(map.size()*sizeof(char*));
  for(int i=0;i<map.size();i++)
  {
    int k = 0;
    int size = int(WINDOW_WIDTH/gain_square_side());
    _current_map[i] = (char*)malloc(size*sizeof(char));
    for(int j = begin;j < begin + (WINDOW_WIDTH/gain_square_side()) + 2;j++)
    {
      _current_map[i][k] = map[i][j];
      k++;
    }
  }
  current_map=_current_map;
}

Point my_map::get_mario_pos()
{
  for(int i = 0;i< map.size();i++)
    for(int j = 0;j< map[i].length();j++)
    {
      if(map[i][j] == 'M')
        return Point(j*gain_square_side(),i*gain_square_side());
    }
}

void my_map::set_coin_and_mushroom(coin* _Coin,mushroom* _Mushroom)
{
  Coin = _Coin;
  Mushroom = _Mushroom;
}

vector<string> my_map::get_map()
{
  return map;
}

void my_map::increase_lives()
{
  lives++;
}

void my_map::read_map()
{
  ifstream map_file;
  map_file.open(file_name);
  if(!map_file)
  {
    cout<<"failed to open the file!"<<endl;
    exit(ZERO);
  }
  string line;
  while(getline(map_file,line))
    map.push_back(line);
  map_file.close();
}

void my_map::reset_map()
{
  begin = 0;
  lives--;
  update_current_map();
  goombas.clear();
  win->pause_music();
  win->play_sound_effect("assets/sounds/sound_effects/mario-death.wav");
  delay(2500);
}
