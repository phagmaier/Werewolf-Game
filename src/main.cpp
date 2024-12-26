#include "raylib.h"
#include "Player.h"
#include "Selector.h"
#include "Timer.h"
#include <iostream>
//WEREWOLF
//

//PROBABLY NOT DONE
void draw_first(bool &display_first, bool &display_second, Player &players, bool &done, int &box, int &coll_time, Selector &selector){
  players.draw_players();
  //players.draw_time();
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    Vector2 pos = GetMousePosition();
    box = players.check_coll(pos);
    //std::cout << box << "\n";
    done= players.check_done_coll(pos);
    coll_time = players.coll_time(pos);
  }

  if (box >= 0){
    players.update_string(box);
  }
  if (coll_time){
    if (coll_time ==1){
      players.update_minutes();
    }
    else{
      players.update_seconds();
    }
  }

  if (done){
    display_first = false;
    display_second = true;
    done = false;
    box = -1;
    selector.add_arr(players.get_names());
  }
}

void draw_second(Selector &selector,bool &display_second, bool &display_third, bool &done,Player &players,Timer &timer){
  //DrawText("SECOND", 190, 200, 20, BLUE);
  selector.display();
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    Vector2 pos = GetMousePosition();
    done = selector.coll_done(pos); 
  }
  if(done){
    //display_first = true;
    display_third = true;
    display_second = false;
    done = false;
    timer.reset(players.get_minutes(),players.get_seconds());
  }
  //display_first = true;
  //display_second = false;
}

void draw_third(bool &done, Timer &timer, bool &display_first){
  bool end_game = false;
  done = timer.display_time(); 
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    Vector2 pos = GetMousePosition();
    //done = selector.coll_done(pos); 
    done = done || timer.coll_done(pos); 
    end_game = timer.coll_end(pos);
  }
  if (done){
    //display_first = true;
    timer.reset();
    done = false;
  }
  if (end_game){
    display_first = true;
    done = false;
  }
}

int main(void){
  bool display_first = true;
  bool display_second  =  false;
  bool done1 = false;
  bool done2 = false;
  int box = -1;
  int col_time1 = 0;
  bool display_third = false;

  
  InitWindow(0, 0, "WEREWOLF");
  const size_t width = GetScreenWidth()/2;
  const size_t height = GetScreenHeight()/2;;
  SetTargetFPS(60); 
  SetWindowSize(width,height);

  //INIT VARIABLES
  Player players = Player(width,height);
  Selector selector = Selector(width, height);
  Timer timer = Timer(1,1,width,height);

  while (!WindowShouldClose()){
    BeginDrawing();

    ClearBackground(RAYWHITE);

    //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    if (display_first){
      draw_first(display_first, display_second, players, done1, box, col_time1,selector);
    }
    else if (display_second){
      //draw_second(selector ,display_second,display_first, done2,players, timer);
      draw_second(selector ,display_second,display_third, done2,players, timer);
    }
    else{
      draw_third(done2, timer, display_first);
    }

    EndDrawing();
  }

  CloseWindow(); 

  return 0;
}
        
