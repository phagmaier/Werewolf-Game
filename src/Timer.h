#ifndef TIMER_H
#define TIMER_H

#include "raylib.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <chrono>

class Timer{
public:
  Timer(int minutes, int seconds, const size_t width, const size_t height) : 
    minutes{minutes}, seconds{seconds},
    totalSeconds{minutes*60+seconds}, 
    start_time{std::chrono::steady_clock::now()},
    x{static_cast<int>(width/2)}, y{static_cast<int>(height/2)},
    done {Rectangle{width/2.0f -100,height-100.0f,350,75}},
    end_game{Rectangle{width/2.0f -100,100,300,75}}

  {}
  bool display_time();
  bool coll_done(Vector2 pos) {return CheckCollisionPointRec(pos,done);}
  bool coll_end(Vector2 pos) {return CheckCollisionPointRec(pos,end_game);}
  void reset(const int minutess, const int secondss);
  void reset();
private:
  //// = std::chrono::steady_clock::now();
  int minutes;
  int seconds;
  int totalSeconds;
  std::chrono::time_point<std::chrono::steady_clock> start_time;
  std::chrono::time_point<std::chrono::steady_clock> now; 
  std::string formatTime(int minutes,int seconds);
  const int fontSize = 50;
  const int x;
  const int y;
  Rectangle done;
  Rectangle end_game;
};

#endif
