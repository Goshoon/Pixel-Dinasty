#pragma once
#include <vector>
#include <SDL2/SDL.h>
#ifndef CELL_H
#define CELL_H

class Pixel;

class Cell
{
public:
  Cell(int left, int right, int top, int bottom);
  SDL_Rect bounds = { 0, 0, 0, 0 };
  int leftBound, rightBound, topBound, bottomBound;
  bool Contains(SDL_Point point);

  std::vector<Pixel*> pixels;
};

#endif
