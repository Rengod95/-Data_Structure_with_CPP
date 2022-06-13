#include "Rectangle.h" // Rectangle Class 선언에 대한 헤더파일을 가져와 메소드와 오퍼레이터에 대한 구체적인 정의를 할 것임
#include <iostream> // std::iostream 사용을 위헤 선언
//using namespace std;

int Rectangle::id = 0;  //Rectangle 객체가 몇 번 생성되었는지를 나타내기 위해 id에 0 할당

Rectangle::Rectangle(int x, int y, int w, int h) { //constructor가 x좌표, y좌표, 넓이, 높이 parameter를 받아 Rectangle 인스턴스 생성시 자동으로 할당
    xLow = x;
    yLow = y;
    width = w;
    height = h;

    std::cout << ++id << "번째 Rectangle 객체 생성\n\n"; //constructor 실행 시 자동으로 id에 1을 더하여 객체가 생성될 때 마다 몇번 째 객체 생성인지 알 게 함
}

Rectangle::~Rectangle() { // destructor에 소멸 표시를 함으로써 해당 좌표값을 가진 Rectangle 객체가 메모리 상에서 소멸된 것을 명시적으로 나타냄
    std::cout << "좌표 (" << xLow << ',' << yLow << ')'
              << " Rectangle 객체 소멸\n\n";
}

std::ostream& operator <<(std::ostream& os, Rectangle& r) { // cout이 필요한 오퍼레이터 << 에 대해 오버로딩을 시행하기에 os에 대한 참조를 parmeter로 설정, Rectangle 객체에 대한 레퍼런스를 parameter로 받아 해당 객체의 멤버변수에 접근
    os << "height : " << r.height << std::endl
       << "width : " << r.width << std::endl
       << "x : " << r.xLow << std::endl
       << "y : " << r.yLow << std::endl << std::endl;

    return os;
}

Rectangle Rectangle::operator +(Rectangle& r) { //operator +가 참조 객체에 대해 피연산되는 객체와 레퍼런스 객체의 멤버 변수 값을 더한 새로운 Rectangle 객체를 반환함. => constructor 실행으로 id값 +1;

    int sum_x, sum_y, sum_w, sum_h;

    sum_x = xLow + r.xLow;
    sum_y = yLow + r.yLow;
    sum_w = this->width + r.width;  //this를 통해 피연산되는 객체의 멤버변수에 접근
    sum_h = this->height + r.height;

    return Rectangle(sum_x, sum_y, sum_w, sum_h);
}