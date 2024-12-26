#include "raylib.h"
#include "Player.h"
#include "Selector.h"
#include <iostream>
//WEREWOLF
//

//PROBABLY NOT DONE
void draw_first(bool &display_first, bool &display_second, Player &players, bool &done, int &box, Selector &selector){
  players.draw_players();
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    Vector2 pos = GetMousePosition();
    box = players.check_coll(pos);
    //std::cout << box << "\n";
    done= players.check_done_coll(pos);
  }

  if (box >= 0){
    players.update_string(box);
  }

  if (done){
    display_first = false;
    display_second = true;
    done = false;
    box = -1;
    selector.add_arr(players.get_names());
  }
}

void draw_second(Selector &selector,bool &display_second, bool &display_first, bool &done){
  //DrawText("SECOND", 190, 200, 20, BLUE);
  selector.display();
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    Vector2 pos = GetMousePosition();
    done = selector.coll_done(pos); 
  }
  if(done){
    display_first = true;
    display_second = false;
    done = false;

  }
  //display_first = true;
  //display_second = false;
}

int main(void){
  bool display_first = true;
  bool display_second  =  false;
  bool done1 = false;
  bool done2 = false;
  int box = -1;

  
  InitWindow(0, 0, "WEREWOLF");
  const size_t width = GetScreenWidth()/2;
  const size_t height = GetScreenHeight()/2;;
  SetTargetFPS(60); 
  SetWindowSize(width,height);

  //INIT VARIABLES
  Player players = Player(width,height);
  Selector selector = Selector(width, height);

  while (!WindowShouldClose()){
    BeginDrawing();

    ClearBackground(RAYWHITE);

    //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    if (display_first){
      draw_first(display_first, display_second, players, done1, box, selector);
    }
    else if (display_second){
      //draw_second(Selector &selector,bool &display_second, bool &display_first, bool &done){
      draw_second(selector ,display_second,display_first, done2);
    }

    EndDrawing();
  }

  CloseWindow(); 

  return 0;
}
        
