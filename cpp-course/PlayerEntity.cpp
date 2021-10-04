#include "PlayerEntity.h"
#include <iostream>

void PlayerEntity::PrintName()
{
	// check
	std::cout << "Name: " << Name << std::endl;
}

void Inheritance()
{
	PlayerEntity player;
	player.Move(5, 5);
	player.PrintName();
}
