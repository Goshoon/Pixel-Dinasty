// https://www.youtube.com/watch?v=iUq0waTh9Pw&ab_channel=%E2%98%86111loggedin%2F%2Fxxenaa%E2%99%A1
#include "pixel.h"
#include "cell.h"
Pixel::Pixel()
{}

Pixel::Pixel(int x, int y, Color col)
{
  position.x = x;
  position.y = y;
  color = col;
}

void Pixel::Update(Cell& cell)
{
  switch(behaviour)
  {
    case DYNAMIC:
      if (position.y < WINDOW_HEIGHT / RENDER_SCALE - 1)
      {
        bool canGoDown = true;
        for (int i = 0; i < cell.pixels.size(); i++)
        {
          if (cell.pixels.at(i)->position.y == position.y+1)
            if(cell.pixels.at(i)->position.x == position.x)
              canGoDown = false;
        }

        if (canGoDown)
          position.y += 1;
      }
      break;
  }

  if (!(lastPosition.x == position.x && lastPosition.y == position.y))
  {
    if(!cell.Contains(position))
    {
      moved = true;
      auto it = std::find(cell.pixels.begin(), cell.pixels.end(), this);
      if (it != cell.pixels.end())
      {
        cell.pixels.erase(it);
      }
    }
    else 
    {
      moved = false;
    }
  }
  else
  {
    moved = false;
  }

  lastPosition = position;
}

void Pixel::Draw()
{
  SDL_SetRenderDrawColor(Application::GetInstance().renderer, color.red, color.green, color.blue, color.alpha);
  SDL_RenderDrawPoint(Application::GetInstance().renderer, position.x, position.y);
}
