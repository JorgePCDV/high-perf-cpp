#include "Player.h"
#include <iostream>

#define LOG(x) std::cout << x << std::endl



void PlayerExample()
{
	Player player;
	player.Move(1, -1);
}
