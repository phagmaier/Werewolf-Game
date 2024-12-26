#ifndef SELECTOR_H
#define SELECTOR_H
#include "raylib.h"
#include <random>
#include <vector>
#include <string>
#include <algorithm>

class Selector{
public:
  Selector(const size_t width, const size_t height);
  void display();
  inline bool coll_done(Vector2 pos){return CheckCollisionPointRec(pos,done);}
  void add_arr(std::string *strs);
private:
  std::string names[3];
  Rectangle recs[3];
  Rectangle done;
  Vector2 GetCenteredTextPosition(const Rectangle rec, const std::string &text, const size_t fontSize);
};

#endif
