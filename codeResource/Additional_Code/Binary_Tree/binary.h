#include <iostream> // 입출력을 위한 삽입
#include <vector> // visit에 활용할 벡터 객체 사용
using namespace std; // 네임 스페이스 선언

class BinarySearchTree; // 클래스 관계 정의를 위한 전방 선언

class Node{ // 노드 객체
	friend class BinarySearchTree; // BST가 노드 객체를 관리함
private:
	char data; // 문자를 담을 멤버
	int key; // 각 노드를 인식할 키 멤버
	Node* leftChild; // 해당 노드가 가리키는 leftchild
	Node* rightChild; // 해당 노드가 가리키는 rightChild
public:
	Node( int _key=0, char _data=0, Node* _left = 0, Node* _right=0): data(_data), key(_key), leftChild(_left),rightChild(_right){}; // 생성자 오버로딩을 통해 입력받은 값을 토대로 노드 인스턴스가 생성될 수 있도록 함
	Node(){
	}
	~Node(){};

	Node* getLeftChild(){ // 해당 노드의 leftChild를 반환
		return this->leftChild;
	}
	Node* getRightChild(){ // 해당 노드의 rightChild를 반환
		return this->rightChild;
	}
	char getNodeData(){ // 해당 노드의 Data(문자 값을 반환)
		return this->data;
	}
	int getNodeKey(){ // 해당 노드의 key를 반환
		return this->key;
	}
	// 최대한 캡슐화 원칙을 지키기 위한 멤버 변수 반환 메소드들을 정의 함.
};

class BinarySearchTree{
private:
	Node* root; // 트리의 최초 루트 노드에 대한 정보를 담는 멤버
	vector<char> dataVector; // 중위순회에 따른 문자 출력시 활용 할 벡터 객체
	vector<int>keyVector; // 확장성을 염두해 둔 키 벡터
public:
	BinarySearchTree(Node* node=0): root(node){}; // 처음 트리가 생성되었을 때 루트 노드에 아무것도 없음을 명시 => 포인터 주소가 0(=nullptr)

	bool isEmpty(){ // 루트 노드의 포인터가 존재하지 않으면 빈 트리
		return root == 0;
	}

	void visit(Node* N){ // 키 값의 순서에 따라 inorder순으로 정렬해서 표시하기 위한 메소드
		keyVector.push_back(N->getNodeKey());
		dataVector.push_back(N->getNodeData());
	}

	void initVector(){ // 반복적 출력시 벡터에 기존에 출력된 원소에 대한 데이터를 초기화 하기 위함
		this->keyVector.clear();
		this->dataVector.clear();
	}

	Node* getRoot(){ // 해당 트리의 루트 노드에 대한 정보를 반환 함
		return this->root;
	}

	Node* searchNode(int target){ return searchNode(root,target);} // 메서드 사용의 편의성을 위한 오버로딩, 어짜피 순회는 root노드 부터 시행하니 target 인자만 받아도 자동적으로 순회 위치를 잡아 메서드를 작동하게 함.
	Node* searchNode(Node* tree, int target)
	{
		if (tree == nullptr){
			cout<<"Does not exist"<<endl;
			return nullptr;
		}
		if (tree->key == target) {// 현재 탐색하고 있는 노드(tree)가 타겟이라면 현재 노드 반환
			return tree;
		}
		else if (tree->key > target) { // 현재 탐색하고 있는 노드의 키 값이 타겟보다 크다면, 타겟은 현재 노드의 왼쪽 child에 존재함
			return searchNode(tree->getLeftChild(), target); // tree를 tree의 leftchild로 바꾸고 리커시브 수행
		}
		else if (tree->key < target) { // 현재 탐색하고 있는 노드의 키 값보다 타겟이 더 크다면, 타겟은 현재 노드의 오른쪽에 위치함.
			return searchNode(tree->getRightChild(), target); // tree 를 tree의 rightchild로 바꾸고 리커시브 수행
		}
	}
	void inOrder(){ // 인자 전달의 편의를 위한 오버로딩
		inOrder(root);
	}
	void inOrder(Node* currentNode){ // 중위 순회 형태로 탐색하며 벡터에 원소 전달
		if(currentNode){ // 현재 탐색하고 있는 노드가 nullptr이 되면 바로 이전의 노드는 리프노드이기 때문에 탐색 종료, 이전의 재귀단계로 복귀
			inOrder(currentNode->getLeftChild());
			visit(currentNode);
			inOrder(currentNode->getRightChild());
		}
	}

	void printBST(){ // 중위순회를 통한 노드 출력 메소드
		initVector(); // 이전 출력으로 인해 기존 백터에 캐싱되어 있는 원소 정보 삭제
		inOrder(); // 중위 순회
		cout << "Value : " << endl;
		for (auto loop : dataVector){cout << loop << " ";} // enhanced loop를 통한 벡터 원소를 순차 출력
		cout << endl;
	}

	Node* inputNode(){ // 키와 데이터 값을 받아 새로운 노드를 생성해 반환
		char _data;
		int _key;
		cin >> _key >> _data;
		Node* tmp = new Node(_key, _data,0,0);
		return tmp;
	}

	void insertNode(Node* target){// 인자 전달의 편의를 위한 오버로딩
		insertNode(root, target);
	}

	void insertNode(Node* parent, Node* target){ // 루트 노드부터 시작하여 적절한 위치에 전달받은 노드포인터 삽입
		if(target->getNodeKey() <=  parent->getNodeKey()){ // 삽입하려는 노드의 키가 현재 탐색하고 있는 노드의 키 보다 작은 경우
			if(parent->getLeftChild() == 0){ // 현재 탐색중인 노드가 리프 노드일 때
				parent->leftChild = target; // 현재 탐색중인 노드의 왼쪽 자식으로 삽입
				return;
			}
			else insertNode(parent->getLeftChild(), target); // 현재 노드의 레프트 차일드부터 다시 탐색 시작
		}
		else if(target->getNodeKey() > parent->getNodeKey()){ // 삽입하려는 노드의 키가 현재 탐색중인 노드의 키보다 큰 경우
			if(parent->getRightChild() == 0){ // 탐색중인 노드가 리프 노드 일 때
				parent->rightChild = target; // 현재 탐색중인 노드의 오른쪽 자식으로 삽입
				return;
			}else insertNode(parent->getRightChild(), target); // 리프노드가 아닌 경우 탐색중인 노드의 오른쪽부터 다시 탐색 시작
		}
	}

	Node* minValueNode(Node* node) // 노드 삭제시 서브트리가 두 개 안 경우 삭제할 노드를 대체할 노드를 찾기 위한 메소드
	{
		Node* current = node;

		while (current && current->leftChild != NULL) // 최소값의 노드는 어느 서브트리던 왼쪽 자식으로 위치함
			current = current->leftChild; // 레프트 차일드가 없는 리프 노드에 도달할 때 까지 반복
		return current;
	}
	void removeNode(int targetKey){// 인자 전달의 편의를 위한 오버로딩
		removeNode(root,nullptr,targetKey)	; // 맨 처음 루트 노드는 부모가 존재하지 않으므로 nullptr 전달
	}
	void removeNode(Node* searchNode, Node* searchNodeParent ,int targetKey){ // 탐색하고 있는 노드와, 해당 노드의 부모 노드에 대한 정보, 찾으려는 노드의 키 값에 대한 정보 세 가지가 필요함
		if(this->isEmpty()){// 트리가 비어 있는 경우는 삭제할 노드가 없음
			cout << "루트 노드가 존재하지 않습니다.";
			return;
		}
		if(targetKey < searchNode->getNodeKey()){ // 타겟 아직 못찾음, 왼쪽으로 탐색
			removeNode(searchNode->getLeftChild(), searchNode,targetKey);
		}
		else if (targetKey > searchNode->getNodeKey()){ // 타겟 아직 못찾음, 오른쪽으로 탐색
			removeNode(searchNode->getRightChild(),searchNode,targetKey);
		}
		else{ // 타겟노드를 찾은 경우
			if( searchNode->getLeftChild() == nullptr && searchNode->getRightChild() == nullptr){// searchNode(삭제할 노드)가 리프노드 인 경우 자식이 하나도 존재하지 않으므로
				if(searchNodeParent->getLeftChild() == searchNode){ searchNodeParent->leftChild = nullptr;} // 삭제할 노드를 지목하는 부모가 가리키는 부분을 null로 처리하면 됌
				if(searchNodeParent->getRightChild() == searchNode){ searchNodeParent->rightChild = nullptr;}
				return;
			}
			else if(searchNode->getLeftChild() == nullptr){ // 삭제할 노드가 하나의 자식만 가지므로 자신의 부모에 자신의 자식을 링크하면 됌
				searchNode  = searchNode->getRightChild();
				searchNodeParent->rightChild = searchNode;
				return;
			}
			else if(searchNode-> getRightChild() == nullptr){ // 자식이 하나지만 위치만 다름
				searchNode = searchNode->getLeftChild();
				searchNodeParent->leftChild = searchNode;
				return;
			} else{ // 서브트리 두개가 존재하는 경우
				Node* tmp = minValueNode(searchNode->getRightChild()); // 오른쪽 서브트리의 최소 값을 삭제할 노드 자리에 대체해야 하므로 탐색
				delete minValueNode(searchNode->getRightChild()); // 오른쪽 서브트리
				tmp->rightChild= searchNode->getRightChild(); // 삭제할 노드의 자식들을 대체할 노드에 연결시킴
			    tmp->leftChild = searchNode->getLeftChild();            
			    delete searchNode; // 타겟 노드 메모리 삭제
			    searchNode = tmp; // 기존 타겟 노드 주소에 대체할 노드로 대체
			    searchNodeParent->rightChild = tmp; //  부모의 자식을 교체
			    return;
			}
		}

	}

	void initialize(){ // BST 살행 함수
		int select = 0; // 선택 기능 판별 멤버
		bool firstInput = true; // 헤드 노드의 존재 유무를 판별
		while(true){
			cout << "1.입력 2.탐색 3.삭제 4.보기 5.종료" << endl;
			cin >> select;
			if (select == 1) {
				if(firstInput) {root = inputNode(); firstInput = false;} // 노드 생성 메서드를 사용해 루트 노드 생성(루트 노드가 없을 때)
				else{insertNode(inputNode());} // 루트노드가 존재하면 삽입 메서드 실행
			}
			else if (select == 2) { // 원하는 노드 찾기
				int tmpK= 0;
				cin >> tmpK;
				Node* tmp = searchNode(tmpK); //  키값이 일치하는 노드 탐색
				cout << tmp->getNodeData() << endl;
			}
			else if (select == 3) { // 노드 삭제
				int tmpK= 0;
				cin >> tmpK;
				removeNode(tmpK); // 키값이 일치하는 노드 삭제
			}
			else if (select == 4) { // 중위 순회로 출력
				printBST();
			}
			else if (select == 5) { // 프로그램 종료
				cout << "종료되었습니다." << endl;
				exit(0);
			}



		}
	}


};
