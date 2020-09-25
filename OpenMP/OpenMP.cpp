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

int main() 
{
	hello_openmp();
	getchar();
	return 0;
}