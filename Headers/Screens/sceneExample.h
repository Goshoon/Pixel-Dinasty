#pragma once
#include "screen.h"
#include "pixel.h"
#include "quadtree.h"
#include <vector>
#include <memory>
#include <cstddef>
#include <iostream>
#include <new>

class sceneExample : public Screen
{
public:
	sceneExample();
	~sceneExample();

	void Update() override;
	void Render() override;

  /* All Pixel instances */
  std::vector<Pixel> pixels;
private:
  float mbCooldown = 0.0f;
  bool brushMenu = false;
  bool sandboxMenu = false;
  SDL_Rect worldBounds = { 0, 0, WINDOW_WIDTH/(int)RENDER_SCALE, WINDOW_HEIGHT/(int)RENDER_SCALE };
  ImVec4 color = ImVec4( 1.0f, 0.0f, 0.0f, 1.0f );
  Color col;
  Quadtree quadtree = Quadtree(0, worldBounds);
  Application& app = Application::GetInstance();
};
