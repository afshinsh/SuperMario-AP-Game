#include "game.h"

using namespace std;

int main(int argc,char* argv[])
{
  Window win(WINDOW_WIDTH,WINDOW_HEIGHT,"Super Mario!");
  win.play_music("assets/sounds/game_music.ogg");
  my_map game_map(argv[ONE],&win);
  game_map.read_map();
  int square_side = game_map.gain_square_side();
  mario super_mario(&win,&game_map,VELOCITY_X,game_map.get_mario_pos(),square_side,5 * square_side);
  game_map.set_mario(&super_mario);
  game_map.update_current_map();
  Point temp(0,0);
  coin Coin(&win,square_side,&super_mario);
  mushroom Mushroom(&win,square_side,&game_map,&super_mario);
  super_mario.set_coin_and_mushroom(&Coin,&Mushroom);
  game_map.set_coin_and_mushroom(&Coin,&Mushroom);
  while(!super_mario.game_is_not_finished())
  {
    try {
      game_map.show_current_map(super_mario.get_pixel_counter());
      super_mario.process_event(win.poll_for_event(),temp,ONE);
      game_map.sync_mushroom();
      //game_map.set_goombas();
      //game_map.check_goombas();
      win.update_screen();
      delay(DEFAULT_DELAY);
    } catch(const char* reset) {  
      game_map.reset_map();
      super_mario.reset_mario_stat();
    }
  }
}