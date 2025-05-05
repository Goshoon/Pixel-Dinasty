// https://www.youtube.com/watch?v=iUq0waTh9Pw&ab_channel=%E2%98%86111loggedin%2F%2Fxxenaa%E2%99%A1
#include "pixel.h"
Pixel::Pixel()
{}

Pixel::Pixel(int x, int y, Color col)
{
  position.x = x;
  position.y = y;
  position.w = 1;
  position.h = 1;
  color = col;
}

void Pixel::Update()
{
  switch(behaviour)
  {
    case DYNAMIC:
      if (position.y < WINDOW_HEIGHT / RENDER_SCALE - 1)
      {
          position.y += 1;
      }
      break;
  }
}

void Pixel::Draw()
{
  SDL_SetRenderDrawColor(app.renderer, color.red, color.green, color.blue, color.alpha);
  SDL_RenderDrawPoint(app.renderer, position.x, position.y);
}
