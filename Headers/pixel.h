#pragma once
#include "application.h"
#include "color.h"
#include "behaviour.h"
#include "collision.h"

#include "imgui.h"

#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>

class Pixel
{
public:
  Pixel();
  Pixel(int x, int y, Color col);
  
  SDL_Rect position;
  Color color;
  Behaviour behaviour = DYNAMIC;
  bool moved = true;

  bool CheckCollision(std::vector<Pixel*>& nearby);
  bool CheckCollision(std::vector<Pixel*>& nearby, int xoffset, int yoffset);

  void Update(std::vector<Pixel*>& nearby);
  void Draw();
private:
  SDL_Point lastPosition;
  void Gravity(std::vector<Pixel*>& nearby);
};
