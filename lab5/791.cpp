#include <iostream>
#include <stack>
using namespace std;

struct Point{
    long long  x, y;
};
Point Tar;
struct KDT{
    Point point; //记录该点的值
    KDT *left;
    KDT *right;
    int D;
};

KDT *root;
void Insert(Point p) {
	KDT *cur = root, *curp = root;
	while(cur){ //转换维度搜索 寻找合适的插入位置
		curp = cur;
        if(cur->D) {
            if(p.x > cur->point.x)
                cur = cur->right;
            else cur = cur->left;
        }
        else {
            if(p.y > cur->point.y)
                cur = cur->right;
            else cur = cur->left;
        }
	}
	if(cur == root) { //根节点特殊判断
		root = new KDT[1];
		root->point = p;
        root->D = 1;
	}
	else {
		cur = new KDT[1];
		cur->point= p;
        cur->D = curp->D?0:1;
        if(curp->D) {
            if(p.x <= curp->point.x)
                curp->left = cur;
            else curp->right = cur;
        }
        else {
            if(p.y <= curp->point.y)
                curp->left = cur;
            else curp->right = cur;
        }
	}
	return;
}

long long cal(Point X, Point Y) {
    return (X.x-Y.x)*(X.x-Y.x)+(X.y-Y.y)*(X.y-Y.y);
}

long long min_dis;
void Nearest_Search(KDT *T) { //平面最近搜索  递归进行查找
	if (!T)
		return;
	if (T->D) { //当前节点根据x轴划分
		if (Tar.x < T->point.x)
			Nearest_Search(T->left);
		else
			Nearest_Search(T->right); //先递归到叶子节点
        long long d = cal(Tar, T->point);
		min_dis = min_dis > d ? d : min_dis; //进行回溯调整
		if (min_dis > (Tar.x - T->point.x)* (Tar.x - T->point.x)) { //以当前的最小距为基准, 目标点的周边范围与目标点不在的另一半区域有交点, 需进入另一半寻找
			if (Tar.x < T->point.x)
				Nearest_Search(T->right);
			else
				Nearest_Search(T->left);
		}
	}
	else { //根据y轴划分
		if (Tar.y < T->point.y)
			Nearest_Search(T->left);
		else
			Nearest_Search(T->right);
        long long d = cal(Tar, T->point);
		min_dis = min_dis > d ? d : min_dis;
		if (min_dis > (Tar.y - T->point.y) *(Tar.y - T->point.y)) {
			if (Tar.y < T->point.y)
				Nearest_Search(T->right);
			else
				Nearest_Search(T->left);
		}
	}
}


int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        Point p;
        cin >> p.x >> p.y;
        Insert(p);
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++) {
        min_dis = 1000000000000000000;
        cin >> Tar.x >> Tar.y;
        Nearest_Search(root);
        cout << min_dis << endl;
    }
    return 0;
}
