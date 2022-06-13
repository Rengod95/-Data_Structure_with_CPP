#include <iostream>
using namespace std;

//template<class T>
//class Circular_Expandable_Queue{
//private:
//	T* queueArray;
//	int capacity;
//	int front;
//	int rear;
//public:
//	Circular_Expandable_Queue(int _capacity): capacity(_capacity){
//		if(capacity <1) throw "크기가 1보단 커야지 시발아";
//		queueArray = new T[capacity];
//		front, rear = 0;
//	}
//
//	bool isEmpty(){ // 원형 큐에서 시작점 == 끝점 인 경우는 단 하나의 원소도 들어가지 않은 경우임, rear%capacity를 적지 않는 이유는 원소가 가득 찬 경우에도 front와 같아지는 경우가 생기기 때문임.
//		return front == rear;
//	}
//
//	bool isFull(){
//		return front == (rear+1)%capacity;
//	}
//
//	T& printFrontElement(){
//		if(isEmpty()) throw "큐가 비었어 시발아";
//		return queueArray[front+1];
//	}
//
//	T& printRearElement(){
//		if(isEmpty()) throw "큐가 비었어 시발아";
//		return queueArray[rear];
//	}
//
//	void push(const T& target){
//		if(isFull()){
//			T* tmp = new T[capacity*2];
//			copy(queueArray+front+1,queueArray+capacity, tmp); //[first, last) 범위의 모든 요소
//			copy(queueArray, queueArray+front,tmp+capacity-front-1);
//			capacity *= 2;
//			delete [] queueArray;
//			queueArray = tmp;
//		}
//		rear = (rear+1)%capacity;
//		queueArray[rear] = target;
//	}
//
//	void pop(){
//		if(isEmpty()) throw "큐가 비었다고 시발아";
//		front = (front+1)%capacity;
//		queueArray[front].~T();
//	}
//
//	void printQueue(){
//		int start = front;
//		int end = rear;
//		while(start<=end){
//			cout << queueArray[start++] << endl;
//		}
//	}
//};

template<class T>
class Queue{
private:
	T* array;
	int capacity, front, rear;
public:
	Queue(int _capacity): capacity(_capacity){
		if(capacity<1) throw "빈칸 하나는 장식이냐 시발?";
		array = new T[capacity];
		front, rear = 0;
	}
	Queue() = default;
	~Queue(){delete [] array;};

	bool isEmpty(){
		return front == rear;
	}

	bool isFull(){
		return front == (rear+1)%capacity;
	}

	T& printFrontElement(){
		return array[(front+1)&capacity]; // capacity로 나눠주는 이유는 배열에서 front가 맨 끝 원소를 가리키고 있는 경우를 생각하면 됌, 무조건 +1을 더해줘야하니 오버플로우 발생 가능성을 차단
	}

	T& printRearElement(){
		return array[rear];
	}

	void push(T& target){
		if(isFull()){
			T* tmp = new T[capacity*2];
			copy(array+front+1,array+capacity,tmp);
			copy(array,array+rear+1,tmp+capacity-front-1);
			capacity *= 2;
			delete [] array;
			array = tmp;
		}
		rear = (rear+1)%capacity;
		array[rear] = target;
	}

	void pop(){
		if(isEmpty()) "비었는데 원소를 어떻게 빼 시발";
		front = (front+1) % capacity;
		array[front].~T();
	}

	void printQueue(){
		int start = front;
		int end = rear;
		while(start<=end){
			cout << array[start++] << endl;
		}
	}
};