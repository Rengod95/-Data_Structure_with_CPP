//template<class T>
//class Bag{
//private:
//	T *bagArray;
//	int capacity;
//	int top;
//
//public:
//	Bag(int bagCapacity) : capacity (bagCapacity){ //capacity로 배열을 동적 생성
//		if(capacity<1) throw "Capacity should be bigger than 0";
//		bagArray = new T[capacity];
//		top = -1;
//	}
//	Bag() = default;
//	~Bag(){delete[] bagArray;}
//
//	int Size(){ // 백의 원소 개수
//		return top+1;
//	}
//	bool isEmpty(){ // 백에 원소가 있는지 없는지
//		return Size()==0;
//	}
//
//	void Push(const T& target){
//		if(Size() == this->capacity){
//			T* tmp = new T[this->capacity * 2];
//			copy(this->bagArray,bagArray+capacity,tmp);
//			delete[] bagArray;
//			bagArray = tmp;
//		}
//		bagArray[++top] = target;
//	}
//
//	void Pop(){
//		if(isEmpty()) throw "Bag is already empty";
//		int deletePos = top/2;
//		copy(bagArray+deletePos+1,bagArray+top+1,bagArray+deletePos);
//	}
//};

template<class T>
class Bag{
private:
	T* bagArray; // 자료형 담을 배열
	int capacity; // 전체 배열의 크기
	int top; // 가장 마지막 원소를 가리키는 인덱스
public:
	Bag(int _capacity): capacity(_capacity){
		if(capacity < 1) throw " no";
		bagArray = new T[capacity]; // capacity를 기준으로 동적으로 배열 생성
		top = -1;
	}
	Bag()=default;
	~Bag(){delete[] bagArray;} // 파괴자는 동적할당된 배열의 메모리를 삭제해야함

	int Size(){
		return top+1; // top은 배열의 index기준이기 때문에 +1 해야 원소 개수
	}

	bool isEmpty(){
		return Size() == 0; // size함수는 top+1을 반환, top+1 이 0이면 원소가 추가된게 아무것도 없는 것 이기 때문에 빈 배열임
	}

	void push(T& target){
		if(Size() == this->capacity){ // 원소의 개수 == 배열의 크기 => 꽉 참 => 2배로 늘림
			T* tmp = new T[capacity*2];
			copy(bagArray,bagArray+capacity,tmp);    // bacArray 포함, bagArray+capacity -1 까지
			this-> capacity *=2;
			delete[] bagArray;
			bagArray = tmp;
		}
		bagArray[++top] = target;
	}

	void pop(){
		if(isEmpty()) throw "empty";
		int deletePos = top/2;  // bagArray[deletePos+1] => *(bagArray+deletePos+1)
		copy(bagArray+deletePos+1,bagArray+top+1,bagArray+deletePos);
		bagArray[top--].~T(); // 원소 하나가 삭제 됐으니 top이 가리키는 공간은 이제 빈공간이므로 메모리 삭제, 한칸 앞으로 당김 +1을 안하는 이유는 인덱스 이기 때문
	}

};