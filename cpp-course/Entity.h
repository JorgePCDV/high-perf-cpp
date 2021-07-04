#pragma once
class Entity
{
public:
	float x, y;
	
	Entity();
	Entity(float X, float Y);
	void Move(float xa, float ya);

	~Entity();

	void Print();
};

void Constructors();

