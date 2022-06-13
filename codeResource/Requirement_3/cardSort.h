#include <iostream> // 입출력을 위한 라이브러리 추가
#include <cstdlib> // 난수 생성을 위한 라이브러리 삽입
#include <ctime>  // 반복적인 난수 생성시 동일 값 생성을 막기 위핸 시간 라이브러리 삽입

static const char* SHAPES[] = { "C", "H","D"  , "S" };  // 카드의 모양에 따른 대소 구분 및 차별화를, 특성있는 변수이기 때문에 전역 객체로 선언
using namespace std; // std 라이브러리의 공간을 표준으로 사용

class Card{ // Card 클래스 선언 및 정의
private:
	int shape = -1; // 카드 모양
	int number = -1; // 카드 넘버 둘다 -1인 이유는 데큐에서 빈 객체를 표현할 때 -1인 경우 비었다는 것을 상정하기 위함.
	friend class Dequeue; //Dequeue 클래스에서 Card의 멤버 변수에 직접 접근하고 메소드를 활용할 수 있도록 하기 위함.
public:
	Card() { // 기본 생성자
	};
	Card(int shape, int number){ // 랜덤값을 이용해 카드 객체를 생성할 때 활용하기 위한 생성자
		this->shape = shape; // Private 멤버 변수에 직접적으로 접근하기 때문에 포인터 접근 연산자인 -> 사용
		this->number = number; // 마찬가지
	}

	static const bool compareCard(const Card& card1, const Card& card2){   //card1 > card2  "true" card2 > card1 "false" 어디서든 메서드를 사용할 수 있게 static const 메서드로 선언 및 정의
		if (card1.shape != card2.shape) { // 모양이 최우선순위로 비교됨, 모양이 다를 때와 같을 때를 나눔
			if (card1.shape > card2.shape) return true; //  S-D-H-C 순서대로 크기 비교
			else return false;
		}
		else {
			if (card1.number > card2.number) return true; // 넘버도 큰  순서대로 비교
			else return false;
		}
	}

	friend ostream& operator<<(ostream& os, Card& card){ // 출력 연산자 오버로딩, shape과 number 출력
		os  <<  SHAPES[card.shape] << card.number;
		return os;
	}
};

class Dequeue // Dequeue 클래스 선언 및 정의
{
private:
	Card* queue = new Card[6]; //  카드를 담을 배열 생성
	int front = 0;       // 앞
	int rear = 0;        // 뒤
	int cardCount = 0;       // 들어온 원소 갯수
	int size = 6;        // 크기

public:
	Dequeue(){ // 기본 생성자
		for (int i = 0; i < size; i++){
			queue[i] = Card(); // 카드를 담을 배열을 초기화
		}
	}

	bool is_full() { // 큐가 가득 찼으면 true 아니면 false 를 반환
		if ((rear + 1) % size == front){ // rear는 계속 추가를 하기 때문에 배열의 size를 초과할 수 있음, size로 나눈 나머지를 rear 와 front로 설정하면 항상 절대적인 index를 나타내게 됌
			cout << " full." << endl;
			return true;
		}
		return false;
	}

	bool is_empty() { // 큐에 원소가 하나도 없으면 front와rear가 같기 때문에 true , 아니면 False
		if (front == rear)
		{
			cout << "Empty." << endl;
			return true;
		}
		return false;
	}

	void print_dequeue_status(){ // 큐의 전반적인 상태를 출력
		cout << "front : " << front << endl;
		cout << "rear : " << rear << endl;
		cout << "size : " << size << endl;
		cout << "status" << endl;
		int next_index = front;
		cout << "[ ";
		while (next_index != rear){ // front+1과 rear가 같은 위치를 가르키면 순차적 탐색이 끝난 것
			next_index = (next_index + 1) % size;
			cout << queue[next_index]  << ",";
		}
		cout << "]" << endl;
	}

	Card get_front() {// front는 가장 첫번째 원소 앞을 가르키기 때문에 front+1 출력
		return queue[(front + 1) % size];
	}

	Card get_rear(){// rear 카드 반환
		return queue[rear];
	}

	int get_count() const { // 삽입된 카드의 갯수 반환
		return cardCount;
	}
	void push_front(Card& data) { // 가장 완쪽 원소의 앞을 가르키기 때문에 Front에 그대로 삽입
		if (is_full()) return;

		queue[front] = data;
		front -= 1;
		if (front < 0){ // 프론트는 음수가 될 수 없으므로 절대적 Front를 반환하기 위해 size를 더함
			front += size;
		}
		cardCount += 1;
	}

	void push_rear(Card& data){
		if (is_full()) return;

		rear = (rear + 1) % size; // rear 가 Size를 초과할 수 없으므로 절대적 size를 반환하기 위해 size로 나눔
		queue[rear] = data;

		cardCount += 1;
	}

	Card pop_front(){ //원하는 자리에 카드를 삽입하기 위해서 pop 한 카드를 리턴해야 함
		Card result = queue[(front + 1) % size];
		if (is_empty()){ // 비었을 때는 빈 카드를 리턴하여 빈 자리임을 알림
			return Card();
		}
		front = (front + 1) % size;
		cardCount -= 1;
		return result;
	}

	Card pop_rear(){ // 마찬가지로 Pop 한 카드의 정보를 가지고 있기 위해 pop 한 카드를 리턴함
		Card result = queue[rear];
		if (is_empty()){
			return Card();
		}
		rear -= 1;
		if (rear < 0){
			rear += size;
		}
		cardCount -= 1;
		return result;
	}

	void sortCard(Card& targetCard){ //들어갈 자리 찾아 삽입 실행
		int tmpF = (front+1)%size; // 실제 front에 영향을 주지 않으면서 큐 전체를 순차적으로 탐색하기 위해 임시 변수를 만듬
		int tmpR = rear; // tmpF 와 같은 역할의 rear
		int countF = 0; // front에서 해당
		int countR = 0;

		while(tmpF != rear+1){ // rear를 넘어가게 되면 큐의 모든 카드를 탐색한 것이 된다.
			if (Card::compareCard(targetCard, queue[tmpF])){
				tmpF = (tmpF+1) % size; // 삽입할 카드가 더 크면 true이기 때문에 다음 카드를 탐색해야 함
				countF++;
			}
			else if(!Card::compareCard(targetCard, queue[tmpF])) break; // 삽입할 카드가 더 작을 경우에는 비교 대상군의 카드 위치를 반환한다.
		}

		while (tmpR!= front%size){
			if (Card::compareCard(targetCard, queue[tmpR])) {
				tmpR = (tmpR-1) ;// 삽입할 카드가 더 크면 true이기 때문에 다음 카드를 탐색해야 함
				if(tmpR < 0) tmpR = tmpR + size; // 음수가 되면 안되기 때문에 절대적 위치를 가리키기 위함
				countR++;
			}
			else if(!Card::compareCard(targetCard, queue[tmpR])) break; // 삽입할 카드가 더 작을 경우에는 비교 대상군의 카드 위치를 반환한다.
		}

		if(tmpF == rear+1) {
			push_rear(targetCard);
		}
		else if( tmpR == front%size) {
			push_front(targetCard);
		}
		else{
			countR += 1;
			if(countR<countF){
				for(int i = 0; i<countR; i++){
					Card tmp =pop_rear();
					push_front(tmp);
					print_dequeue_status();
				}
				push_rear(targetCard);
				print_dequeue_status();
				for(int i = 0; i<countR; i++){
					Card tmp =pop_front();
					push_rear(tmp);
					print_dequeue_status();
				}
			}
			else if( countF<=countR){
				for(int i = 0; i<countF; i++){
					Card tmp =pop_front();
					push_rear(tmp);
					print_dequeue_status();
				}
				push_front(targetCard);
				print_dequeue_status();
				for(int i = 0; i<countF; i++){
					Card tmp =pop_rear();
					push_front(tmp);
					print_dequeue_status();
				}
			}
		}
	}

	void sortDequeue(Card& targetCard){ // 원하는 칸에 삽입
		if(get_count() == 0){ // 카드가 하나도 없을 때
			push_rear(targetCard);
			print_dequeue_status();
			return;
		}
		else if(get_count() == 1){ // 카드가 하나 일 때
			if (Card::compareCard(targetCard,queue[rear])) push_rear(targetCard); // 뒤 또는 앞에 삽입
			else push_front(targetCard);
			print_dequeue_status();
			return;
		}
		else if(get_count() >1){
			cout<< "두개 이상";
			this->sortCard(targetCard); // 삽입하려는 카드보다 큰 카드의 위치를 찾음
		}

	};

	void initializeDequeue() {
		Card* card_list = new Card[52];
		srand(time(NULL));
		srand((unsigned int)time(0));
		for (int i = 0; i < 52; i++){
			int cardShape = i % 4;
			int cardNum = (i % 13);
			card_list[i] = Card(cardShape, cardNum);
		}
		for (int i = 0; i < 100; ++i)
		{
			int id, id2;
			Card iTemp;
			id = rand() % 52;
			id2 = rand() % 52;

			iTemp = card_list[id];
			card_list[id] = card_list[id2];
			card_list[id2] = iTemp;
		}

		for(int i = 0; i<size-1; i++) sortDequeue(card_list[i]);
	}

};