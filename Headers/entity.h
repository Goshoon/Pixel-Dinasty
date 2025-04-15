#pragma once
#include <memory>
#include "application.h"
using std::unique_ptr;

extern unique_ptr<Application> app;

class Entity
{
public:
	Entity();
	Entity(int x, int y);

	unsigned short frame, xOffset, yOffset;
	bool animated;

	SDL_Rect position;
	SDL_Texture* sprite;

	void Update();
	void Draw();
private:
	SDL_Rect src; // Animacion
};