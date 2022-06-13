#include "iostream"
#include "cmath"

using namespace std;

class sparseMatrix;
class matrixTerm{
    friend class sparseMatrix;
private:
    int row;
    int column;
    int value;

    matrixTerm(){
        row=0;
        column =0;
        value=0;
    }
    matrixTerm(int row, int col, int value){
        this->row = row;
        this->column = col;
        this->value = value;
    }
    ~matrixTerm() = default;
};

class sparseMatrix{
    int totalRow, totalCol, totalTerms, capacity;
    matrixTerm* matrix;

    sparseMatrix(){ // 기본 생성자
        totalRow = 0;//행렬의 행의 갯수
        totalCol = 0; // 행렬의 열의 갯수
        totalTerms = 0; // value가 0이 아닌 원소의 갯수
        capacity=1;//
        matrix = new matrixTerm[capacity];//totalterms만큼 <r,c,v>인 matrixterm을 담을 배열, capacity == totalterms;
    }
    sparseMatrix(const int& rows,const int& columns){ // 입력받기 위한 새로운 sparseMatrix constructor
        this->totalRow = rows;
        this->totalCol = columns;
        this->totalTerms = 0;
        this->capacity = 1;
        this->matrix = new matrixTerm[capacity];
    };
    sparseMatrix(const int& rows,const int& columns, const int totalterm){// 전치를 위해 기존 sparseMatrix값을 참조하는 constructor
        this->totalRow = rows;
        this->totalCol = columns;
        this->totalTerms = totalterm;
        this->capacity = 1;
        this->matrix = new matrixTerm[capacity];
    };

    ~sparseMatrix(){
        delete[] matrix;
    }

    friend istream& operator >>(istream & _is, sparseMatrix& sMatrix){ // 행렬의 행,열, 원소 입력받기
        int totalRow, totalCol;

        cout << "행렬의 열의 수:";
        cin >> totalCol;
        cout << "행렬의 행의 수:";
        cin >> totalRow;

        if(!(totalCol > 0 and totalRow >0)) { // 행,열이 0이하면 행렬 성립 X
            cout << "잘못된 값입니다." << endl;
            return _is;
        }

        sparseMatrix tempSmatrix(totalRow,totalCol);

        for(int i=0; i<totalCol*totalRow;i++){
            int tempCol,tempRow,tempValue;
            cout << "행-열-값 의 순서대로 값을 삽입 해 주세요. 행 혹은 열에 음수 를 넣으면 삽입이 종료됩니다."<<endl;
            cout << "행 :";
            cin >> tempCol;
            if (tempCol >= 0 && tempCol<totalCol){//행,열은 음수 x
                cout << "열 :";
                cin >> tempRow;
                if(tempRow >= 0 && tempRow<totalRow){
                    cout << "값 :";
                    cin >> tempValue;
                    if(!tempValue) tempSmatrix.newMatrixTerm(tempRow,totalCol,tempValue);//값이 0 이 아닌 각 원소를 matrixTerm형태로 변환후 배열에 삽입
                }else break;
            }else break;
        }

        sMatrix = tempSmatrix;
        return _is;
    };

    void newMatrixTerm(const int row, const int column,const int value){
        bool isSame = false;
        if(this->totalTerms == this->capacity-1){
            int newCapacity = capacity*2;
            matrixTerm *tempMatrix = new matrixTerm[newCapacity];
            copy(this->matrix,this->matrix+this->totalTerms,tempMatrix);
            this->matrix = tempMatrix;
        }
        for(int i = 0; i<totalTerms; i++){
            if(matrix[i].column != column and matrix[i].row !=row and matrix[i].value){
                continue;
            }else isSame = true;
        }
        if(!isSame){
            matrix[totalTerms].column = column;
            matrix[totalTerms].row = row;
            matrix[totalTerms++].value = value;
        }

    };

    sparseMatrix transposeFaster(){
        sparseMatrix tmpSmatrix(this->totalRow, this->totalCol, this->totalTerms);//전치된 행렬 복사를 위한 sparseMatrix 생성

        if(totalTerms > 0){
            int *rowSize = new int[totalCol]; int *rowStart = new int[totalCol]; // column 기준으로 rowsize는 각 col에 있는 원소의 개수를 나타내고, rowstart는 이후 전치할 때 어떤 자리에 넣어야 하는지 index를 나타냄
            fill(rowSize,rowSize+totalCol,0);

            for(int i = 0; i<totalTerms; i++){//기존 Matrix의 모든 term에 접근
                rowSize[matrix[i].column]++; // matrix의 i번째 원소가 가지는 col == rowsize의 index가 됨, rowsize의 index == 해당 term의 col
            };

            rowStart[0] = 0; // rowStart의 index == term의 col => rowstart[0]=0 은 0번째 col의 첫 원소의 시작 지점이 배열의 0번
            for(int i = 1; i<totalCol; i++){ //1번col ~TotalCol에 대해 각 col의 첫 원소의 시작지점
                rowStart[i] = rowSize[i-1]+rowStart[i-1]; // 이전 col 원소 개수
            };

            for(int i =0; i<totalTerms; i++){
                int termPos = rowStart[matrix[i].column]; // matrix 의 term의 col이 전치 배열의 index가 됨
                tmpSmatrix.matrix[termPos].column = matrix[i].row;
                tmpSmatrix.matrix[termPos].row = matrix[i].column;
                tmpSmatrix.matrix[termPos].value = matrix[i].value;
                rowStart[matrix[i].column]++;// 기존 삽입 지점에 원소가 들어갔기 떄문에 삽입지점 한칸 뒤로 이동, rowStart[matrix[i].column] < rowstart[matrix[i].(column+1)
            }
            delete[] rowStart; delete[] rowSize;
        }
        return tmpSmatrix;
    }



};
