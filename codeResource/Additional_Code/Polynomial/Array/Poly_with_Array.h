#include <algorithm>

using namespace std;
class Polynomial;

class Term{
	friend class Polynomial;
private:
	float coef;
	int exp;
public:
	Term(float  _coef=0, int _exp=0){
		coef = _coef;
		exp = _exp;
	}
};

class Polynomial{
private:
	Term* termArray;
	int capacity;
	int termCount;
public:
	Polynomial(int _capacity=1){
		termArray= new Term[_capacity];
		capacity = _capacity;
		termCount = 0;
	}

	void newTerm(const float c, const int e){
		if(capacity == termCount){
			Term* tmp = new Term[capacity*2];
			copy(termArray,termArray+capacity, tmp);
			capacity *= 2;
			delete[] termArray;
			termArray = tmp;
		}
		termArray[termCount++] = Term(c,e);
	}

	Polynomial add(const Polynomial& target){
		int aPos=0, bPos = 0;
		Polynomial C;
		while(termArray[aPos].exp && target.termArray[bPos].exp ){
			if(termArray[aPos].exp == target.termArray[bPos].exp){
				int sumCoef = termArray[aPos].coef + target.termArray[bPos].coef;
				if(sumCoef) C.newTerm(sumCoef, termArray[aPos].exp);
				aPos++;bPos++;
			}
			else if (termArray[aPos].exp < target.termArray[bPos].exp){
				C.newTerm(target.termArray[bPos].coef, target.termArray[bPos].exp);
				bPos++;
			}
			else{
				C.newTerm(termArray[aPos].coef, termArray[aPos].exp);
				aPos++;
			}
		}
		while(aPos <= termCount){
			C.newTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
		while(bPos<=target.termCount){
			C.newTerm(target.termArray[bPos].coef, target.termArray[bPos].exp);
			bPos++;
		}
	}

};