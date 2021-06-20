#include <iostream>
#include "Pointers.h"

#define LOG(x) std::cout << x << std::endl

void Pointers()
{
	// Stack
	int var = 8;
	int* ptr = &var;
	*ptr = 10;
	LOG(var);

	// Heap
	char* buffer = new char[8];
	memset(buffer, 0, 8);

	// Pointer to pointer
	char** buffer_ptr = &buffer;
}
