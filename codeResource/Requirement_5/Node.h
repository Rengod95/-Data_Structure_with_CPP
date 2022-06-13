#include <cstdlib>
#include <vector>
using namespace std;

class Node
{
public:
	int key;
	char value;
	Node* leftChild = nullptr;
	Node* rightChild = nullptr;
	Node () = default;
	Node(int _key, char _value, Node* _leftChild, Node* _rightChild) : key(_key), value(_value) ,leftChild(_leftChild), rightChild(_rightChild) { }

// 트리에 target 이 있다면 해당 노드 리턴
	Node* BST_SearchNode(Node* tree, int target)
	{
		if (tree == nullptr)
			return nullptr;

		if (tree->key == target)
			return tree;
		else if (tree->key > target)
			return BST_SearchNode(tree->leftChild, target);
		else if (tree->key < target)
			return BST_SearchNode(tree->rightChild, target);

	}

	void BST_InOrder(Node* tree, vector<int>& pos, vector<char>& keys)
	{
		if (tree == nullptr)
			return;
		BST_InOrder(tree->leftChild, pos, keys);
		pos.push_back(tree->key); // 출력
		keys.push_back(tree->value);
		BST_InOrder(tree->rightChild, pos, keys);

	}

	void BST_InsertNode(Node* tree, Node* node)
	{
		if (node->key <= tree->key) { // 현재 재귀 단계에서의 트리의 루트와 크기 비교 (서브트리의 루트)
			if (tree->leftChild == nullptr) { // 루트보다 작은데 마침 루트에게 왼쪽 자식이 없다면 루트의 왼쪽 자식으로 세팅 후 종료
				tree->leftChild = node;
				return;
			}
			else
				BST_InsertNode(tree->leftChild, node); // 루트보다 작은데 루트에게 왼쪽 자식이 있다면 거기에 추가될 수 없으므로 더 내려가야 함. 왼쪽 서브트리로 내려가기.
		}
		else if (node->key > tree->key) {  // 루트보다 큰데 마침 루트에게 오른쪽 자식이 없다면 루트의 오른쪽 자식으로 세팅 후 종료
			if (tree->rightChild == nullptr) {
				tree->rightChild = node;
				return;
			}
			else
				BST_InsertNode(tree->rightChild, node); // 루트보다 큰데 루트에게 오른쪽 자식이 있다면 거기에 추가될 수 없으므로 더 내려가야 함. 오른쪽 서브트리로 내려가기.
		}
	}

	Node* BST_SearchMinNode(Node* tree)
	{
		if (tree == nullptr)
			return nullptr;

		if (tree->leftChild == nullptr)
			return tree;
		else
			return BST_SearchMinNode(tree->leftChild);
	}

	Node* BST_RemoveNode(Node* tree, Node* parent, int target)
	{
		// target과 일치하는 노드는 삭제할 노드다.
		// 삭제할 노드의 위치가 되는 노드는 tree 에, 삭제할 노드의 부모는 parent 에 저장된다.
		// 삭제할 노드(tree)는 removedNode 에 복사해 옮겨두고 나중에 이를 리턴한다.
		// tree 의 값을 새롭게 세팅해 이제 삭제되고 새로운 노드로 대체된 것처럼 연산해준다.
		if(tree->key == target){
			cout << "최상위 노드는 삭제할 수 없습니다."<< endl;
			return nullptr;
		}
		if (tree == nullptr)
			return nullptr;

		Node* removedNode = nullptr;

		/* 삭제할 노드 탐색하기*/
		if (tree->key > target)
			removedNode = BST_RemoveNode(tree->leftChild, tree, target);
		else if (tree->key < target)
			removedNode = BST_RemoveNode(tree->rightChild, tree, target);
		else if (tree->key == target) { // 삭제할 노드 찾음
			removedNode = tree; // 삭제된 노드 리턴할거라 삭제 작업 전 캐싱

			// 1. 삭제하려는 노드의 자식 서브트리가 0 개 일때 (=단말노드)
			if (tree->leftChild == nullptr && tree->rightChild == nullptr) {
				if (parent->leftChild == tree)
					parent->leftChild = nullptr;
				if (parent->rightChild == tree)
					parent->rightChild = nullptr;
			}
				// 2. 삭제하려는 노드의 자식 서브트리가 1 개 일때
			else if (tree->leftChild == nullptr || tree->rightChild == nullptr) {
				Node* temp = nullptr;
				if (tree->leftChild != nullptr)
					temp = tree->leftChild;
				else
					temp = tree->rightChild;

				if (parent->leftChild == tree)
					parent->leftChild = temp;
				else
					parent->rightChild = temp;
			}
				// 3. 삭제하려는 노드의 자식 서브트리가 2 개 일 때
			else if (tree->leftChild != nullptr && tree->rightChild != nullptr) {
				Node* minNode_Of_BiggerNodes = BST_SearchMinNode(tree->rightChild);
				minNode_Of_BiggerNodes = BST_RemoveNode(tree, nullptr, minNode_Of_BiggerNodes->key);
				tree->key = minNode_Of_BiggerNodes->key;
			}
		}

		return removedNode;
	}


};


void initializeBST(){
	int select = 0;
	bool firstInput = true;
	int tmpKey;
	char tmpValue;
	Node tree(NULL,NULL, nullptr, nullptr);
	vector<int> treeKeys;
	vector<char> treeValues;

	while(true){
		cout << "1.입력 2.탐색 3.삭제 4.보기 5.종료" << endl;
		cin >> select;

		if(select == 1){
			cin >> tmpKey >> tmpValue;
			if(firstInput){
				tree.key = tmpKey;
				tree.value = tmpValue;
				cout << "헤드 노드 삽입"<< endl;
				firstInput = false;
			}
			else{
				tree.BST_InsertNode(&tree, new Node(tmpKey,tmpValue, nullptr, nullptr));
			}

			treeKeys.clear();
			treeValues.clear();
		}else if(select == 2){
			cin >> tmpKey;
			Node* tmp = tree.BST_SearchNode(&tree,tmpKey);
			cout << tmp->value << endl;
		} else if(select==3){
			cin >> tmpKey;
			tree.BST_RemoveNode( &tree, nullptr,tmpKey);
			treeKeys.clear();
			treeValues.clear();
		} else if(select == 4){
			tree.BST_InOrder(&tree,treeKeys,treeValues);
			cout << "Value : " <<endl;
			for(auto loop : treeValues)
			{
				cout  <<  loop<< " ";
			}
			cout<< endl;

			treeKeys.clear();
			treeValues.clear();
		}else if (select == 5){
			cout<< "종료되었습니다."<<endl;
			exit(0);
		}

	}

}