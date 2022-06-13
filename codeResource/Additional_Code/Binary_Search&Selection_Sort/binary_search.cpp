#include <iostream>
#include "selection_sort.cpp"
using namespace std;

int BinarySearch(int *a, const int x, const int left, const int right) {
     // 정렬된 배열 a[0], ..., a[n-1]에서 x를 탐색
     while (left <= right) {
        int middle = (left + right) / 2; 
        if (x < a[middle]) return BinarySearch(a, x, left, middle - 1);
        else if (x > a[middle]) return BinarySearch(a,x,middle + 1,right);
        else return middle;
	 } // while 의 끝
	 	cout<< "발견안됌";
        return -1;  // 발견되지 않음
}

int main(){
	int a[10] = {17, 25, 67, 84, 90, 30, 55, 6, 9, 28};
	selection_sort( sizeof(a)/sizeof(int),a);
	cout << BinarySearch(a,25,a[0],a[9]);
	return 0;
}
