#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <random> 
#include <ctime> 
#include <chrono>

using namespace std;

int n_tests[] = { 10, 100, 200, 400, 1000, 2000, 4000, 10000, 20000, 50000, 100000, 200000, 400000, 800000, 1000000, 2000000, 4000000, 8000000, 10000000, 20000000 };

int main(int argc, char * argv[])
{
	char* filein;

	filein = argv[1];
	freopen(filein, "wb", stdout);
	//freopen("matr.in", "wb", stdout);
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	uniform_real_distribution <double> distribution(-1e3, 1e3);

	int n = 1000;
	if (argc > 1)
		n = n_tests[atoi(argv[2])];
	fwrite(&n, sizeof(n), 1, stdout);

	int *cur = new int[2];
	for (int i = 0; i < n - 4; i++)
	{
		cur[0] = distribution(generator);
		cur[1] = distribution(generator);
		fwrite(cur, sizeof(*cur), 2, stdout);
	}

	cur[0] = -1000;
	cur[1] = 1000;
	fwrite(cur, sizeof(*cur), 2, stdout);
	cur[0] = 1000;
	cur[1] = 1000;
	fwrite(cur, sizeof(*cur), 2, stdout);
	cur[0] = 1000;
	cur[1] = -1000;
	fwrite(cur, sizeof(*cur), 2, stdout);
	cur[0] = -1000;
	cur[1] = -1000;
	fwrite(cur, sizeof(*cur), 2, stdout);

	double time = 1.0;
	fwrite(&time, sizeof(time), 1, stdout);
	delete cur;
	return 0;
}