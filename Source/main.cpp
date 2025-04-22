#include "main.h"
using std::cout, std::cin, std::shared_ptr, std::unique_ptr, std::make_unique;

int main(int argc, char* argv[])
{
	// Inicializar SDL2 & ImGui
	Inititialize();

	// Crear escena inicial
	unique_ptr<Screen> currentScreen = make_unique<sceneExample>();
  Application& app = Application::GetInstance();

	while(!app.done) /* Ciclo loop */
	{
		app.Input(); /* Detectar teclas e interacciones con la ventana */

		ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    //cout << app.mPosition.x << " : " << app.mPosition.y << "\n";

    currentScreen->Update(); /* Metodo de crear botones e interacciones de la escena actual */
		app.Display(); /* Mostrar interfaces y Actualizar pantalla */
		currentScreen->Render(); /* Metodo de mostrar elementos como imagenes u efectos */
		app.DrawEverything(); /* Actualizar la pantalla y dibujar el frame actual */
	}

	// Cerrar dependencias y limpiar memoria
	Quit();
	
	return 0;
}
