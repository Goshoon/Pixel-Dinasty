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

  /* Create Pixels */
  if(app.mbLeft && mbCooldown < 1)
  {
    if (!ImGui::GetIO().WantCaptureMouse)
    {
      Color col;
      col.red = static_cast<int>(color.x * 255.0f);
      col.green = static_cast<int>(color.y * 255.0f);
      col.blue = static_cast<int>(color.z * 255.0f);
      col.alpha = static_cast<int>(color.w * 255.0f);
      Pixel pixel = Pixel(app.mPosition.x, app.mPosition.y, col);
      pixels.emplace_back(pixel);
      mbCooldown = 100.0f;
    }
  }
}

void sceneExample::Render()
{
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
