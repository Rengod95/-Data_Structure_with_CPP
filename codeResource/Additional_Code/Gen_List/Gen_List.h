
template<class T> class GenList;

template<class T>
class Node{
private:
	bool tag;
	Node<T>* next;
	union {
		T data;
		Node<T>* down;
	};
};

template<class T>
class GenList{
private:
	Node<T>*first;
public:

	void copyList(const GenList<T>& L){ first = L.first;};

	Node<T>* copyList(Node<T>* P){
		Node<T>* Q = 0;
		if(P){
			Q = new Node<T>;
			Q->tag = P->tag;
			if(!Q->tag) Q->data = P->data;
			else Q->down = copyList(P->down);
			Q->next = P->next;
		};
		return Q;
	}

	bool operator ==( const GenList<T>& L){
		return Equal(first,L.first);
	}

	bool Equal(Node<T>* n1, Node<T>*n2){
		if((!n1)&&(!n2)) return true;
		if((n1) && (n2) && (n1->tag) && (n2->tag)){
			if(n1->tag){
				return Equal(n1->down,n2->down) && Equal(n1->next, n2->next);
			}else (n1->data == n2->data) && Equal(n1->next,n2->next);
		}
	}


};