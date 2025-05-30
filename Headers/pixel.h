#pragma once
#include "application.h"
#include "color.h"
#include <cstdint>
#include <vector>
#include <memory>
#include <algorithm>

#include "imgui.h"

#ifndef PIXEL_H
#define PIXEL_H

enum Behaviour 
{
  STATIC,
  DYNAMIC,
  WATER
};

class Pixel
{
public:
  Pixel();
  Pixel(int x, int y, Color col);
  
  SDL_Rect position;
  Color color;
  Behaviour behaviour = DYNAMIC;
  bool moved = true;

  bool CheckCollision(const Pixel& other) const
  {
    if (this == &other) return false;

    SDL_Rect nextPosition = position;
    nextPosition.y += 1;
    return SDL_HasIntersection(&nextPosition, &other.position);
  }

  void Update(std::vector<Pixel*>& nearby);
  void Draw();
private:
  SDL_Point lastPosition;
  void Gravity(std::vector<Pixel*>& nearby);
};

#endif
