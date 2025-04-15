#pragma once
#include "application.h"
#include <cstdint>
#include <vector>
#include <memory>

typedef uint8_t u8;

enum Behaviour 
{
  STATIC,
  DYNAMIC
};

struct Color
{
  u8 red;
  u8 green;
  u8 blue;
  u8 alpha;
};

class Pixel
{
public:
  Pixel();
  Pixel(int x, int y);
  
  SDL_Point position;
  Color color;
  Behaviour behaviour = DYNAMIC;

  void Update(std::vector<std::shared_ptr<Pixel>>& cell);
  void Draw();
};
