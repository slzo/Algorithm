#include <iostream>
#include <ctime>
using namespace std;

int ht[15000000];//load factor = 2/3
#define check_num 1000
int main(){
    for(int i = 0; i < 15000000; i++) //初始化
        ht[i] = -1;
    long long num;
    for(int i = 0; i < 10000000; i++) { //采用多项式hash
        cin >> num;
        int index = (997+109*num+107*num*num)%15000000;
        while(ht[index] != -1)
            index = (index+1)%15000000;
        ht[index] = num;
    }
    srand( (unsigned)time(NULL) );
    clock_t st,ed;
    st = clock();
    for(int i = 0; i < check_num; i++) {
        long long seek = rand()%10000000;
        int index = (997+109*seek+107*seek*seek)%15000000;
        int counter = 15000000;
        while(counter){
            if(ht[index] == seek) { //find
                cout << seek << ":yes" << endl;
                break;
            }
            else if(ht[index] == -1) { //reach a empty means can't find
                cout << seek << ":no" << endl;
                break;
            }
            else {
                index = (index+1)%15000000;
                counter--;
            }
        }
        if(!counter) cout << seek << ":no" << endl; //遍历全部均未找到
    }
    ed = clock();
    cout << check_num << "次查询: " << endl;
    cout << "查询时间: " << (double)(ed-st) << "ms" << endl;
    return 0;
}

