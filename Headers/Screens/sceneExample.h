#pragma once
#include "screen.h"
#include "cell.h"
#include "pixel.h"
#include <vector>
#include <memory>

class sceneExample : public Screen
{
public:
	sceneExample();
	~sceneExample();

	void Update() override;
	void Render() override;

  int cells = 2;
  int horizontalThreshold = (WINDOW_WIDTH/RENDER_SCALE) / cells;
  int verticalThreshold = (WINDOW_HEIGHT/RENDER_SCALE) / cells;

  /* All Pixel instances */
  std::vector<Pixel*> pixels;

  /* Quadtree Cells */
  Cell topLeft = Cell(0, horizontalThreshold, 0, verticalThreshold);
  Cell bottomLeft = Cell(0, horizontalThreshold, verticalThreshold, WINDOW_HEIGHT);
  Cell topRight = Cell(horizontalThreshold, WINDOW_WIDTH, 0, verticalThreshold);
  Cell bottomRight = Cell(horizontalThreshold, WINDOW_WIDTH, verticalThreshold, WINDOW_HEIGHT);
private:
  Cell* mCell;
  float mbCooldown = 0.0f;
  bool brushMenu = false;
  bool sandboxMenu = false;
  ImVec4 color = ImVec4( 1.0f, 0.0f, 0.0f, 1.0f );
  Application& app = Application::GetInstance();
};
