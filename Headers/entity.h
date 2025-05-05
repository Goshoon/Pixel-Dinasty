#pragma once
#include "application.h"

class Entity
{
public:
	Entity();
	Entity(int x, int y);

	unsigned short frame, xOffset, yOffset;
	bool animated;

	SDL_Rect position;

	void Update();
	void Draw();
private:
	SDL_Rect src; // Animacion
};
