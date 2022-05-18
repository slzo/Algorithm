#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int G_M[51][51]; //使用邻接均阵保存图
int d[51], low[51],pred[51],discover[51];
int c_num[51], CV_flag[51]; //c_num是DFS_Tree中节点孩子的数量,CV_flag用于判断是否是cut_vertex
int t = 0; //time

void Init(){ //初始化各个变量
	for(int i = 0; i < 51; i++) {
		CV_flag[i] = c_num[i] = d[i] = low[i] = pred[i] = discover[i] = 0;
		for(int j = 0; j < 51; j++)
			G_M[i][j]=0;
		}
	return ;
}

int Create(char* filepath) { //根据输入建立邻接矩阵
	ifstream file;
	file.open(filepath, ios::in);
	if(!file.is_open())
		return 0;
	string s;
	int num=1;
	while( getline(file, s) ) {
		stringstream ss(s);
		while( getline(ss,s,',') )
			G_M[num][atoi(s.c_str())] = 1;
		num++;
	}
	return 1;
}

void DFS(int u){ //DFS遍历图
	discover[u]=1;
	low[u] = d[u] = ++t;
	for(int v = 1; v < 51; v++)
		if(G_M[u][v]) {
			if(!discover[v]) {
				pred[v] = u;
				DFS(v);
				low[u] = min(low[u],low[v]);
				if(d[u] <= low[v])
					CV_flag[u] = 1; //子树中无backedge指向祖先,该点极有可能是cut vertex
			}
			else if( v != pred[u] )
				low[u] = min(low[u], d[v]);
		}
}

void findAllBridges() { //找出所有bridge
	t = 0;
	for(int u = 1; u < 51; u++)
		if(!discover[u])
			DFS(u);
	for(int v = 1; v < 51; v++) {
		int u = pred[v];
		if(u && d[v] == low[v])
			cout << '(' << u << ','<< v << ')' << endl;
	}
	return;
}
void findAllCV() { //找出所有cut vertex
	for(int i = 1; i < 51; i++)
		c_num[pred[i]]++;
	for(int i = 1; i < 51; i++) {
		if(pred[i] == 0 && (c_num[i]>=2))  //root of DFS_tree && outdegree>=2, must be a cut vertex
			cout << i << ' ';
		else if(pred[i]!=0 && CV_flag[i]) //sub_tree no backedge to his ans
				cout << i << ' ';
		else continue;
	}
	return;
}
int main(int argc, char **argv) {
	Init();
	if(!Create(argv[1]))
		return 0;
	findAllBridges();
	findAllCV();
	cout << endl;
	return 0;
}

	
