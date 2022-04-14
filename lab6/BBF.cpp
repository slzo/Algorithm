#include <iostream>
#include <queue>
#include <algorithm>
#define E_MAX 10
using namespace std;

//------------------定义KDT的数据结构------------------------
struct Point{
    long long  x, y;
};
struct KDT{
    struct Node{//非叶子节点记录分裂值及左右子树
        long long split_value;
        int D;
        KDT *left;
        KDT *right;
    };
    union { //叶子节点记录点数据,
        Point point;
        Node node;
    } value;
    bool isleaf; //记录是否是叶子节点
};
KDT *root;
//---------------------------------------------------------

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

//--------------------最近邻搜索---------------------------------
long long min_dis;
Point Target; //目标节点
long long cal_dis(Point a, Point b){ //计算target point到cur point的欧式距离
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
void KNN(KDT *T) {
    if(T->isleaf) { //叶子节点
        long long d = cal_dis(T->value.point, Target);
        min_dis = min_dis > d ? d : min_dis;
        return;
    }
    else {
        if(T->value.node.D) { //以x轴划分
            if(Target.x <= T->value.node.split_value) {
                KNN(T->value.node.left);
                long long l = (Target.x - T->value.node.split_value)*(Target.x - T->value.node.split_value);
                if(l < min_dis) {
                }
            }
            else {
                KNN(T->value.node.right);
                long long l = (Target.x - T->value.node.split_value)*(Target.x - T->value.node.split_value);
                if(l < min_dis) {
                }
            }
        }
        else {
            if(Target.y <= T->value.node.split_value) {
                KNN(T->value.node.left);
                long long l = (Target.y - T->value.node.split_value)*(Target.y - T->value.node.split_value);
                if(l < min_dis) {
                }
            }
            else {
                KNN(T->value.node.right);
                long long l = (Target.y - T->value.node.split_value)*(Target.y - T->value.node.split_value);
                if(l < min_dis) {
                }
            }
        }
        return;
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
	depth %= 2;
    KDT* T;
    if(l==r) { //叶子节点,构造叶子,储存点值
        T->isleaf = true;
        T->value.point = *(V+l);
        return T;
    }
    else { //非叶子节点,储存分裂信息
        T->isleaf = false;
        KDT::Node split_;
        int mid = (l+r)/2;
        if(depth){ //选取中间节点作为节点,建立平衡树
            nth_element(V+l, V+mid, V+r+1 , mycmpx);
            split_.split_value = (V+mid)->x; split_.D = depth;
        }
        else {
            nth_element(V+l, V+mid, V+r+1 , mycmpy);
            split_.split_value = (V+mid)->y; split_.D = depth;
        }
        T->value.node = split_;
        T->value.node.left = Built(l, mid,depth+1);
        T->value.node.right = Built(mid+1, r, depth+1);
        return T;
    }
}
//-----------------------------------------------------------------

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
