#include <iostream>
#include <bitset>
#include <ctime>
using namespace std;
#define p 100000007 //a big prime
#define m 80000000 // the length of bloom_filter
#define check_num 1000 //检查的数字个数

bitset<80000000> Bloom_Fliter;
long long num_list[10000000]; //存储数据,进行结果核对使用

int main() {
	long long num;
	for(int i = 0; i < 10000000; i++) {
		cin >> num;
		num_list[i] = num;
		int h1 = (101*num)%p%m; //hash1 = 101*x mod p mod m
		int h2 = (1001+101*num)%p%m; //hash2 = 101*x+997 mod p mod m
		int h3 = (701+103*num+101*num*num)%m; // hash3 = 701+103x+101x^2 mod m
		int h4 = (809+107*num+103*num*num)%m; // hash4 = 809+107x+103x^2 mod m
		int h5 = (997+109*num+107*num*num)%m; // hash5 = 997+109x+107x^2 mod m
		Bloom_Fliter[h1] = 1;
		Bloom_Fliter[h2] = 1;
		Bloom_Fliter[h3] = 1;
		Bloom_Fliter[h4] = 1;
		Bloom_Fliter[h5] = 1;
	}
//---------------------------------随机生成1000个数字进行检查-------------------------------
	//--------生成待查询的测试点----------
	long long seek_list[check_num];
	srand( (unsigned)time(NULL) );
	for(int i = 0; i < check_num; i++)
		seek_list[i] = rand()%10000000;
	//---------------------------------
	bitset<check_num> ans;//储存bloom_filter查询结果
	clock_t st, ed;
	st = clock();
	for(int i = 0; i < check_num; i++) {
		long long seek = seek_list[i];
		int s1 = (101*seek)%p%m; //hash1 = 101*x mod p mod m
		int s2 = (1001+101*seek)%p%m; //hash2 = 101*x+997 mod p mod m
		int s3 = (701+103*seek+101*seek*seek)%m; // hash3 = 701+103x+101x^2 mod m
		int s4 = (809+107*seek+103*seek*seek)%m; // hash4 = 809+107x+103x^2 mod m
		int s5 = (997+109*seek+107*seek*seek)%m; // hash5 = 997+109x+107x^2 mod m
		if(Bloom_Fliter[s1] && Bloom_Fliter[s2] && Bloom_Fliter[s3] && Bloom_Fliter[s4] && Bloom_Fliter[s5])
			ans[i] = 1;
		else
			ans[i] = 0;
	}
	ed = clock();
//--------------------------------------------------------------------------------------
//--------------------------------使用遍历检查进行结果核对-----------------------------------
	int false_postive = 0;
	for(int i = 0; i < check_num; i++) {
	bool flag = false;
	long long seek = seek_list[i];
	for(int j = 0; j < 10000000; j++)
		if(seek == num_list[j]) {
			flag = true;
			break;
		}
	if( !flag && ans[i] ) //数字不再但bloom_filter查询存在
		false_postive++;
	}
//----------------------------------------------------------------------------------------
	cout << check_num << "次检查: " << endl;
	cout << "查询时间: " << (double)(ed-st) << "ms" << endl;
	cout << "误报率: " << false_postive << "/" << check_num << " = " << (double)false_postive/check_num << endl;
	return 0;
}


