#pragma once
class Entity
{
public:
	float x, y;
	
	Entity();
	Entity(float X, float Y);

	~Entity();

	void Print();
};

void Constructors();

