#include "queue.h"
#include <iostream>

using namespace std;
int main(){
	Queue<int> test(3);
	test.push(3);
	test.push(4);
	test.push(8);
	test.push(1);
	test.pop();
	test.push(5);
	test.printQueue();
};