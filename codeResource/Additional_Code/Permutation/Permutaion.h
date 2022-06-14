#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
void permutation(T* arr, const int start, const int end){
	if(start == end){
		for(int i = start; i<=end; i++){cout <<arr[i]<<endl;}
	}
	else{
		for(int i = start; i<=end; i++){
			swap(arr[start],arr[i]);
			permutation(arr, start+1, end);
			swap(arr[start], arr[i]);
		}
	}
}