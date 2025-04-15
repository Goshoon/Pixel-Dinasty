#include "entity.h"

Entity::Entity()
{}

Entity::Entity(int x, int y)
{
	position.x = x;
	position.y = y;
	position.w = 32;
	position.h = 32;
}

void Entity::Update()
{}

void Entity::Draw()
{}