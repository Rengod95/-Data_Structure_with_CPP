#include <iostream>
using namespace std;

template<class T>
class Node{
private:
	T data;
	 Node<T>* left,right;
public:
};

template<class T>
class Double_List{
private:
	Node<T>* head;
public:
	void deleteNode(Node<T>* target){
		if(target==head) throw "첫번째는 못지워 시발아";
		target->left->right = target->right;
		target->right->left = target->left;
		delete target;
	}

	void insert(Node<T> *targetLeft, Node<T>* target){
		target->left = targetLeft;
		target->right = targetLeft->right;
		targetLeft->right = target;
		target->right->left = target;
	}



};