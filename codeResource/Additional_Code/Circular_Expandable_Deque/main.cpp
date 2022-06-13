#include "Deque.h"
using namespace std;

int main(){
	Deque<int> test(3);
	 test.pushBack(1);
	 test.pushBack(5);
	 test.pushFront(13);
	 test.pushFront(11);
	 test.popFront();
	 test.popBack();
	 test.printDeque();
	 test.getRearIndex();
	 test.getFrontIndex();
	 test.pushFront(30);
	 test.pushBack(500);
	 test.printDeque();
	test.getRearIndex();
	test.getFrontIndex();

}