#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include <iostream>
#include <string>

class Player{
public:
  Player(const size_t width, const size_t height);
  void draw_players();
  void update_string(const size_t pos);
  size_t check_coll(const Vector2 pos);
  inline bool check_done_coll(const Vector2 pos){return CheckCollisionPointRec(pos,done) ? valid_done() : false;}
  std::string *get_names(){return strings;}
private:
  Rectangle recs[10];
  std::string strings[10];
  Vector2 GetCenteredTextPosition(const Rectangle rec, const std::string &text, const size_t fontSize);
  Rectangle done;
  void drawFooter();
  bool valid_done();
};

#endif
