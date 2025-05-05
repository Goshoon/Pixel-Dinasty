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
  std::vector<Pixel> pixels;
private:
  float mbCooldown = 0.0f;
  bool brushMenu = false;
  bool sandboxMenu = false;
  ImVec4 color = ImVec4( 1.0f, 0.0f, 0.0f, 1.0f );
  Application& app = Application::GetInstance();
};
