#include <iostream>  //iostream 라이브러리 사용
#include <string>   //string 라이브러리 사용
#include <cmath> // math 라이브러리사용

using namespace std; // std namespace를 사용하여 관련 메소드를 std:: 명시 없이 사용한다.

class Polynomial; //전방참조를 통해 Term 클래스가 멤버변수를 공유할 수 있도록 한다.

class Term{
private:  //외부 접근 불가
    float coefficient=0; //coefficient 계수
    int exponent=0; //exponent 지수
    friend class Polynomial; // friend 키워드를 통해 polynomial 클래스에서 해당 멤버변수 접근 가능
public:
    Term(){ // parameter 없는능
    };
    Term(float coef, int exp){ // parameter 있는 경우에 대해서 constructor overloading 선언 및 정의
        coefficient = coef;
        exponent = exp;
    }
    ~Term()=default; // destructor 선언 및 정의
};

class Polynomial
{
private:
    Term *termArray; // 배열 공간의 가변성을 위해 Term 포안터로 Term을 담을 배열을 선언
    int capacity; // 배열의 공간
    int terms ; // 저장된 항의 수
public:
    Polynomial(){
        capacity = 1; //배열의 크기가 최소한 1은 되어야 term 삽입이 가능함
        terms = 0;
        termArray = new Term[capacity]; // 포인터 변수 termarray에 new를 통해 배열 할당과 동시에 초기화
    };
    ~Polynomial(){
        delete [] termArray;
    };

    void sum(){ //해당 다항식 객체에 대해 같은 지수에 대하여 식을 정리하는 함수
        for(int i = 0; i<terms; i++){ // 기준 index
            for(int j = i+1; j<terms; j++) { // 비교 인덱스, i보다 한칸 뒤여야 함
                if(termArray[i].exponent == termArray[j].exponent){// 두 항의 지수가 같다면
                    float tmpCoef = termArray[i].coefficient + termArray[j].coefficient; // 계수를 합하고
                    termArray[i] = Term(tmpCoef,termArray[i].exponent); // 합한 계수 및 지수에 대한 term을 생성하여 기준 인덱스에 삽입

                    for(int k = j; k<terms;k++){ // 비교인덱스에 대해
                        termArray[k] = termArray[k+1]; //두 항을 합해주었으니 비교 인덱스에 있는 항을 제거하고, 그 뒤 항들을 앞으로 당겨온다.
                    }
                    terms--;// 항이 하나 줄었으니 총 항의 개수도 감소
                }
            }
        }
        for(int i = 0; i<terms; i++){
            if(termArray[i].coefficient == 0){// 항을 합친 이후 계수가 0인 항에 대해서는
                for(int k = i; k<terms;k++){
                    termArray[k] = termArray[k+1];//0인 항들은 지우고, 각 항들을 앞으로 당긴다.
                }
                terms--; //항 개수 감소
            }
        }
        for(int i = 0; i<terms; i++) { // 버블 소트를 활용하여 정리된 다항식을 지수의 오름차순으로 다시 정리한다.
            for (int j = i + 1; j < terms; j++) {
                if(termArray[i].exponent < termArray[j].exponent){
                    Term tmpTerm = termArray[i];
                    termArray[i] = termArray[j];
                    termArray[j] =tmpTerm;
                }
            }
        }
//        for(int i = 0; i<terms; i++){//모든 원소 출력
//            cout << "계:"<< termArray[i].coefficient << "지:" << termArray[i].exponent<< " ";
//        }
    };

    static Polynomial mul(const Polynomial& A, const Polynomial& B){ // 두 다항식을 곱하는 함수, static키워드로 해당 객체 없이도 호출 가능하게 선언 및 정의, 두 polynomial 객체의 값을 직접적으로 변경하는 것이 아니기에 const 키워드 선언
        Polynomial tempP;
        // 임시 polynomial 객체 생성
        if(A.terms !=0 and B.terms !=0){
            for(int i = 0; i<A.terms; i++){ // 기준 인덱스
                for(int j = 0; j<B.terms; j++){ // 비교 인덱스
                    float tmpCoef = A.termArray[i].coefficient * B.termArray[j].coefficient; // 계수는 곱하기
                    int tmpExp = A.termArray[i].exponent + B.termArray[j].exponent; // 지수는 더하기
                    tempP.newTerm(tmpCoef,tmpExp); // 해당 지수와 계수를 가지는 새로운 Term을 tempP의 term배열에 할당
                }
            }
        }
        else{// 다항식을 sum으로 정리한 식에 대해 아무런 항도 존재 하지 않으면 다항식 끼리의 곱샘은 0을 곱한 것으로 간주함
                tempP.newTerm(0,0);
                return tempP;
        }
        tempP.sum(); //식 정리 함수 호출
        return tempP;
    }

    int eval(const int& X){ //정상
        float sumOfPol = 0; //각 항들에 x를 대입한 값을 저장
        for(int i = 0; i<this->terms;i++){
            sumOfPol += this->termArray[i].coefficient * pow(X,this->termArray[i].exponent);//해당 객체의 term배열에 있는 모든 항의 지수에 대해 x에 지수만큼 제곱한 것을 곱하여 더함
        }
        return sumOfPol;
    }


    void newTerm(const float theCoeff, const int theExp) // 계수와 지수의 값 변동을 할 것이 아니기에 const 키워드 선언
    {
        if (terms == capacity) //capacity의 초기값이 1이니, 항의 갯수가 term배열의 크기와 같을때마다 배열의 크기를 늘려주어야 함
        {
            capacity *= 2; // 배열 크기 두배로 늘리기
            Term *temp = new Term[capacity]; //new array // 늘어난 capacity만큼의 크기를 가지는 새로운 term배열에 대한 주소를 temp에 할당
            copy(termArray, termArray + terms, temp); //termarray의 첫번째 원소 주소에서, 항이 저장되어 있는 공간까지를 temp에 복사
            delete[]termArray; //기존 term 배열 삭제
            termArray = temp; // 기존 배열에 복사한 배열 할당
        }
        termArray[terms].coefficient = theCoeff; //terms 단위는 1부터 시작하고, 배열은 0부터 시작하기 때문에 term 삽입이후 terms는 항상 삽입된 term 뒤의 위치를 가르키게 된다.
        termArray[terms++].exponent = theExp;
    };

    friend ostream &operator<<(ostream& os, Polynomial& poly) { // 출력 연산자 오버로딩
        for (int i = 0; i < poly.terms; i++) {//모든 항들에 대해
            if (poly.termArray[i].exponent != 1 && poly.termArray[i].exponent != 0) { // 지수가 1이 아닐 때,
                if (poly.termArray[i].coefficient > 0) { //계수가 양수인 경우
                    if (i == 0) os << poly.termArray[i].coefficient << "x^" << poly.termArray[i].exponent; // 첫 항
                    else {
                        os << "+" << poly.termArray[i].coefficient << "x^" << poly.termArray[i].exponent; // 첫 항이 아닐 떄
                    }
                }
                else if (poly.termArray[i].coefficient < 0) //계수가 음수인 경우
                    os << poly.termArray[i].coefficient << "x^" << poly.termArray[i].exponent;
            }
            else if (poly.termArray[i].exponent == 1) { // 지수가 1인 경우
                if (poly.termArray[i].coefficient > 0) { //계수가 양수
                    if (i == 0) os << poly.termArray[i].coefficient << "x"; // 첫 항, x^1은 x와 같음
                    else {
                        os << "+" << poly.termArray[i].coefficient<< "x"; //첫 항 아님
                    }
                }
                else if (poly.termArray[i].coefficient < 0) { //계수가 음수인 경우
                    os << poly.termArray[i].coefficient<< "x";
                }
            }
            else if (poly.termArray[i].exponent == 0){ // 지수가 0인 경우
                if (poly.termArray[i].coefficient > 0) { //계수가 양수인 경우
                    if (i == 0) os << poly.termArray[i].coefficient; // 첫 항 x^0 은 1이기에 계수부만 표시
                    else {
                        os << "+" << poly.termArray[i].coefficient; // 첫 항 아님
                    }
                }
                else if (poly.termArray[i].coefficient < 0) { //계수가 음수인 경우
                    os << poly.termArray[i].coefficient;
                }
                else if(poly.termArray[i].coefficient==0){ // 계수가 0인 경우(다항식 곱이 0이 되는 경우)
                    os << 0;
                }
            }

        }
        cout << endl;
        //cout << "항의 수:"<< poly.terms << endl;
        return os; //ostream 객체 리턴
    };

    friend istream &operator>>(istream& _is, Polynomial& poly){ // 입력 연산자 오버로딩, poly 객체이 값을 변경할 것이니 참조로 parameter 선언
        float tmpCoef =0;//임시 계수
        int tmpExp = 0;//임시 지수
        int count = 1; // 지수 혹은 계수부의 입력에 비정상적으로 값이 들어가는 것을 막고 순서대로 입력이 계수-순서대로 할당되도록 하기 위해 설정
        while(true){// 엔터키 입력까지 계속 반복, 입력 마무리 이후, 엔터키 한 번 더 입력해줘야 함
            if(count%2 == 1) {//홀수 번째 수 일 때 계수를 받도록 함
                _is >> tmpCoef;
                count++;

                if (tmpCoef == 0) { // 입력 받은 계수가 0일 때
                    if (cin.get() == '\n') break; // 다음 수가 없다면 종료
                    else {// 그 다음 수가 존재한다면
                        _is >> tmpExp;// 계수가 0, 항 성립 안됨 -> 입력 순서를 지키기 위해 입력만 받고 할당은 암함.
                        count++; // 입력 순서를 맞추어 다음번 루프에 계수륿 입력받도록 함
                        if(tmpExp==0) {
                            poly.newTerm(1,0);
                            continue;
                        }
                        if (cin.get() == '\n') break;// 지수 입력 이후 추가적인 입력이 없다면 종료
                        else continue;
                    }
                }
                else { //입력 받은 계수가 0이 아닐 떄
                    if (cin.get() == '\n') { //다음 수가 없다면
                        poly.newTerm(tmpCoef, 0);// 지수부 입력이 없기때문에 상수항으로 생성
                        break; //입력 종료
                    }
                    else {// 다음 수가 존재한다면
                        if (count % 2 == 0) {// 짝수 번째 수 일때 지수 입력받기
                            _is >> tmpExp;
                            count++;
                            if(tmpExp >=0)poly.newTerm(tmpCoef,tmpExp); // 지수가 음수인 경우를 제외하고는 새로운 항 추가

                            if (cin.get() == '\n') break; // 지수 입력 뒤에 추가로 숫자가 없다면 입력 종료
                            else continue;//추가로 숫자가 있다면 순환
                        }
                    }
                }
            }
        }
        poly.sum(); // 해당 식을 정리해주는 메서드 호출
        return _is;
    };

    Polynomial& operator=(const Polynomial &A){ // 할당 연산자 오버로딩
        this->termArray = A.termArray; // 피 연산 객체에 인자로 들어온 객체의 termarray, terms, capacity를 할당해 인자로 들어온 객체를 바인딩하도록 함.
        this->terms = A.terms;
        this->capacity = A.capacity;

        return *this;
    }

};


