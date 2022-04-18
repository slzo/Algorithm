#include <iostream>
#include <algorithm>
#include <queue>
#include <ctime>
using namespace std;
bool Flag;
//------------------定义KDT的数据结构------------------------
struct Point{
    long long  x, y;
};
struct KDT{
    Point point; //记录该点的值
    KDT *left;
    KDT *right;
    int D;
};
KDT *root;
//-------------------------------------------------------------

//------------------构造Bin的优先队列------------------------
struct Bin{
    KDT*T; //节点位置
    long long distance; //节点距离当前平面分割线的距离
};
bool operator < (Bin a, Bin b) { //重载运算符,已Bin.distance为基准对其进行排序
    return a.distance < b.distance;
}
bool operator == (Bin a, Bin b) {
    return a.distance == b.distance;
}
bool operator > (Bin a, Bin b) {
    return a.distance > b.distance;
}
priority_queue<Bin, vector<Bin>, greater<Bin> > que; //Bin优先队列,递增进行,每次取出队首元素即距离目标点最近的bin
int E_Max= 20; //最大叶子检查数量
//-------------------------------------------------------------

//-------------------------------------------------------------
long long cal_len(Point X, Point Y) {
    return (X.x-Y.x)*(X.x-Y.x)+(X.y-Y.y)*(X.y-Y.y);
}
Point Target;
long long min_dis;

void KNN(KDT *T) { //平面最近搜索  递归进行查找
	if (!T) { //到达叶子节点,选取最近的bin进行回溯
		if( !que.empty() ) {
			Bin tmp = que.top(); que.pop();
			if( tmp.distance < min_dis )
				KNN(tmp.T);
			else { //当前最优待选节点也不符合条件,说明已经为最优,直接退出
				while(!que.empty())
					que.pop();
			}
		}
		return;
	}
    long long d = cal_len(Target, T->point);
    min_dis = min_dis > d ? d : min_dis;
	E_Max--;
	if(!E_Max) Flag = 0;//检查节点个数达最大
	if (T->D) { //当前节点根据x轴划分
		long long l = (Target.x - T->point.x)* (Target.x - T->point.x);
		if (Target.x < T->point.x) {
			if(l < min_dis) //目前节点最小距范围与平面有交点,搜索一子树,同时将其另一子树加入待考察区域

				if(Flag) { //Bin的个数未达最大值,可继续添加
					Bin tmp;
					tmp.T = T->right; tmp.distance = l; //搜索左子树,同时将右子树压入bin的优先队列
					que.push(tmp);
				}
			KNN(T->left); //搜索左子树
		}
		else {
			if(l < min_dis)
				if(Flag) {
					Bin tmp;
					tmp.T = T->left; tmp.distance = l; //搜索右子树,同时将左子树压入bin的优先队列
					que.push(tmp);
				}
			KNN(T->right);
		}
	}
	else { //根据y轴划分,与上述基本相同
		long long l = (Target.y - T->point.y)* (Target.y - T->point.y);
		if (Target.y < T->point.y) {
			if(l < min_dis)
				if(Flag) {
					Bin tmp;
					tmp.T = T->right; tmp.distance = l; //搜索左子树,同时将右子树压入bin的优先队列
					que.push(tmp);
				}
			KNN(T->left);
		}
		else {
			if(l < min_dis)
				if(Flag) {
					Bin tmp;
					tmp.T = T->left; tmp.distance = l; //搜索右子树,同时将左子树压入bin的优先队列
					que.push(tmp);
				}
			KNN(T->right);
		}
	}
}
//-------------------------------------------------------------

//------------------------建树-----------------------------------
bool mycmpx(Point x, Point y) {
	if(x.x < y.x)
		return 1;
	return 0;
}
bool mycmpy(Point x, Point y) {
	if(x.y < y.y)
		return 1;
	return 0;
}

Point *V;
KDT* Built(int l, int r, int depth){
	if(l>r)
		return NULL;
	int mid = (l+r)/2;
	depth %= 2;
	if(depth) //选取中间节点作为节点,建立平衡树
		nth_element(V+l, V+mid, V+r+1 , mycmpx);
	else
		nth_element(V+l, V+mid, V+r+1 , mycmpy);
	KDT*T = new KDT[1];
	T->D = depth;
	T->point = *(V+mid); //中间值作为节点, 其他值均等分在左右子树
	T->left = Built(l, mid-1,depth+1);
	T->right = Built(mid+1, r, depth+1);
	return T;
}
//-------------------------------------------------------------

int main() {
    int n;
    cin >> n;
	V = new Point[n];
    for(int i = 0; i < n; i++) {
        Point p;
        cin >> p.x >> p.y;
		V[i] = p;
    }
    root = Built(0, n-1, 1);
    int m;
    cin >> m;
	clock_t st, en;
	st = clock();
    for(int i = 0; i < m; i++) {
        cin >> Target.x >> Target.y;
        min_dis = 1000000000000000000;
		Flag = true;
        KNN(root);
        cout << min_dis << endl;
    }
    en = clock();
	cout << (double)(en-st)/CLOCKS_PER_SEC << "s" <<endl;
    return 0;
}
