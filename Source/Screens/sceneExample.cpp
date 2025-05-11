#include "sceneExample.h"

sceneExample::sceneExample()
{
	std::cout << "Created scenedd!\n";
  pixels.reserve(1700);
  placeSound = Application::GetInstance().GetSound("pixel");
  deleteSound = Application::GetInstance().GetSound("delete");
}

sceneExample::~sceneExample()
{}

void sceneExample::Update()
{
  Application& app = Application::GetInstance();
  mbCooldown *= 0.1f;
  col.red = static_cast<int>(color.x * 255.0f);
  col.green = static_cast<int>(color.y * 255.0f);
  col.blue = static_cast<int>(color.z * 255.0f);
  col.alpha = static_cast<int>(color.w * 255.0f);

  app.backgroundColor.red = static_cast<int>(backgroundColor.x * 255.0f);
  app.backgroundColor.green = static_cast<int>(backgroundColor.y * 255.0f);
  app.backgroundColor.blue = static_cast<int>(backgroundColor.z * 255.0f);

  /* Clear Quadtree and place Pixels on repective cells */
  quadtree.Clear();
  for (auto& pix : pixels)
    quadtree.Insert(&pix);

  /* Update every Pixel */
  for (auto& pix : pixels)
  {
    std::vector<Pixel*> nearby;
    quadtree.Retrieve(nearby, pix.position);
    pix.Update(nearby);
  }

  /* Check if in SDL2 Context */
  if (!ImGui::GetIO().WantCaptureMouse)
  {
    /* Create Pixels */
    if(app.mbLeft && mbCooldown < 1)
    {
      if (SDL_PointInRect(&app.mPosition, &quadtree.bounds))
      {
        std::cout << pixels.size() << "\n";
        bool canPlace = true;
        std::vector<Pixel*> nearby;
        SDL_Rect mPosition = { app.mPosition.x, app.mPosition.y, 1, 1 };
        quadtree.Retrieve(nearby, mPosition);

        for(auto& near : nearby)
        {
          if (near->position.x == app.mPosition.x && near->position.y == app.mPosition.y)
          {
            canPlace = false;
            break;
          }
        }

        if (canPlace)
        {
          Mix_PlayMusic(placeSound, 1);
          Pixel pixel = Pixel(app.mPosition.x, app.mPosition.y, col);
          pixel.behaviour = currentBehaviour;
          pixels.emplace_back(pixel);
          mbCooldown = 100.0f;
        }
      }
    }
    else if (app.mbRight && mbCooldown < 1) /* Erase Pixels */
    {
      mbCooldown = 100.0f;
      for (auto it = pixels.begin(); it != pixels.end(); ) 
      {
        if (SDL_PointInRect(&app.mPosition, &it->position) == SDL_TRUE) 
        {
          // Erase
          pixels.erase(it);
          Mix_PlayMusic(deleteSound, 1);
        }
        else
        {
          ++it;
        }
      }
    } 
  }
}

void sceneExample::Render()
{
  Application& app = Application::GetInstance();

  SDL_SetRenderDrawColor(app.renderer, col.red, col.green, col.blue, 100);
  SDL_RenderDrawPoint(app.renderer, app.mPosition.x, app.mPosition.y);
  for(int i = 0; i < pixels.size(); i++)
    pixels.at(i).Draw();

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

    if (ImGui::MenuItem("Sandbox"))
      sandboxMenu = (sandboxMenu ? false : true);

    ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("Window"))
  {
    if (ImGui::MenuItem("Fullscreen"))
    {
      Uint32 flags = SDL_GetWindowFlags(app.window);

      if (flags & SDL_WINDOW_FULLSCREEN) 
      {
        SDL_SetWindowFullscreen(app.window, 0);
      }
      else
      {
        SDL_SetWindowFullscreen(app.window, SDL_WINDOW_FULLSCREEN);
      }
    }
    ImGui::EndMenu();
  }

  ImGui::EndMainMenuBar();

  if (brushMenu)
  {
    ImGui::Begin("Brush!", &brushMenu);
    ImGui::Text("Brush color");
    ImGui::ColorEdit4("Color", (float*)&color, ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_AlphaBar );

    if (ImGui::Button("Static"))
      currentBehaviour = STATIC;

    ImGui::SameLine();

    if (ImGui::Button("Dynamic"))
      currentBehaviour = DYNAMIC;
/*
    if (ImGui::Button("Water"))
      currentBehaviour = WATER;
    */
    ImGui::End();
  }

  if (sandboxMenu)
  {
    ImGui::Begin("Sandbox!", &sandboxMenu);
    ImGui::Text("Background color");
    ImGui::ColorEdit3("Color",(float*)&backgroundColor , ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_AlphaBar );
    ImGui::End();
  }

  SDL_Color boundCol = { 255, 255, 255, 255 };
}
