#pragma once
#include "application.h"
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>

#include "imgui.h"

#ifndef PIXEL_H
#define PIXEL_H

class Cell;
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
  Pixel(int x, int y, Color col);
  
  SDL_Point position;
  Color color;
  Behaviour behaviour = DYNAMIC;
  bool moved = true;

  void Update(Cell& cell);
  void Draw();
private:
  SDL_Point lastPosition;
};

#endif
