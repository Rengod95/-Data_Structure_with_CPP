#include "Rectangle.h" // Rectangle Class 선언에 대한 헤더파일을 가져와 메소드와 오퍼레이터에 대한 구체적인 정의를 할 것임
#include <iostream> // std::iostream 사용을 위헤 선언
//using namespace std;

int Rectangle::id = 0;  //Rectangle 객체가 몇 번 생성되었는지를 나타내기 위해 id에 0 할당

Rectangle::Rectangle() {
    xLow = 0;
    yLow = 0;
    width = 0;
    height = 0;
    std::cout << ++id << "번째 Rectangle 객체 생성\n\n";
}
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

std::ostream& operator <<(std::ostream& os, Rectangle& r) { // << operator 는 std::ostream의 객체를 필요로 하기 때문에 cout의 역할을 하는 ostream 객체 os에 대한 참조를 인자로 받고 Rectangle 객체에만 오버로딩이 실행되어야 하기 때문에 Rectangle 객체의 참조를 전달
    os << "height : " << r.height << std::endl
        << "width : " << r.width << std::endl
        << "x : " << r.xLow << std::endl
        << "y : " << r.yLow << std::endl << std::endl;

    return os;
}

std::istream& operator >>(std::istream& is, Rectangle& r){ // >> operator는 std::istream의 객체를 필요로 하기 때문에 cin의 역할을 하는 is 참조를 인자로 받고 Rectangle 객체에서만 오버로딩이 실행되어야 하기 때문에 Rectangle객체의 참조를 전달
    is >> r.xLow >> r.yLow >> r.width >> r.height;
    return is;
}

Rectangle Rectangle::generateIntersection(Rectangle &square1, Rectangle &square2) { // 두 사각형의 겹치는
    if (square1.xLow >= square2.xLow + square2.width) return Rectangle(0,0,0,0);
    else if (square2.xLow >= square1.xLow + square1.width) return Rectangle(0,0,0,0);
    else if (square1.yLow >= square2.yLow + square2.height) return Rectangle(0,0,0,0);
    else if (square2.yLow >= square1.yLow + square1.height) return Rectangle(0,0,0,0);

    int tmpX, tmpY, tmpWidth, tmpHeight;

    if(square1.xLow>square2.xLow){
        tmpX = square1.xLow;
    } else tmpX = square2.xLow;

    if(square1.yLow>square2.yLow){
        tmpY = square1.yLow;
    } else tmpY = square2.yLow;

    if (square1.yLow+square1.height > square2.yLow+square2.height){
        tmpHeight = square2.height+square2.yLow - tmpY;
    } else tmpHeight = square1.height+square1.yLow - tmpY;

    if (square1.xLow+square1.width > square2.yLow+square2.width){
        tmpWidth = square2.width+square2.xLow -tmpX;
    } else tmpWidth = square1.width+square1.xLow - tmpX;

    return Rectangle(tmpX,tmpY,tmpWidth,tmpHeight);
}
bool Rectangle::isIntersected(Rectangle& r){ // width 혹은 height가 없으면 사각형이 될 수 없음 즉 겹치는 부분이 존재하지 않는다는 것
    if(r.height == 0 or r.width == 0){
        return false;
    } else return true;
}

int Rectangle::areaShow(Rectangle& r3){
    return (r3.width * r3.height);
}


Rectangle Rectangle::operator+(Rectangle& r) { //operator +가 참조 객체에 대해 피연산되는 객체와 레퍼런스 객체의 멤버 변수 값을 더한 새로운 Rectangle 객체를 반환함. => constructor 실행으로 id값 +1;

    int sum_x, sum_y, sum_w, sum_h;

    sum_x = xLow + r.xLow;
    sum_y = yLow + r.yLow;
    sum_w = this->width + r.width;  //this를 통해 피연산되는 객체의 멤버변수에 접근
    sum_h = this->height + r.height;

    return Rectangle(sum_x, sum_y, sum_w, sum_h);
}
