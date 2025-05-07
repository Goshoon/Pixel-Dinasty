#include "main.h"
using std::cout, std::cin, std::shared_ptr, std::unique_ptr, std::make_unique;

int main(int argc, char* argv[])
{
	// Initialize SDL2 & ImGui
	Inititialize();

	// Create initial scene
	unique_ptr<Screen> currentScreen = make_unique<sceneExample>();
  Application& app = Application::GetInstance();

	while(!app.done)
	{
		app.Input(); /* User inputs */

		ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    currentScreen->Update(); /* Scene update position and input */
		app.Display(); /* Mostrar interfaces y Actualizar pantalla */
		currentScreen->Render(); /* Render elements on the scene */
		app.DrawEverything(); /* Refresh window and clear renderer */
	}

	// Cerrar dependencias y limpiar memoria
	Quit();
	
	return 0;
}
