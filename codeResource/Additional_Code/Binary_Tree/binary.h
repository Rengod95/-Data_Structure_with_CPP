#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class BinarySearchTree;

class Node{
	friend class BinarySearchTree;
private:
	char data;
	int key;
	Node* leftChild;
	Node* rightChild;
public:
	Node( int _key=0, char _data=0, Node<T>* _left = 0, Node<T>* _right=0): data(_data), key(_key), leftChild(_left),rightChild(_right){};
	Node(){
	}
	~Node(){delete leftChild; delete rightChild;};

	void getLeftChild(){
		return this->leftChild;
	}
	void getRightChild(){
		return this->rightChild;
	}
	void getNodeData(){
		return this->data;
	}
	void getNodeKey(){
		return this->key;
	}
};

class BinarySearchTree{
private:
	Node* root;
	vector<Node*> nodes;
public:
	BinaryTree(Node* node=0): root(node){};

	bool isEmpty(){
		return root == 0;
	}
	void visit(Node* N){
		nodes.push_back(N);
	}
	void getRoot(){
		return this->root;
	}

	void inOrder(){
		inOrder(root);
	}
	void inOrder(Node* currentNode){
		if(currentNode){
			inOrder(currentNode->getLeftChild());
			visit(currentNode);
			inOrder(currentNode->getRightChild());
		}
	}

	Node* inputNode(){
		char _data;
		int _key;
		cin >> _key >> _data << endl;
		Node* tmp = new Node(_key, _data,0,0);
		return tmp;
	}

	void insertNode(Node* target){
		insertNode(root, target);
	}
	void insertNode(Node* parent, Node* target){
		if(target->getNodeKey() <=  parent->getNodeKey()){
			if(parent->getLeftChild() == 0){
				parent->getLeftChild() = target;
				return;
			}
			else insertNode(parent->getLeftChild(), target);
		}
		else if(target->getNodeKey() > parent->getNodeKey()){
			if(parent->getRightChild() == 0){
				parent->getRightChild() = target;
				return;
			}else insertNode(parent->getRightChild(), target);
		}
	}

	void removeNode(Node* parent, Node* child, int targetKey){
		if(this->isEmpty()){
			cout << "루트 노드가 존재하지 않습니다."
		}



	}








	void levelOrder(){
		vector<Node<T>*> s;
		Node<T>* currentNode = root;
		while (currentNode){
			visit(currentNode);
			if(currentNode->leftChild) s.push_back(currentNode->leftChild);
			if(currentNode->rightChild) s.push_back(currentNode->rightChild);
			if(s.empty()) return;
			currentNode = s.front(); s.pop_front();
		}
	}


};
