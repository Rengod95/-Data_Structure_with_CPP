#include <algorithm>
#include <iostream>
using namespace std;

template<class T>
void changeSize(T * &targetArray, int oldSize, int newSize){
	if(newSize <0) throw "Size should be >=0";

	T* temp = new T[newSize];
	int number = min(oldSize,newSize);
	copy(targetArray, targetArray+number,temp);
	delete []targetArray;
	targetArray = temp;

}

