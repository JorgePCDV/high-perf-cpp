#pragma once
class Player
{
public:
	int x, y;
	int speed;

	void Move(int xa, int ya) {
		x += xa * speed;
		y += ya * speed;
	}
};

void PlayerExample();

