#include "Stack.h"

int main(){
	Stack<int> test(3);
	test.Push(3);
	test.Push(5);
	test.Push(7);
	test.Pop();
	test.Push(1);
	test.Push(19);
	test.printCapacity();
	test.printStack();
	test.Pop();
	test.Pop();
	test.Pop();
	test.Pop();
	test.Pop();
	test.Pop();
	test.printStack();
	return 0;
}
