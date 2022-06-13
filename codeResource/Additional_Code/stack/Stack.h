#include <iostream>
using namespace std;

template<class T>
class Stack{
private:
	T* stackArray;
	int capacity;
	int top;
public:
	Stack(int _capacity) : capacity(_capacity){
		if(capacity<1) throw 'too small';
		stackArray = new T[capacity];
		top = -1;
	}
	~Stack(){delete[] stackArray;};

	bool isEmpty()const{ // 원소가 있는지 없는지 판별
		return top == -1;
	}

	int Size()const{ // 원소의 갯수 반환
		return top+1;
	}

	T& Top()const{
		if(isEmpty()) throw "원소가 없다고 시발아";
		return stackArray[top]; // top+1이 아닌 이유는 top이 인덱스 그 자체
	}

	void Push(const T& target){
		if(Size() == capacity){
			T* tmp = new T[capacity*2];
			copy(stackArray, stackArray+capacity,tmp);
			capacity *=2;
			delete[] stackArray;
			stackArray = tmp;
		}
		stackArray[++top] = target;
	}

	void Pop(){
		if(isEmpty()) "원소가 없다고 시발아";
		stackArray[top--].~T();
	}

	void printStack(){
		int start = 0;
		int end = this-> top;
		while(start<=end){
			cout<<stackArray[start++] << endl;
		}
	}

	void printCapacity(){
		cout << "이만큼 크다 시발아" <<this->capacity << endl;
	}
};