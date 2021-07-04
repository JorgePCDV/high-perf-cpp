#include "Entity.h"
#include <iostream>


void Constructors()
{
	Entity e;
	e.Print();

	Entity e1(2.0f, 3.0f);
	e1.Print();
}

Entity::Entity()
{
	x = 0.0f;
	y = 0.0f;
}

Entity::Entity(float X, float Y)
{
	x = X;
	y = Y;
}

void Entity::Print()
{
	std::cout << Entity::x << ", " << Entity::y << std::endl;
}
