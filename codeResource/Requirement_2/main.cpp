#include <iostream>
#include "polynomial.h" //polynomial 객체 삽입

using namespace std; //std namespace를 사용하여 관련 메소드를 std:: 명시 없이 사용한다.

int main(){
    Polynomial A,B,C; // 다항식 객체 A B C 생성
    int x; // 다항식의 미지수에 대입할 값을 저장하는 변수

    cout << "A(x) 입력:";
    cin >> A;

    cin.get();

    cout << "B(x) 입력:";
    cin >> B;

    cout << "A(x)=" << A;
    cout << "B(x)=" << B;

    C = Polynomial::mul(A, B); // mul 연산을 통해 A와 B다항식을 곱한 다항식을 C에 바인딩
    cout << "A(x) * B(x) =" << C;
    cout << "대입 값 x 입력:";
    cin >> x;

    cout <<"A("<<x<<")="<<A.eval(x)<<endl<< "B(" << x << ")=" << B.eval(x) << " C(" << x << ")=" << C.eval(x) << endl;
    //출력 형식에 맞게 각 식에 x=? 를 대입한 값 출력
    return 0;
}