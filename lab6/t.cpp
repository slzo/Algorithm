#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

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
    KDT*T;
    long long distance;
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
priority_queue<Bin, vector<Bin>, greater<Bin> > que;
//-------------------------------------------------------------

//-------------------------------------------------------------
long long cal_len(Point X, Point Y) {
    return (X.x-Y.x)*(X.x-Y.x)+(X.y-Y.y)*(X.y-Y.y);
}
Point Target;
long long min_dis;
void KNN(KDT *T) { //平面最近搜索  递归进行查找
	if (!T)
		return;
    long long d = cal_len(Target, T->point);
    min_dis = min_dis > d ? d : min_dis;
	if (T->D) { //当前节点根据x轴划分
		if (Target.x < T->point.x)
			KNN(T->left);
		else
			KNN(T->right); //先递归到叶子节点
		if (min_dis > (Target.x - T->point.x)* (Target.x - T->point.x)) { //以当前的最小距为基准, 目标点的周边范围与目标点不在的另一半区域有交点, 需进入另一半寻找
			if (Target.x < T->point.x)
				KNN(T->right);
			else
				KNN(T->left);
		}
	}
	else { //根据y轴划分
		if (Target.y < T->point.y)
			KNN(T->left);
		else
			KNN(T->right);
		if (min_dis > (Target.y - T->point.y) *(Target.y - T->point.y)) {
			if (Target.y < T->point.y)
				KNN(T->right);
			else
				KNN(T->left);
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

    return 0;
}
