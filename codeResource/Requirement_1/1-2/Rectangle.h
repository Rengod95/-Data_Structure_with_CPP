#pragma once // 헤더 파일의 내용이 여러개 인 것을 방지하기 위해 컴파일 시 컴파일러에 한 번만 포함되도록 설정함
#include <iostream> // iostream 사용한다고 선언

class Rectangle  // Rectangle 객체에 대한 정의
{
private: // Rectangle 객체 외부에서 해당 변수에 직접적으로 접근할 수 없도록 private scope에 멤버 변수 선언
    static int id;
    int width;// 넓이
    int height;//높이
    int xLow, yLow; // x좌표, y좌표

public:// 외부에서 클레스 메소드를 통해 객체에 접근할 수 있도록 함
    Rectangle();
    Rectangle(int, int, int, int); // int인자 4개를 가지는 constructor 선언
    ~Rectangle(); // destructor 선언

    friend std::ostream& operator <<(std::ostream&, Rectangle&); //private 멤버나 protected 멤버를 외부 클래스에서 접근할 수 있도록 함
    friend std::istream& operator >>(std::istream&, Rectangle&);

    static Rectangle generateIntersection(Rectangle&, Rectangle&); // intersection을 생성하는 함수(r3)
    static bool isIntersected(Rectangle&); // 겹치는 지 판별해서 출력의 유무를 정함
    static int areaShow(Rectangle&);
Rectangle operator +(Rectangle&); //+ 오퍼레이터에 대한 해당 클래스의 오버로딩 선언
};




