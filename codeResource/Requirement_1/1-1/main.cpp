

#include <iostream> //스탠다드 라이브러리 iostream 삽입
#include "Rectangle.h" // 클래스 Rectangle에 대한 정의가 담겨져 있는 헤더파일 삽입

int main()
{
    Rectangle r1(1, 1, 3, 4); // x:1 y:1 width:3 height:4 인 Rectangle 객체 생성
    std::cout << r1; // 오버로딩된 << 연산자로 r1객체 출력

    Rectangle* r2 = new Rectangle(2, 3, 5, 5); // Rectangle 객체에 대한 포인터 변수를 생성하면서 new를 통해 동적 할당과 동시에 constructor 호출
    std::cout << *r2; // 참조를 통한 출력

    r1 = r1 + *r2; // 오버로딩된 + 연산자를 이용해 두 객체를 더한 값을 r1에 할당

    std::cout << r1; // r1출력

    delete r2; // 동적할당된 메모리가 더이상 필요 없어졌으니 delete로 삭제
}