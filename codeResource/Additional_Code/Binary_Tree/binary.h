#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<class T> class BinaryTree;
template<class T>
class Node{
	friend class BinaryTree<T>;
private:
	T data;
	int key;
	Node<T>* leftChild;
	Node<T>* rightChild;
public:
	Node(T _data=0, int _key=0, Node<T>* _left = 0, Node<T>* _right=0): data(_data), key(_key), leftChild(_left),rightChild(_right){};
	Node(){
	}
	~Node(){delete leftChild; delete rightChild;};
};
// var++ => var = var + 1
template<class T>
class BinaryTree{
private:
	Node<T>* root;
	vector<Node<T>*> nodes;
public:
	BinaryTree(T* node=0): root(node){};

	bool isEmpty(){
		return root == 0;
	}
	void visit(Node<T>* N){
		nodes.push_back(N);
	}

	void inOrder(){
		inOrder(root);
	}
	void inOrder(Node<T>* currentNode){
		if(currentNode){
			inOrder(currentNode->leftChild);
			visit(currentNode);
			inOrder(currentNode->rightChild);
		}
	}

	void preOrder(){
		preOrder(root);
	}
	void preOrder(Node<T>* currentNode){
		if(currentNode){
			visit(currentNode);
			preOrder(currentNode->leftChild);
			preOrder(currentNode->rightChild);
		}
	}

	void postOrder(){
		postOrder(root);
	}
	void postOrder(Node<T>* currentNode){
		if(currentNode){
			postOrder(currentNode->leftChild);
			postOrder(currentNode->rightChild);
			visit(currentNode);
		}
	}

	void nonRecurInOrder(){
		vector<Node<T>*> s;
		Node<T>* currentNode = root;
		while (currentNode){
			s.push_back(currentNode);
			currentNode=currentNode->leftChild;
		}
		if(s.empty()) return;
		currentNode = s.end(); s.pop_back();
		visit(currentNode);
		currentNode = currentNode->rightChild;
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
