
#define _CRT_SECURE_NO_WARNINGS
#include "Sol.h"
#include <cstdio>
//#include <time.h> 
#include <chrono>
#include <iostream>
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/tick_count.h"

using namespace tbb;

using namespace std;

int main(int argc, char * argv[])
{
	int num_threads = 1; 
	if (argc > 1) 
		num_threads = atoi(argv[1]);
	
	
	CPoint *mainArrOfPoints = 0;

	int amountOfPoints;
	freopen("matr.in", "rb", stdin); 
	freopen("matr.out", "wb", stdout);
	fread(&amountOfPoints, sizeof(amountOfPoints), 1, stdin);
	int linCountConv = 0;

	mainArrOfPoints = new CPoint[amountOfPoints];
	int *A = new int[2 * amountOfPoints];
	fread(A, sizeof(*A), 2 * amountOfPoints, stdin);
	for (int j=0; j<amountOfPoints; j++)
	{
		mainArrOfPoints[j].x = A[2*j];
		mainArrOfPoints[j].y = A[2*j + 1];
	}
	task_scheduler_init init;
	int rows, grainSize=100;
	tick_count start = tick_count::now();
	parallel_for(blocked_range<int>(0, rows, grainSize), Conv(mainArrOfPoints, amountOfPoints, linCountConv));
	tick_count finish = tick_count::now();
	tick_count time = (finish - start).seconds();
	
	int *B = new int[2 * linCountConv];
	for (int j = 0; j<linCountConv; j++)
	{
		B[2*j] = mainArrOfPoints[j].x;
		B[2*j + 1] = mainArrOfPoints[j].y;
	}
	
	fwrite(&linCountConv, sizeof(linCountConv), 1, stdout);
	fwrite(B, sizeof(*B), 2 * linCountConv, stdout);
	fwrite(&time, sizeof(time), 1, stdout);
	delete B;
	fclose(stdin);
	fclose(stdout);
	
}