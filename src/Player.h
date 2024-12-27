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
  //return 0 for nothing 1 for left 2 for right
  int coll_time(Vector2 pos);
  void draw_time();
  void update_minutes();
  void update_seconds();
  //literally no idea how they got flipped or how to fix
  inline int get_minutes(){return seconds.size() > 0 ? std::stoi(seconds) : 0;}
  inline int get_seconds(){return minutes.size() > 0 ? std::stoi(minutes) : 0;};
  inline bool time_valid(){return get_seconds() <60 && (get_seconds() || get_minutes());}
private:
  Rectangle recs[10];
  std::string strings[10];
  Rectangle done;
  bool on_left;
  bool on_right;
  Rectangle left_time;
  Rectangle right_time;
  std::string minutes;
  std::string seconds;
  Vector2 GetCenteredTextPosition(const Rectangle rec, const std::string &text, const size_t fontSize);
  void drawFooter();
  bool valid_done();
  //bool is_sixity(char c);
  //bool is_ten(std::string &str);
  };

#endif
