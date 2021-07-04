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
	std::cout << "Constructed Entity" << std::endl;
	x = 0.0f;
	y = 0.0f;
}

Entity::Entity(float X, float Y)
{
	x = X;
	y = Y;
}

Entity::~Entity()
{
	std::cout << "Entity Destroyed" << std::endl;
}

void Entity::Print()
{
	std::cout << Entity::x << ", " << Entity::y << std::endl;
}
