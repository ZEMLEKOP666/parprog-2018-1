#define _CRT_SECURE_NO_WARNINGS
#include <cstdio> 
#include <cmath> 
#include <string>

using namespace std;

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class result {
private: 
	FILE * bur; 
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
	result(bool read = false)
	{
		if (read) bur = fopen("result.txt", "r"); else bur = fopen("result.txt", "w");
	} 
	~result() 
	{ 
		fclose(bur); 
	}

	void write_type(ext_cls t) 
	{ 
		fwrite(&t, sizeof(t), 1, bur); 
	}

	void write_verdict(verdict v) 
	{ 
		write_type(ext_cls::VERDICT); 
		fwrite(&v, sizeof(v), 1, bur); 
	}
	void write_message(string str) 
	{ 
		write_type(ext_cls::MESSAGE); 
		int l = str.size(); 
		fwrite(&l, sizeof(l), 1, bur); 
		fwrite(&str[0], sizeof(str[0]), l, bur); 
	}
	void write_time(long long x) 
	{ 
		write_type(ext_cls::TIME); 
		fwrite(&x, sizeof(x), 1, bur); 
	}
	void write_memory(unsigned long long x) 
	{ 
		write_type(ext_cls::MEMORY); 
		fwrite(&x, sizeof(x), 1, bur); 
	}
} checker_result;

int main(int argc, char * argv[])
{
	char* filein = argv[1];
	char* fileout = argv[2];
	char* fileans = argv[3];
	
	FILE * bui = fopen(filein, "rb");
	FILE * buo = fopen(fileout, "rb");
	FILE * bua = fopen(fileans, "rb");
	
	/*FILE * bui = fopen("matr.in", "rb");
	FILE * buo = fopen("matr.out", "rb");
	FILE * bua = fopen("answer.txt", "rb");*/
	
	int n;
	fread(&n, sizeof(n), 1, bui);

	int * ans = new int[2 * n], *res = new int[2 * n];
	int ans_time, res_time;

	fread(&res_time, sizeof(res_time), 1, buo);
	fread(res, sizeof(*res), 2 * n, buo);

	fread(&ans_time, sizeof(ans_time), 1, bua);
	fread(ans, sizeof(*ans), 2 * n, bua);

	double diff = 0.0; 
	for (int i = 0; i < n * n; i++) 
		diff += (ans[i] - res[i]) * (ans[i] - res[i]);

	if (diff < 1e-6) 
	{ 
		checker_result.write_message("AC. Numbers are equal."); 
		checker_result.write_verdict(verdict::AC); 
	}
	else 
	{ 
		checker_result.write_message("WA. Output is not correct."); 
		checker_result.write_verdict(verdict::WA); 
	}

	checker_result.write_time(res_time * 1e7);
	delete ans;
	delete res;

	fclose(bua); 
	fclose(buo);
	return 0;
}