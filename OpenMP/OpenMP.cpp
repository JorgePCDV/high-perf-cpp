#include <iostream>
#include <chrono>
#include <omp.h>
#include "OpenMP.h"

using namespace std;

void hello_openmp() 
{
#pragma omp parallel
	{
		cout << "Hello OpenMP ";
	}
}

int main() 
{
	hello_openmp();
	getchar();
	return 0;
}