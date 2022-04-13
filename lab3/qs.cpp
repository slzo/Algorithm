#include <iostream>
using namespace std;

int n; // 待排序的数组长度
int cmpcounter; //比较的次数
int swapcounter; // 交换的次数

void swap(int *a, int *b) { // swap a & b
		int tmp = *a;
		*a = *b; 
		*b = tmp;
		return;
}

void qs_ft(int left, int right, int *arr) { // use the first element as pivot
		if(left >= right)
						return ;
		int pivot = arr[left];
		int i = left+1;
		for(int j = left+1; j <= right; j++) {
						cmpcounter++;
						if(arr[j] < pivot) {
										swapcounter++;
										swap(arr+i, arr+j);
										i++;
						}
		}
		swap(arr+i-1, arr+left);
		swapcounter++;
		qs_ft(left, i-2 > left ? i-2 : left, arr);
		qs_ft(i, right, arr);
		return;
}

void qs_lt(int left, int right, int *arr) { // use the last element as pivot
		if(left >= right)
						return;
		int pivot = arr[right];
		int i = left;
		for(int j = left; j < right; j++) {
						cmpcounter++;
						if(arr[j] < pivot) {
										swapcounter++;
										swap(arr+i, arr+j);
										i++;
						}
		}
		swap(arr+i, arr+right);
		swapcounter++;
		qs_lt(left, i-1 > left ? i-1 : left, arr);
		qs_lt(i+1, right, arr);
		return;
}

void qs_rd(int left, int right, int *arr) { // use the random element as pivot
		if(left >= right)
						return;
		int index = left+(rand()%(right-left+1));
		int pivot = arr[index];
		int	i = (left == index ? left+1 : left);
		for(int j = left; j <= right; j++) {
						cmpcounter++;
						if(arr[j] < pivot) {
										swapcounter++;
										swap(arr+i, arr+j);
										i++;
						}
		}
		swapcounter++;
		if(i <= index) {
						swap(arr+i, arr+index);
						qs_rd(left, i-1 > left ? i-1 : left, arr);
						qs_rd(i+1, right, arr);
		}
		else {
						swap(arr+i-1, arr+index);
						qs_rd(left, i-2 > left ? i-2 : left, arr);
						qs_rd(i, right, arr);
		}
		return;
}

int Choosepivot(int left, int right, int *arr) { //choose the pivot from middle\left\right
		int middle = (left+right)/2;
		if( (arr[middle] >= arr[left]) ^ (arr[middle] > arr[right]) )
						return middle;
		if( (arr[left] > arr[middle]) ^ (arr[left] > arr[right]) )
						return left;
		if( (arr[right] > arr[left]) ^ (arr[right] > arr[middle]) )
						return right;
		return middle;
}

void qs_md(int left, int right, int *arr) { // use the median-of-three as pivot
		if(left >= right)
						return;
		int index = Choosepivot(left, right, arr);
		int pivot = arr[index];
		int	i = (left == index ? left+1 : left);
		for(int j = left; j <= right; j++) {
						cmpcounter++;
						if(arr[j] < pivot) {
										swapcounter++;
										swap(arr+i, arr+j);
										i++;
						}
		}
		swapcounter++;
		if(i <= index) {
						swap(arr+i, arr+index);
						qs_rd(left, i-1 > left ? i-1 : left, arr);
						qs_rd(i+1, right, arr);
		}
		else {
						swap(arr+i-1, arr+index);
						qs_rd(left, i-2 > left ? i-2 : left, arr);
						qs_rd(i, right, arr);
		}
		return;
}

int main(){
		cin >> n;
		int *arr1 = new int[n];
		int *arr2 = new int[n];
		int *arr3 = new int[n];
		int *arr4 = new int[n];
		for(int i = 0; i < n; i++) {
						cin >> arr1[i];
						arr2[i] = arr1[i];
						arr3[i] = arr1[i];
						arr4[i] = arr1[i];
		}
		cout << "for " << n << " element." << endl;
		cmpcounter = 0;
		swapcounter = 0;
		qs_ft(0,n-1, arr1);
		cout << "first element: compare " << cmpcounter << " times, swap "  << swapcounter << " times." << endl;
		cmpcounter = 0;
		swapcounter = 0;
		qs_lt(0,n-1, arr2);
		cout << "last element: compare " << cmpcounter << " times, swap "  << swapcounter << " times." << endl;
		cmpcounter = 0;
		swapcounter = 0;
		qs_rd(0,n-1, arr3);
		cout << "random element: compare " << cmpcounter << " times, swap "  << swapcounter << " times." << endl;
		cmpcounter = 0;
		swapcounter = 0;
		qs_md(0,n-1, arr4);
		cout << "median element: compare " << cmpcounter << " times, swap "  << swapcounter << " times." << endl;
//		for(int i = 0; i < n; i++)
//						cout<< arr[i] << " ";
//		cout << endl;
		return 0;		
}
