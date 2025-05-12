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

void Pixel::Update(std::vector<Pixel*>& nearby)
{
  switch(behaviour)
  {
    case DYNAMIC:
      Gravity(nearby);
      break;
    case WATER:
      Gravity(nearby);
      break;
  }
}

void Pixel::Draw()
{
  Application& app = Application::GetInstance();
  SDL_SetRenderDrawColor(app.renderer, color.red, color.green, color.blue, color.alpha);
  SDL_RenderDrawRect(app.renderer, &position);
}

void Pixel::Gravity(std::vector<Pixel*>& nearby)
{
  if (position.y < WINDOW_HEIGHT / RENDER_SCALE - 1)
  {
    bool canGoDown = true;

    if (CheckCollision(nearby, 0, 1))
      canGoDown = false;

    if (canGoDown)
    {
      position.y++;
    }
  }
}

/* Collision */
bool Pixel::CheckCollision(std::vector<Pixel*>& nearby)
{
  for(auto& near : nearby)
  {
    if (this == near) continue;

    if (Collide(position, near->position))
      return true;
  }

  return false;
}

bool Pixel::CheckCollision(std::vector<Pixel*>& nearby, int xoffset, int yoffset)
{
  SDL_Rect pos = position;
  pos.x += xoffset;
  pos.y += yoffset;

  for(auto& near : nearby)
  {
    if (this == near) continue;

    if (Collide(pos, near->position))
    {
      return true;
    }
  }

  return false;
}
