#include "sceneExample.h"

sceneExample::sceneExample()
{
	std::cout << "Created scenedd!\n";
}

sceneExample::~sceneExample()
{
  for(int i = 0; i < pixels.size(); i++)
  {
    delete pixels.at(i);
  }
}

void sceneExample::Update()
{
  mbCooldown *= 0.1f;

  /* Create Pixels */
  if(app.mbLeft && mbCooldown < 1)
  {
    if (!ImGui::GetIO().WantCaptureMouse)
    {
      if (topLeft.Contains(app.mPosition))
        mCell = &topLeft;
      if (topRight.Contains(app.mPosition))
        mCell = &topRight;
      if (bottomLeft.Contains(app.mPosition))
        mCell = &bottomLeft;
      if (bottomRight.Contains(app.mPosition))
        mCell = &bottomRight;

      Color col;
      col.red = static_cast<int>(color.x * 255.0f);
      col.green = static_cast<int>(color.y * 255.0f);
      col.blue = static_cast<int>(color.z * 255.0f);
      col.alpha = static_cast<int>(color.w * 255.0f);

      bool canSpawn = true;
      for(int i = 0; i < mCell->pixels.size(); i++)
      {
        if(mCell->pixels.at(i)->position.x == app.mPosition.x && mCell->pixels.at(i)->position.y == app.mPosition.y)
          canSpawn = false;
      }

      if (canSpawn)
      {
        pixels.emplace_back(new Pixel(app.mPosition.x, app.mPosition.y, col));
        mbCooldown = 100.0f;
      }
    }
  }

  /* Place Pixels into the right cell */
  for (int i = 0; i < pixels.size(); i++)
  {
    if (pixels.at(i)->moved)
    {
      if(topLeft.Contains(pixels.at(i)->position))
      {
        topLeft.pixels.emplace_back(pixels.at(i));
      }
      if(bottomLeft.Contains(pixels.at(i)->position))
      {
        bottomLeft.pixels.emplace_back(pixels.at(i));
      }
      if(topRight.Contains(pixels.at(i)->position))
      {
        topRight.pixels.emplace_back(pixels.at(i));
      }
      if(bottomRight.Contains(pixels.at(i)->position))
      {
        bottomRight.pixels.emplace_back(pixels.at(i));
      }
    }
  }

  //std::cout << topLeft.bounds.x << " : " << topLeft.bounds.w << " : " << topLeft.bounds.y << " : " << topLeft.bounds.h << "\n";

  std::cout << "tl: " << topLeft.pixels.size();
  std::cout << " bl: " << bottomLeft.pixels.size();
  std::cout << " tr: " << topRight.pixels.size();
  std::cout << " br: " << bottomRight.pixels.size() << "\n";

  /* Update every pixel entity */
  for (int i = 0; i < topLeft.pixels.size(); i++)
    topLeft.pixels.at(i)->Update(topLeft);

  for (int i = 0; i < topRight.pixels.size(); i++)
    topRight.pixels.at(i)->Update(topRight);

  for (int i = 0; i < bottomLeft.pixels.size(); i++)
    bottomLeft.pixels.at(i)->Update(bottomLeft);

  for (int i = 0; i < bottomRight.pixels.size(); i++)
    bottomRight.pixels.at(i)->Update(bottomRight);
}

void sceneExample::Render()
{
  for(int i = 0; i < pixels.size(); i++)
    pixels.at(i)->Draw();

  ImGui::BeginMainMenuBar();
  if (ImGui::BeginMenu("File"))
  {
    ImGui::MenuItem("Save");
    ImGui::Separator();

    if (ImGui::MenuItem("Exit"))
      app.done = true;

    ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("Edit"))
  {
    if (ImGui::MenuItem("Brush"))
      brushMenu = (brushMenu ? false : true );
    ImGui::MenuItem("Sandbox");
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();

  if (brushMenu)
  {
    ImGui::Begin("Brush!", &brushMenu);
    ImGui::ColorEdit4("Color", (float*)&color, ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_AlphaBar );
    ImGui::End();
  }

  SDL_Color boundCol = { 255, 255, 255, 255 };
}
