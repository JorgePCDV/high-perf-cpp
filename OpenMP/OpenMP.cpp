#include <iostream>
#include <chrono>
#include <omp.h>
#include "OpenMP.h"

using namespace std;

void hello_openmp() 
{
	omp_set_num_threads(8);
#pragma omp parallel
	{
#pragma omp critical
		cout 
			<< "Hello OpenMP " 
			<< omp_get_thread_num()
			<< "/"
			<< omp_get_num_threads()
			<< endl;
	}
}

void pfor()
{
	const int length = 1024 * 1024 * 64;
	float *a = new float[length],
		  *b = new float[length],
		  *c = new float[length],
		  *result = new float[length];

	for (size_t i = 0; i < length; i++)
	{
		result[i] = a[i] + b[i] * erff(c[i]);
	}
}

int main() 
{
	hello_openmp();
	pfor();
	getchar();
	return 0;
}