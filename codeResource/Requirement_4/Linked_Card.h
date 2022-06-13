#pragma once//헤더 파일 중복 삽입 방지
#include <iostream> //입출력 연산자 사용을 위한 iostream include
#include <string> // string 타입 사용을 위한 string include
#include <cstdlib> //srand를 사용하기 위한 cstdlib include
#include <ctime> //time을 사용하기 위한 ctime include

using namespace std; //  namespace 사용을 통해 std:: 생략
static const char* SHAPES = " SDHC"; // 카드의 모양을 나타내기 위한 정적 변수 생성, 이후 인덱싱으로 출력할 때 재사용
template<class T> class Chain; //Node에서 chain클래스로 friend선언하기 위한 전방 선언

class Card { // 기본적인 데이터를 구성하는 카드 객체
public:
	int number; //Card의 숫자
	char shape; //Card의 모양 S,D,H,C
	int shapingNum; //Card의 shape를 결정 해 주는 숫자
	int id; //카드간 크기를 비교할 때 하나의 숫자로 쉽게 비교하기 위함

	Card() {// 기본 생성자,
		int number = 0;
		char shape = NULL;
		int shapingNum = 0;
		int id = 0;
	}

	Card(int _number, int _shapingNum) {// constructor overloading , number와 shapingNum을 받아 새로운 카드를 생성함
		number = _number;
		shapingNum = _shapingNum;
		id = ((_shapingNum - 1) * 13) + (_number); //고유한 식을 통해 각 카드마다 기존 카드 룰에 맞는 크기를 할당
		setForm();
	}
	~Card() =default;

	void setForm(){//shapeNum 값에 따라서 Card 객체의 shape 결정하는 함수
		this->shape = SHAPES[shapingNum]; // string은 인덱싱 가능하기 떄문에 SHAPE를 정적 변수로 선언하고 인덱싱으로 고유 문자 할당
	}
};


template<class T> // 템플릿 클래스 선언
class Node {
	friend class Chain<T>; // Chain 클래스에서 Node클래스 사용을 위한 friend 선언
private:
	T data; // Card객체가 담길 멤버변수,  템플릿이기에 T타입으로 선언
	Node<T>* link; // 다음 node를 가르킬 포인터 변수

};

template<class T> //Node<T>를 받을 탬플릿 클래스 선언
class Chain {
private:
	Node<T>* front; // linkedList의 헤드가 되는 노드 front에 대한 주소 변수 선언
public:
	Chain() { // constructor 선언
		front = 0; // front노드의 디폴트 값
	}
	~Chain() =default; //  destructor 선언

	void printCard() { //  카드의 모양과 숫자 출력
		Node<T>* current = front; // 맨 첫번째 자리의 노드에 대해 변경없이 탐색하기 위해 첫 노드에 대한 포인터 복사.
		while (current != 0) { // 맨 끝 노드에 도달할 때 까지
			cout << current->data.shape // 카드 출력
				 << current->data.number
				 << " ";
			current = current->link; // 다음 노드 탐색을 위해 링크에 접근
		}
		cout << endl;
	};

	void order() { // 삽입된 카드 노드 들을 크기에 맞게 정렬
		Node<T>* current = front; // 맨 첫번째 자리의 노드에 대해 변경없이 탐색하기 위해 첫 노드에 대한 포인터 복사
		Node<T>* pre = 0; // 정렬되는 카드가 카드와 카드 사이에 있는 경우를 고려하기 위한 변수 선언

		while (current->link != 0) { // 맨 끝 노드에 도달할 때 까지
			if (current->data.id > current->link->data.id) { // 기준 노드가 다음 노드보다 크다면
				Node<T>* temp; // 노드 정보 손실을 막기 위한 임시 노드 포인터 변수 선언
				temp = current->link; // 타겟 노드의 링크 정보 저장
				current->link = temp->link; // 타겟 노드와 다음 노드의 위치를 바꾸기 때문에 다음노드의 링크를 타겟 노드 링크에 할당
				temp->link = current; // 다음 노드는 타겟노드의 위치에 도달, 다음 노드가 가리키는건 타겟 노드가 되어야 하기 떄문

				if (current != front) { // 자리가 바뀌는 노드가 노드와 노드 사이에 있을 때
					pre->link = temp; // current와 temp(뒤노드)가 자리가 바뀌었기 때문에 current를 가리키던 pre는 temp를 가리켜야 함
				}

				if (current == front) { // 자리가 바뀌는 두 노드를 제외한 카드가 없는 경우
					front = temp;
				}
				pre = temp; //
			}
			else { // 기준노드 < 다음노드 순서로 크기가 있는 경우
				break;
			}
			cout << "--Swapping--";
			printCard(); // 자리 변환 이후 전체 리스트 출력
		}

	}

	void push(T& o) {
		Node<T>* tmpNode = new Node<T>; //새로운 노드 객체 생성
		tmpNode->data = o; // initalize함수에서 받은 카드 데이터를 할당
		tmpNode->link = front;  //front는 노드 삽입을 위한 명목상의  헤드 노드, 디폴트 값으로 0을 가짐, 새로 추가할 노드 객체의 링크에 front정보 할당
		front = tmpNode; // 기존의 front 자리에 새로 추가한 노드 할당
		cout << "New Card : " //새로 추가한 노드 카드에 대한 정보 출력
			 << tmpNode->data.shape
			 << tmpNode->data.number
			 << endl;

		cout << "push : ";
		printCard(); // 푸쉬 함수 수행이후 전체 링크드 리스트 출력
		order(); // 순서 정렬 시행
	}

	void initializeChain(){ // 연결리스트 체인 객체 초기화

		srand((unsigned int)time(NULL));// rand호출마다 다른 값이 출력되기 위한 srand 및 time

		for(int i = 0; i<5; i++){ // 5장의 카드 삽입
			int num = (rand() % 13) + 1; // 1~13사이의 수 랜덤 생성
			int shpaingNum = (rand() % 4) + 1;// 1~4사이의 수 랜덤 생성
			Card tmpCard = Card(num, shpaingNum); //각 반복마다 임시 카드 객체 생성
			this->push(tmpCard); // 각 카드 push
		}

	}
};
