#include "pixel.h"

Pixel::Pixel()
{}

Pixel::Pixel(int x, int y)
{
  position.x = x;
  position.y = y;
  color.red = 28;
  color.green = 96;
  color.blue = 0;
  color.alpha = 255;
}

void Pixel::Update(std::vector<std::shared_ptr<Pixel>>& cell)
{
  switch(behaviour)
  {
    case DYNAMIC:
      if (position.y < WINDOW_HEIGHT / RENDER_SCALE - 1)
      {
        bool canGoDown = true;
        for (int i = 0; i < cell.size(); i++)
        {
          if (cell.at(i)->position.y == position.y+1)
            if(cell.at(i)->position.x == position.x)
              canGoDown = false;
        }

        if (canGoDown)
          position.y += 1;
      }
      break;
  }
}

void Pixel::Draw()
{
  SDL_SetRenderDrawColor(Application::GetInstance().renderer, color.red, color.green, color.blue, color.alpha);
  SDL_RenderDrawPoint(Application::GetInstance().renderer, position.x, position.y);
}
