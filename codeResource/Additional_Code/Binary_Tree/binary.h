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
	vector<char> dataVector;
	vector<int>keyVector;
public:
	BinaryTree(Node* node=0): root(node){};

	bool isEmpty(){
		return root == 0;
	}
	void visit(Node* N){
		keyVector.push_back(N->getNodeKey());
		dataVector.push_back(N->getNodeData());
	}
	void initVector(){
		keyVector.clear();
		dataVector.clear();
	}
	void getRoot(){
		return this->root;
	}

	Node* searchNode(int target){ return searchNode(root,target);}
	Node* searchNode(Node* tree, int target)
	{
		if (tree == nullptr){
			cout<<"Does not exist"<<endl;
			return nullptr;
		}
		if (tree->key == target) {
			return tree;
		}
		else if (tree->key > target) {
			return searchNode(tree->getRightChild(), target);
		}
		else if (tree->key < target) {
			return searchNode(tree->getLeftChild(), target);
		}
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

	void printBST(){
		initVector();
		inOrder();
		cout << "Value : " << endl;
		for (auto loop : dataVector){cout << loop << " ";}
		cout << endl;
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

	Node* minValueNode(Node* node)
	{
		Node* current = node;

		while (current && current->left != NULL)
			current = current->left;

		return current;
	}

	void removeNode(Node* searchNode, Node* searchNodeParent ,int targetKey){
		if(this->isEmpty()){
			cout << "루트 노드가 존재하지 않습니다."
			return;
		}
		if(targetKey < target->getNodeKey()){ // 타겟 아직 못찾음, 왼쪽으로 탐색
			removeNode(searchNode->getLeftChild(), searchNode,targetKey);
		}
		else if (targetKey > parent->getNodeKey()){ // 타겟 아직 못찾음, 오른쪽으로 탐색
			removeNode(searchNode->getRightChild(),searchNode,targetKey);
		}
		else{
			if(!searchNode->getRightChild() && !searchNode->getLeftChild()){// searchNode(삭제할 노드)가 리프노드 인 경우
				delete searchNode;
				searchNode= 0;
			}
			else if(searchNode->getLeftChild() == 0){ // 하나의 차일드만 존재함, 겹치는 경우를 신경 쓸 필요가 없음
				Node* tmp = searchNode->getRightChild();
				delete searchNode;
				searchNode = tmp;
			}
			else if(searchNode-> getRightChild() == 0){
				Node* tmp = searchNode->getLeftChild();
				delete searchNode;
				searchNode = tmp;
			}
			Node* tmp = minValueNode(searchNode->getRightChild());
			delete minValueNode(searchNode->getRightChild());
			tmp->getRightChild() = searchNode->getRightChild();
			tmp->getLeftChild() = searchNode->getLeftChild();
			delete searchNode;
			searchNode = tmp;
			searchNodeParent->getRightChild() = tmp;
		}

	}

	void initializeBST(){
		int select = 0;
		bool firstInput = true;
		while(true){
			cout << "1.입력 2.탐색 3.삭제 4.보기 5.종료" << endl;
			cin >> select;
			if (select == 1) {
				if(firstInput) {root = inputNode(); firstInput = false;}
				else{insertNode(inputNode());}
			}
			else if (select == 2) {
				int tmpK= 0;
				cin >> tmpK;
				Node* tmp = searchNode(tmpK);
				cout << tmp->getNodeData() << endl;
			}
			else if (select == 3) {
				int tmpK= 0;
				cin >> tmpK;
				tree->BST_RemoveNode(tree, nullptr, tmpKey);
				treeKeys.clear();
				treeValues.clear();
			}
			else if (select == 4) {
				tree->BST_InOrder(tree, treeKeys, treeValues);
				cout << "Value : " << endl;
				for (auto loop : treeValues)
				{
					cout << loop << " ";
				}
				cout << endl;

				treeKeys.clear();
				treeValues.clear();
			}
			else if (select == 5) {
				cout << "종료되었습니다." << endl;
				exit(0);
			}



		}
	}


};
