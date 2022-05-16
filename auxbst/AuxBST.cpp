#include <iostream>
#include <stack>
using namespace std;

#define Ele int

struct ABST{
	struct ABST* left;
	struct ABST* right;
	struct ABST* parent;
	Ele element;
	int size;
};
ABST *root;

void Insert(Ele c) { //插入
	ABST *cur = root;
	ABST *p = root;
	while(cur) {
		p = cur;
		cur->size++; //在寻找插入位置的过程中，所有遍历到的节点的size均增加1
		if(cur->element > c) 
			cur = cur->left;
		else 
			cur = cur->right;
	}
	if(cur == root){ //第一次插入,对根节点特殊处理
		root = new ABST[1];
		root->element = c;
		root->size = 1;
		root->parent = NULL;
	}
	else { 
		cur = new ABST[1];
		cur->element = c;
		cur->size = 1;
		cur->parent = p;
		if(p->element > c)
			p->left = cur;
		else p->right = cur;
	}
	return ;
}
void DL(ABST* cur, int op) { //删除时调用
	ABST *suc;
	if(op == 0)
		suc = NULL;
	else if(op == 1) {
		suc = cur->left;
		suc->parent = cur->parent;
	}
	else {
		suc = cur->right;
		suc->parent = cur->parent;
	}
	if(cur->parent->left == cur) 
		cur->parent->left = suc;
	else  cur->parent->right = suc;
	delete(cur);
	return;
}

void Delect(Ele c) {
	ABST *cur = root;
	while(cur) {
		cur->size -= 1; //寻找c所在节点的过程中,所有遍历到的节点的size均减少1
		if(cur->element > c) 
			cur = cur->left;
		else if(cur->element < c) 
			cur = cur->right;
		else {
			if(cur->left) { 
				if(cur->right) { //左右孩子皆存在
					ABST *suc = cur->right;
					while(suc->left) { //找到后继节点作为替换目标
						suc->size -= 1;
						suc = suc->left;
					}
					if(suc == cur->right){ //后继节点为待删除节点的孩子 
						suc->left = cur->left;
						suc->size = cur->size;
						DL(cur, 2);
					}
					else {
						suc->parent->left = suc->right;
						suc->size = cur->size-1;
						suc->right = cur->right;
						suc->left = cur->left;
						if(cur == root) { //删除根节点特殊处理
							suc->parent = NULL;
							root = suc;
						}
						else {
							if(cur == cur->parent->left)
								cur->parent->left = suc;
							else cur->parent->right = suc;
						}
						delete(cur);
					}
				}
				else //只有左孩子,直接把左孩子作为替代
					 DL(cur,1);
			}
			else {
				if(cur->right) //只有右孩子，直接将右孩子作为替代
					DL(cur,2);
				else //无孩子，直接删除即可
					DL(cur,0);
			}
			return ;
		}
	}
	cout << "error : no num " << c << " in the AuxBSTree" << endl;
	return;
}
Ele Select(ABST *T,int k) { 
	if(T->left) {
		if( (T->left->size)+1 == k) //当前节点正好为待找节点
			return T->element;
		else if( (T->left->size) >= k ) //待找节点在左子树中，寻找左子树中的第k小值
			return Select(T->left, k); 
		else return Select(T->right, k-(T->left->size)-1); //待找节点在右子树中，寻找右子树中的第t小值
	}
	else { //无左子树，直接在右子树中递归
		if(k == 1)
	   		return T->element;
		else return Select(T->right, k-1);
	}
}

ABST* Successor(ABST* T) { //找到后继节点，find(z,k)调用
	ABST *cur;
	if(T->right) {
		cur = T->right;
		while(cur->left) 
				cur = cur->left;
	}
	else {
		cur = T;
		while(cur->parent) {
			if(cur == cur->parent->left)
				return cur->parent;
			else 
				cur = cur->parent;
		}
	}
	return cur;
}

Ele Find(Ele z, int k) {
	int counter = 0;
	ABST *cur = root;
	stack<ABST*> R;
	R.push(root);
	ABST*p=root;
	while(!R.empty()) { //先序遍历找到第一个大于z的值v
		if(!p) {
			p = R.top();
			R.pop();
			if(p->element < z)
				counter++;
			else if(p->element == z)
				break;
			else
				break;
			p = p->right;
		}
		else {
			R.push(p);
			p = p->left;
		}
	}
	return Select(root, counter+k); //返回第 th(v)+k 大的值
}

void Print(ABST*T){
	ABST *cur = T;
	if(T->left)
		Print(T->left);
	cout << " " << T->element << "-" << T->size;
	if(T->right)
		Print(T->right);
	return;
}
	
void Deal(int op) {
	Ele z; 
	int k;
	switch (op) {
		case 1:
			cin >> z;
			Insert(z);
			break;
		case 2:
			cin >> z;
			Delect(z);
			break;
		case 3:
			cin >> k;
			cout << "the " << k << "th num is " << Select(root, k) << endl;
			break;
		case 4:
			cin >> z >> k;
			cout << "the "<< k <<"th num bigger than " << z << " is " << Find(z, k) << endl;;
			break;
		case 5:
			Print(root);
			cout << endl;
			break;
		default :
			cout << "no such command!" <<endl;
			break;
	}
	return ;
}
int main() {
		int op = 1;
		while(op) {
			cin >> op;
			Deal(op);
		}
		return 0;
}
