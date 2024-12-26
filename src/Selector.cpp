#include "Selector.h"

void Selector::add_arr(std::string *strs){
  //std::vector<std::string> tmp;

  std::string roles[3];
  std::vector<std::string> tmp;
  for (int i=0;i<10;++i){
    if (strs[i].size()){
      tmp.push_back(strs[i]);
    }
  }

  roles[0] = "WEREWOLF";
  roles[1] = "SEER";
  roles[2] = "DOCTOR";
  
  std::random_device rd;
  std::mt19937 rng(rd()); // Create a random number generator

  std::shuffle(tmp.begin(), tmp.end(), rng);

  for (int i=0;i<3;++i){
    names[i] = roles[i] + ":\t" + tmp[i];
  }
}

Selector::Selector(const size_t width, const size_t height){
  
  const int bottom = 150;
  const int padding = 20;

  // Calculate available height for the three rectangles (minus padding and bottom margin)
  const float total_rec_height = height - bottom - 4 * padding; // 4 paddings: top + between rects + bottom
  const float rec_height = total_rec_height / 3; // Divide evenly among the three rectangles
  const float rec_width = width - 2 * padding; // Full width minus left and right padding

  // Create the rectangles
  for (int i = 0; i < 3; ++i) {
    float y = padding + i * (rec_height + padding); // Start with top padding and add cumulative height
    recs[i] = Rectangle{padding, y, rec_width, rec_height};
  }

  // Create the 'done' rectangle
  const float done_width = 175;
  const float done_height = 100;
  const float done_x = (width - done_width) / 2; // Centered horizontally
  const float done_y = height - bottom + (bottom - done_height) / 2; // Centered within the bottom margin
  done = Rectangle{done_x, done_y, done_width, done_height};
}

void Selector::display(){
  const static std::string done_str = "DONE";
  static const size_t fontSize = 50;
  for (int i=0;i<3;++i){
    DrawRectangleRec(recs[i], LIGHTGRAY); 
    DrawRectangleLinesEx(recs[i],1,BLACK);
    Vector2 pos = GetCenteredTextPosition(recs[i], names[i],fontSize);
    DrawText(names[i].c_str(),pos.x,pos.y,fontSize,RED);
  }
  DrawRectangleRec(done, LIGHTGRAY); 
  DrawRectangleLinesEx(done,1,BLACK);
  Vector2 pos = GetCenteredTextPosition(done, done_str,fontSize);
  DrawText(done_str.c_str(),pos.x,pos.y,fontSize,BLUE);

}


Vector2 Selector::GetCenteredTextPosition(const Rectangle rec, const std::string &text, const size_t fontSize){
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
