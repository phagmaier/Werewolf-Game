#include "Timer.h"

std::string Timer::formatTime(int minutes, int seconds) {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes
        << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    return oss.str();
}

bool Timer::display_time(){
  now = std::chrono::steady_clock::now();
  int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
  int remainingSeconds = totalSeconds - elapsed;

  if (remainingSeconds < 0) remainingSeconds = 0; // Stop at 0

  int minutes = remainingSeconds / 60;
  int seconds = remainingSeconds % 60;

  // Format time as a string
  std::string timeStr = formatTime(minutes, seconds);
  DrawText(timeStr.c_str(), x, y, fontSize,RED);
  DrawRectangleRec(done,LIGHTGRAY);
  DrawRectangleLinesEx(done,1,BLACK);
  DrawText("NEXT ROUND", done.x+5, done.y+12, fontSize,BLUE);

  DrawRectangleRec(end_game,LIGHTGRAY);
  DrawRectangleLinesEx(end_game,1,BLACK);
  DrawText("END GAME", end_game.x+5, end_game.y+12, fontSize,BLUE);
  return remainingSeconds <= 0;
}

void Timer::reset(const int minutess, const int secondss){
  minutes = minutess;
  seconds = secondss;
  totalSeconds = minutes*60+seconds;
  start_time = std::chrono::steady_clock::now();
}

void Timer::reset(){
  totalSeconds = minutes*60+seconds;
  start_time = std::chrono::steady_clock::now();
}
