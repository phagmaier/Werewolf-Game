#include "Player.h"

Player::Player(const size_t width, const size_t height){
  const size_t rows = 2;
  const size_t cols = 5;
  const size_t w_padding = 20;
  const size_t h_padding = 20;
  const size_t start_x = w_padding;
  const size_t start_y = 100;
  const size_t bottom_margin = 150; // Additional space at the bottom

  // Adjust available space for rectangles to include padding on the edges
  const float rec_width = (width - start_x - w_padding * (cols + 1)) / cols;
  const float rec_height = (height - start_y - h_padding * (rows + 1) - bottom_margin) / rows;

  size_t count = 0;
  for (size_t row = 0; row < rows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      float x = start_x + w_padding + col * (rec_width + w_padding);
      float y = start_y + h_padding + row * (rec_height + h_padding);
      recs[count] = Rectangle{x, y, rec_width, rec_height};
      strings[count] = "";
      ++count;
    }


  }
  
  const float done_x = width/2;
  const float upper_bound = recs[9].y + recs[9].height;
  const float y = height - (height - upper_bound)/2;
  const float done_width = 150;
  const float done_height = 60;
  done = Rectangle{done_x, y, done_width, done_height};

  //NEW FOR TIMER
  on_left = false;
  on_right = false;
  left_time = Rectangle{done.x - 100,done.y,50,50};
  right_time = Rectangle{left_time.x+left_time.width - 100,done.y,50,50};
  minutes = "";
  seconds = "";
}

Vector2 Player::GetCenteredTextPosition(const Rectangle rec, const std::string &text, const size_t fontSize){
  const static float spacing = 1.0f;
  //const static size_t fontSize = 30;
  int textWidth = MeasureTextEx(GetFontDefault(), text.c_str(), fontSize, spacing).x;
  int textHeight = MeasureTextEx(GetFontDefault(), text.c_str(), fontSize, spacing).y;

  Vector2 position = {
    rec.x + (rec.width - textWidth) / 2.0f,
    rec.y + (rec.height - textHeight) / 2.0f
  };

  return position;
}

void Player::draw_players(){
  static const size_t fontSize=30;
  static const size_t num_players = 10;
  static const size_t line_width= 1;

  static const Color fill_color = LIGHTGRAY;
  static const Color line_color = BLACK;

  for (size_t i=0;i<num_players;++i){
    DrawRectangleRec(recs[i],fill_color);
    DrawRectangleLinesEx(recs[i],line_width,line_color);
    if (strings[i].size()){
      Vector2 pos = GetCenteredTextPosition(recs[i],strings[i], fontSize);
      DrawText(strings[i].c_str(),pos.x,pos.y,fontSize,BLACK);
    }
  }
  drawFooter();
  draw_time();
}

void Player::drawFooter(){
  static const size_t fontSize=40;
  static const std::string str = "DONE";
  static const size_t fontSize2 = 50;  
  static const std::string str2 = "ENTER PLAYER NAMES";
  DrawRectangleRec(done,LIGHTGRAY);
  DrawRectangleLinesEx(done,1,BLACK);
  Vector2 pos = GetCenteredTextPosition(done,str,fontSize);
  DrawText(str.c_str(),pos.x,pos.y,fontSize,RED);
  
  DrawText(str2.c_str(),pos.x-250,fontSize2,fontSize2,BLUE);
}

size_t Player::check_coll(const Vector2 pos){
  size_t count = 0;
  const static size_t num_recs = 10;
  for (size_t i=0; i<num_recs;++i){
    if (CheckCollisionPointRec(pos,recs[i])){
      return count;
    }
    ++count; 
  }
  return -1;
}

bool Player::valid_done(){
  size_t count = 0;
  for (size_t i=0;i<10;++i){
    if (strings[i].size()){
      ++count;
    }
  }
  return count >=5 && time_valid();
}

void Player::update_string(const size_t pos){
  std::string *str = &strings[pos];
  int key = GetCharPressed();

  // Handle backspace
  if (IsKeyPressed(KEY_BACKSPACE) && str->length() > 0) {
    str->pop_back();
  }
  
  while (key > 0 && str->size()<10) {
    *str += (char)key;
    key = GetCharPressed(); 
  }
}

//return 0 for nothing 1 for left 2 for right
int Player::coll_time(Vector2 pos){
  int result = 0;
  if (CheckCollisionPointRec(pos,left_time)){
    result = 1;
  }
  else if (CheckCollisionPointRec(pos,right_time)){
    result = 2;
  }
  return result;
}

void Player::draw_time() {
  // Concatenate the minutes and colon properly
  
  // Draw the left time rectangle (for minutes and colon)
  DrawRectangleRec(left_time, LIGHTGRAY);  
  DrawRectangleLinesEx(left_time, 1, BLACK);
  
  // Adjust text position to be centered inside the left_time rectangle
  std::string str = minutes.size() ? minutes.c_str() : "00";
  if (str.size()==1){
    str.push_back('0');
  }
  //Vector2 minutes_pos = GetCenteredTextPosition(left_time, minutes, 30);
  //DrawText(str.c_str(), minutes_pos.x-20, minutes_pos.y-10, 30, BLUE);
  DrawText(str.c_str(), left_time.x+5, left_time.y+10, 30, BLUE);
  
  // Draw the right time rectangle (for seconds)
  DrawRectangleRec(right_time, LIGHTGRAY);  
  DrawRectangleLinesEx(right_time, 1, BLACK);
  
  // Adjust text position to be centered inside the right_time rectangle
  str = seconds.size() ? seconds.c_str() : "00";
  if (str.size()==1){
    str.push_back('0');
  }
  //Vector2 seconds_pos = GetCenteredTextPosition(right_time, seconds, 30);

  //DrawText(str.c_str(), seconds_pos.x-20, seconds_pos.y-10, 30, BLUE);
  DrawText(str.c_str(), right_time.x+5, right_time.y+10, 30, BLUE);


  DrawText("TIME:", left_time.x-170, left_time.y+10,30,BLUE);
}


void Player::update_minutes() {
  int key = GetCharPressed();

  // Handle backspace
  if (IsKeyPressed(KEY_BACKSPACE) && minutes.size()) {
    minutes.pop_back();
  }

  // Handle digit key press
  if (key >= KEY_ZERO && key <= KEY_NINE && minutes.size() < 2) {
    minutes.push_back((char)key);
  }
}

void Player::update_seconds() {
  int key = GetCharPressed();

  // Handle backspace
  if (IsKeyPressed(KEY_BACKSPACE) && seconds.size()) {
    seconds.pop_back(); 
  }

  // Handle digit key press
  if (key >= KEY_ZERO && key <= KEY_NINE && seconds.size() < 2) {
    seconds.push_back((char)key); 
  }
}

