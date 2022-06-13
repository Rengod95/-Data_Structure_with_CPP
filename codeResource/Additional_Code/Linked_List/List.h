#include <iostream>
#include <algorithm>

using namespace std;
template<class T> class Chain;

template<class T>
class Node{
	friend class Chain<T>;
private:
	T data;
	Node* link;
public:
	Node()=default;
	Node(T _data, Node* _link = 0): data(_data) , link(_link){};
	~Node() = default;

	T& getData(){
		return this->data;
	}

	Node* getLinkData(){
		return this->link;
	}

	void setData(const T _data){
		this->data = _data;
	}

	void setLink(const Node* _link){
		this->link = _link;
	}
};

template<class T>
class Chain{
private:
	Node<T>* head=0;
	Node<T>* last = 0;
public:
	Chain() {head = 0;};
	Chain(Node<T>* _head) : head(_head){};
	~Chain() {delete head;};

	bool isEmpty(){
		return head == 0;
	}

	class iterator{
	public:
		Node<T>* current;
		iterator(Node<T>* _current): current(_current){};

		iterator& operator ++(){
			current = current->link;
			return *this;
		}

		iterator operator ++(int){
			iterator old = *this;
			current = current->link;
			return old;
		}

		T& operator *() const { return current->data;};
		T* operator ->() const{return &current->data;};
		bool operator !=(const iterator X){return this->current != X.current;};
		bool operator ==(const iterator X){return this->current == X.current;};
	};

	iterator begin(){
		return iterator(head);
	}

	iterator end(){
		return iterator(NULL);
	}

	void setLast() {
			iterator start = begin();
			for(Chain<T>::iterator iter = begin(); iter != end(); ++iter){
				if(iter.current->link == 0) last =  iter.current;
				break;
			}
	}

	void insertBack(const T& newData){
		if(!isEmpty()){
			last->link = new Node<T>(newData);
			last = last->link;
		}
		else{
			head = new Node<T>(newData);
			last = head;
		}
	}

	void deleteNode(const T& targetData){
		if(isEmpty()) throw "리스트가 비었어 시발아";
		if(last == head) head = head->link;
		else{
			Node<T>* prev = head;
			Node<T>* next = 0;
			for(Chain<T>::iterator iter = begin(); iter != end(); iter++){
				if(*iter == targetData){
					if(iter.current->link == 0){
						prev->link  = 0;
						last = prev;
						delete iter.current;
						return;
					}
					prev->link = iter.current->link;
					delete iter.current;
					return;
				}
				else{
					prev = iter.current;
				}
			}
		}
		cout<< "일치하는 노드가 없어 시발아" << endl;
		return;
	}

	void printList(){
		for(Chain<T>::iterator iter = begin(); iter!=end(); ++iter){
			if(isEmpty()) throw "원소가 없다고 시발아";
			cout << *iter << endl;
		}
	}

	void sumData(){
		T min = 0;
		for(Chain<T>::iterator iter = begin(); iter!=end(); ++iter){
			if(isEmpty()) throw "원소가 없다고 시발아";
			min += *iter;
		};
		cout<<min<<endl;
	}

	void Concatenate(Chain<T>& other){
		if(isEmpty()){
			head = other.head;
			last = other.last;
		}
		else{
			last->link = other.head;
			last = other.last;
		}
	}
};


