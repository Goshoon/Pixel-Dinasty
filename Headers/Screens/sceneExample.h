#pragma once
#include "screen.h"
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

  /* All Pixel instances */
  std::vector<std::shared_ptr<Pixel>> pixels;

  /* Quadtree Cells */
  std::vector<std::shared_ptr<Pixel>> topLeft;
  std::vector<std::shared_ptr<Pixel>> topRight;
  std::vector<std::shared_ptr<Pixel>> bottomLeft;
  std::vector<std::shared_ptr<Pixel>> bottomRight;
private:
  float mbCooldown = 0.0f;
};
