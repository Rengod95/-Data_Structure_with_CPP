#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
class Deque{
private:
	T* array;
	int front, rear, capacity;
	int count;
public:
	Deque(int _capacity): capacity(_capacity){
		if(capacity<1) throw "빈칸 하나는 장식이냐 시발아";
		array = new T[capacity];
		front=0;
		rear = 0;
		count = 0;
	}
	Deque(){
		array = new T[1];
		front,rear,count = 0;
	}
	~Deque(){
		delete[] array;
	}
	bool isEmpty();
	bool isFull();
	int getFrontIndex();
	int getRearIndex();
	T getFrontNode();
	T getRearNode();
	T* expandQueue();
	void pushBack(const T& target);
	void pushFront(const T& target);
	void popBack();
	void popFront();
	void printDeque();
};

template<class T>
bool Deque<T>::isEmpty() {
	return front==rear;
}

template<class T>
bool Deque<T>::isFull() {
	return front == (rear+1)%capacity;
}

template<class T>
T* Deque<T>::expandQueue(){
	T* tmp = new T[capacity*2];
	copy(array, array+capacity,tmp);
	capacity *= 2;
	delete[] array;
	array = tmp;
}


template<class T>
void Deque<T>::pushFront(const T &target) {
	if(isFull()) expandQueue();
	array[front--] = target;
	if(front<0) front+=capacity;
	count++;
}

template<class T>
void Deque<T>::pushBack(const T &target) {
	if(isFull()) expandQueue();
	rear = (rear+1)%capacity;
	array[rear] = target;
	count++;
}

template<class T>
void Deque<T>::popFront() {
	if(isEmpty()) throw "큐가 비었어 시발아";
	front = (front+1)%capacity;
	count--;
}

template<class T>
void Deque<T>::popBack() {
	if(isEmpty()) throw "큐가 비었어 시발아";
	rear -= 1;
	if(rear < 0) rear += capacity;
	count--;
}

template<class T>
int Deque<T>::getFrontIndex() {
	cout << "Front : " << front << endl;
	return front;
}

template<class T>
int Deque<T>::getRearIndex() {
	cout << "Rear : " << rear << endl;
	return rear;
}

template<class T>
T Deque<T>::getFrontNode() {
	return array[(front+1)%capacity];
}

template<class T>
T Deque<T>::getRearNode() {
	return array[rear];
}

template<class T>
void Deque<T>::printDeque() {
	int begin = (front+1)%capacity;
	int end = (rear+1)%capacity;
	while(begin != end){
		cout<< "Deque_Index : " << begin << " Data : " << array[begin++] << endl;
		if(begin == capacity) begin = begin%capacity;
	}
}