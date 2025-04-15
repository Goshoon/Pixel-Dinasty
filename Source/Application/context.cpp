#include "context.h"

void Inititialize() // Iniciar SDL y SDL_Image
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG;

	// Inicializar Dear ImGui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui::StyleColorsDark(); // Tema

  // Setup Platform/Renderer backends
  Application& app = Application::GetInstance();
  ImGui_ImplSDL2_InitForSDLRenderer(app.window, app.renderer);
  ImGui_ImplSDLRenderer2_Init(app.renderer);
}
void Quit() // Cerrar aplicacion
{
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
    
	SDL_Quit();
}
