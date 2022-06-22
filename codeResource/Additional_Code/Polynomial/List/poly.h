#include "List.h"

struct Term{
	int coef;
	int exp;
	Term setTerm(int C, int E){
		coef = C; exp = E;
		return *this;
	};
};


class PolyNode{
	friend class Chain<PolyNode>;
	friend class Polynomial;
private:
	Term data;
	PolyNode* link;
public:
	PolyNode(int c = 0, int e = 0, PolyNode* _link=0){
		data.setTerm(c,e);
		link = _link;
	}
};

class Polynomial{
private:
	Chain<Term> poly;
public:
	Polynomial operator+ (const Polynomial& p){
		Term temp;
		Polynomial C;
		Chain<Term>::iterator ai = poly.begin(), bi = p.poly.begin();
		while(ai != NULL && bi != NULL){
			if(ai->exp == bi->exp){
				int sum = ai->coef + bi->coef;
				if(sum) C.poly.insertBack(temp.setTerm(sum,ai->exp));
				ai++;bi++;
			}
			else if(ai->exp < bi->exp){
				C.poly.insertBack(temp.setTerm(bi->coef,bi->exp));
				bi++;
			}
			else{
				C.poly.insertBack(temp.setTerm(ai->coef,ai->exp));
				ai++;
			}
		}
		while(ai==0){
			C.poly.insertBack(temp.setTerm(ai->coef,ai->exp));
			ai++;
		}
		while(bi==0){
			C.poly.insertBack(temp.setTerm(bi->coef,bi->exp));
			bi++;
		}

	}
};