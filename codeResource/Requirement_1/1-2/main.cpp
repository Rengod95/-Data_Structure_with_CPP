
#include <iostream>
#include "Rectangle.h"

int main()
{
    Rectangle r1,r2,r3; // Rectangle 객체 r1,r2,r3 생성

    std::cin>> r1;  // r1의 멤버 변수 입력받기
    std::cout << r1; // r1 멤버변수 출력

    std::cin>> r2;    // r2의 멤버 변수 입력받기
    std::cout << r2;  // r2 멤버변수 출력

    r3 = Rectangle::generateIntersection(r1,r2); // Rectangle 클래스의 generate 메소드를 통해 겹치는 사각형에 대한 객체 r3 생성

    if(Rectangle::isIntersected(r3)){ // r3가 가로, 세로가 존재한다면
        std::cout << r3; // r3 객체를 출력
        std::cout << "넓이:" <<Rectangle::areaShow(r3) << std::endl;
    }else std::cout << "겹치는 부분이 존재하지 않습니다." << std::endl; // 가로 혹은 세로가 존재하지 않는다면 겹쳐서 생기는 intersected 박스가 존재하지 않는다는 의미.


}
