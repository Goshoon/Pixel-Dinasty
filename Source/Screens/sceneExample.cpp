#include "sceneExample.h"

sceneExample::sceneExample()
{
	std::cout << "Created scenedd!\n";
}

sceneExample::~sceneExample()
{}

void sceneExample::Update()
{
  mbCooldown *= 0.1f;
  Application& app = Application::GetInstance();

  /* Create Pixels */
  if(app.mbLeft && mbCooldown < 1)
  {
    pixels.emplace_back(std::make_shared<Pixel>(app.mPosition.x, app.mPosition.y));
    mbCooldown = 100.0f;
  }

  /* Place Pixels into the right cell */
  for (int i = 0; i < pixels.size(); i++)
  {
    if (pixels.at(i)->position.x < WINDOW_WIDTH/2)
    {
      if(pixels.at(i)->position.y < WINDOW_HEIGHT/2)
      {
        topLeft.emplace_back(pixels.at(i));
      }
      else
      {
        bottomRight.emplace_back(pixels.at(i));
      }
    }
    else
    {
      if(pixels.at(i)->position.y < WINDOW_HEIGHT/2)
      {
        topRight.emplace_back(pixels.at(i));
      }
      else
      {
        bottomRight.emplace_back(pixels.at(i));
      }
    }
  }

  /* Update every pixel entity */
  for (int i = 0; i < topLeft.size(); i++)
    topLeft.at(i)->Update(topLeft);

  for (int i = 0; i < topRight.size(); i++)
    topRight.at(i)->Update(topRight);

  for (int i = 0; i < bottomLeft.size(); i++)
    bottomLeft.at(i)->Update(bottomLeft);

  for (int i = 0; i < bottomRight.size(); i++)
    bottomRight.at(i)->Update(bottomRight);

  /* Clear quadtrees */
  topLeft.clear();
  topRight.clear();
  bottomLeft.clear();
  bottomRight.clear();
}

void sceneExample::Render()
{
  for(int i = 0; i < pixels.size(); i++)
    pixels.at(i)->Draw();
}
