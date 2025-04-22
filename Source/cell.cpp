#include "cell.h"

Cell::Cell(int left, int right, int top, int bottom)
{
  leftBound = left;
  rightBound = right;
  topBound = top;
  bottomBound = bottom;
}

bool Cell::Contains(SDL_Point point)
{
  if( point.x >= leftBound // left
     && point.y >= topBound // top 
     && point.x <= rightBound // right 
     && point.y <= bottomBound ) // bottom
    return true;

  return false;
}
