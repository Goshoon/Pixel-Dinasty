#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640
#define RENDER_SCALE 6.0f

class Application
{
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::unordered_map<std::string, SDL_Texture*> images;

	bool done = false;
	bool mbLeft = false;
	bool mbRight = false;
  SDL_Point mPosition; // Relative mouse Position (x, y)

  static Application& GetInstance()
	{
    static Application instance;
    return instance;
  }

	void Display();
	void DrawEverything();
	void Input();
	void AddTexture(const std::string& ID, const char* fileDir);
	SDL_Texture* GetTexture(const std::string& ID);
	void DrawRectangle(int x, int y, int width, int height, SDL_Color color);
	void RenderImage( SDL_Texture* image, int x, int y );
	void RenderImage( SDL_Texture* image, int x, int y, int w, int h );
private:
  Application();
	~Application();

  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;

	void InputReleased(SDL_Event* event);
	void InputPressed(SDL_Event* event);
};
