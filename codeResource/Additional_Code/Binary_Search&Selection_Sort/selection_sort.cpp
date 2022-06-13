#include <iostream>
   
   
    int* selection_sort(const int n, int*a){ // n은 배열의 길이, 포인터a는 배열의 주소
        for (int i = 0; i<n; i++){ //기준 포인터는 i
            int j = i; //반환 받을 인덱스 만들어놓기
            for (int k = i+1; k<n; k++){ //움직일 포인터는 k
                if (a[k] < a[j]){ //움직이는 놈보다 기준놈이 크다면
                    j = k; // 반환 받을 인덱스에 작은 놈 인덱스를 할당
                }
            }
			int tmp = a[i];
			a[i]= a[j];
			a[j] = tmp;  // 다 돌고 젤 작은 값의 인덱스를 반환 받아 스왑 함수를 통해 해당 인덱스의 값 바꿔치기
        }
		for(int i = 0; i<n;i++)
		std::cout << a[i] <<std::endl;

		return a;
    }

using namespace ::std;

//int main(){
//    int array[] = {1,6,2,6,8,4,2,7};
//	selection_sort(sizeof(array)/sizeof(int), array);
//	return 0;
//}