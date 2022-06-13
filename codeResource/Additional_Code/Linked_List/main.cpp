#include <iostream>
#include <algorithm>
#include "List.h"

using namespace std;
int main(){
	Chain<int> test;
	Chain<int> other;
	other.insertBack(100);
	other.insertBack(300);
	test.insertBack(4);
	test.insertBack(34);
	test.insertBack(5);
	test.insertBack(3);
	test.deleteNode(3);
	test.insertBack(1);
	test.Concatenate(other);
	test.insertBack(409);
	test.printList();
	test.sumData();
}