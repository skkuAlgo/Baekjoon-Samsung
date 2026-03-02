#include <iostream>

using namespace std;

int K;
char one[9];
char two[9];
char three[9];
char four[9];

int kind[101];
int dir[101];
int arr[4][8];

void print(){
    for(int i=0; i<4; i++){
        for(int j=0; j<8; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void left(int i){
    int temp[8];
    int index = 0;

    temp[7] = arr[i][0];

    for(int j=0; j<7; j++){
        temp[j] = arr[i][j+1];
    }

    for(int j=0; j<8; j++){
        arr[i][j] = temp[j];
    }
}

void right(int i){
    int temp[8];
    int index = 0;

    temp[0] = arr[i][7];

    for(int j=1; j<8; j++){
        temp[j] = arr[i][j-1];
    }

    for(int j=0; j<8; j++){
        arr[i][j] = temp[j];
    }
}

// 오른쪽을 확인
void rotate1(int isStart, int k, int d){
    // 닿아있는 부분 확인
    if (k==1){
        if (arr[0][2] != arr[1][6]) rotate1(0, 2, -d);
    }
    else if (k==2){
        if (arr[1][2] != arr[2][6]) rotate1(0, 3, -d);
    }
    else if (k==3){
        if (arr[2][2] != arr[3][6]) rotate1(0, 4, -d);
    }
    
    // 회전
    if (isStart) return;
    if(d==1) right(k-1);
    if (d==-1) left(k-1);
}

// 왼쪽 확인
void rotate2(int isStart, int k, int d){
    if(k==2){
        if(arr[1][6] != arr[0][2]) rotate2(0, 1, -d);
    }
    else if (k==3){
        if (arr[2][6] != arr[1][2]) rotate2(0, 2, -d);
    }
    else if (k==4){
        if (arr[3][6] != arr[2][2]) rotate2(0, 3, -d);
    }

    if (isStart) return;
    if (d==1) right(k-1);
    if (d==-1) left(k-1);
}


int main(){
    cin >> one;
    cin >> two;
    cin >> three;
    cin >> four;
    cin >> K;

    for(int i=0; i<K; i++){
        cin >> kind[i] >> dir[i];
    }

    for(int i=0; i<8; i++){
        if (one[i] == '0') arr[0][i] = 0;
        else arr[0][i] = 1;

        if (two[i] == '0') arr[1][i] = 0;
        else arr[1][i] = 1;
        
        if (three[i] == '0') arr[2][i] = 0;
        else arr[2][i] = 1;

        if (four[i] == '0') arr[3][i] = 0;
        else arr[3][i] = 1;
    }

    // print();
    for(int i=0; i<K; i++){
        rotate1(1, kind[i], dir[i]);
        rotate2(1, kind[i], dir[i]);
        if (dir[i]==1) right(kind[i]-1);
        if (dir[i]==-1) left(kind[i]-1);
        // print();
    }


    // score
    int score = arr[0][0] + arr[1][0] * 2 + arr[2][0] * 4 + arr[3][0] * 8;
    cout << score << endl;

    return 0;
}
