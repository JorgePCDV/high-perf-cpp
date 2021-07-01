#include "References.h"
#include <iostream>

#define LOG(x) std::cout << x << std::endl

void IncrementWithPointer(int* value) 
{
	(*value)++;
}

void IncrementWithReference(int& value) 
{
	value++;
}

void References()
{
	int a = 5;
	IncrementWithPointer(&a);
	IncrementWithReference(a);
	LOG(a);
	int& ref = a;
	ref = 2;
	LOG(a);

	std::cin.get();
}
