#include <iostream>

using namespace std;

int TC, N;

int cube[6][9];
int now[6];

// 0 -> w, 1 -> g, 2 -> r, 3 -> b, 4 -> y, 5 -> o
char mapping[6] = {'w', 'g', 'r', 'b', 'y', 'o'};

// 최종 정답 출력
void print(int index){
    for(int i=0;i<9;i++){
        if(i!=0 && i%3 == 0) cout << "\n";
        cout << mapping[cube[index][i]];
    }
    cout << "\n";
}

void print_b_d(int i){
    cout << mapping[cube[i][2]];
    cout << mapping[cube[i][1]];
    cout << mapping[cube[i][0]];
    cout << endl;

    cout << mapping[cube[i][5]];
    cout << mapping[cube[i][4]];
    cout << mapping[cube[i][3]];
    cout << endl;

    cout << mapping[cube[i][8]];
    cout << mapping[cube[i][7]];
    cout << mapping[cube[i][6]];
    cout << "\n\n";
}

void minus_rotate(int a){
    int temp = cube[a][0];
    cube[a][0] = cube[a][2];
    cube[a][2] = cube[a][8];
    cube[a][8] = cube[a][6];
    cube[a][6] = temp;
    
    temp = cube[a][3];
    cube[a][3] = cube[a][1];
    cube[a][1] = cube[a][5];
    cube[a][5] = cube[a][7];
    cube[a][7] = temp;
}

void plus_rotate(int a){
    int temp = cube[a][0];
    cube[a][0] = cube[a][6];
    cube[a][6] = cube[a][8];
    cube[a][8] = cube[a][2];
    cube[a][2] = temp;
    
    temp = cube[a][3];
    cube[a][3] = cube[a][7];
    cube[a][7] = cube[a][5];
    cube[a][5] = cube[a][1];
    cube[a][1] = temp;
}


// 0 1 2
void case1(int a, int b, int c, int d){
    int t1 = cube[a][0];
    int t2 = cube[a][1];
    int t3 = cube[a][2];

    cube[a][0] = cube[b][0];
    cube[a][1] = cube[b][1];
    cube[a][2] = cube[b][2];

    cube[b][0] = cube[c][0];
    cube[b][1] = cube[c][1];
    cube[b][2] = cube[c][2];

    cube[c][0] = cube[d][0];
    cube[c][1] = cube[d][1];
    cube[c][2] = cube[d][2];

    cube[d][0] = t1;
    cube[d][1] = t2;
    cube[d][2] = t3;
}

// 6 7 8
void case2(int a, int b, int c, int d){
    int t1 = cube[a][6];
    int t2 = cube[a][7];
    int t3 = cube[a][8];

    cube[a][6] = cube[b][6];
    cube[a][7] = cube[b][7];
    cube[a][8] = cube[b][8];

    cube[b][6] = cube[c][6];
    cube[b][7] = cube[c][7];
    cube[b][8] = cube[c][8];

    cube[c][6] = cube[d][6];
    cube[c][7] = cube[d][7];
    cube[c][8] = cube[d][8];

    cube[d][6] = t1;
    cube[d][7] = t2;
    cube[d][8] = t3;
}

// 2 5 8 -> 6 3 0
void case3(int a, int b, int c, int d){
    int t1 = cube[a][2];
    int t2 = cube[a][5];
    int t3 = cube[a][8];

    cube[a][2] = cube[b][2];
    cube[a][5] = cube[b][5];
    cube[a][8] = cube[b][8];

    cube[b][2] = cube[c][6];
    cube[b][5] = cube[c][3];
    cube[b][8] = cube[c][0];

    cube[c][6] = cube[d][6];
    cube[c][3] = cube[d][3];
    cube[c][0] = cube[d][0];

    cube[d][6] = t1;
    cube[d][3] = t2;
    cube[d][0] = t3;
}

// 큐브 위치 바꾸기
void cubeRotate(string cmd){
    string alpha = cmd.substr(0,1);
    string sign = cmd.substr(1,1);

    if (alpha == "F"){
        plus_rotate(1);
        minus_rotate(3);
        if (sign == "+") {
            case2(1,4,3,0);
            plus_rotate(2);
        }
        else {
            case2(0, 3, 4, 1);
            minus_rotate(2);
        }
        minus_rotate(1);
        plus_rotate(3);
    }
    else if (alpha == "B"){
        plus_rotate(1);
        minus_rotate(3);
        if(sign == "-"){
            case1(0,1,4,3);
            minus_rotate(5);
        }
        else{ 
            case1(0,3,4,1);
            plus_rotate(5);
        }
        minus_rotate(1);
        plus_rotate(3);
    }
    else if (alpha == "L"){
        if (sign == "+"){
            case3(5,4,2,0);
            plus_rotate(1);
        }
        else{
            case3(4, 5, 0, 2);
            minus_rotate(1);
        }
    }
    else if (alpha == "R"){
        if(sign == "-"){
            case3(2,0,5,4);
            minus_rotate(3);
        }
        else{
            case3(0,2, 4, 5);
            plus_rotate(3);
        }
    }
    else if (alpha == "U"){
        if(sign == "-"){
            case1(5,3,2,1);
            minus_rotate(0);
        }
        else{
            case1(1, 2, 3, 5);
            plus_rotate(0);
        }
    }
    else if (alpha == "D"){
        if(sign == "+"){
            case2(1, 5, 3, 2);
            plus_rotate(4);
        }
        else{
            case2(2, 3, 5, 1);
            minus_rotate(4);
        }
    }
}


void initcube(){
    for(int i=0; i<6; i++){
        for(int j=0; j<9; j++){
            cube[i][j] = i;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> TC;

    for(int t=0; t<TC; t++){
        cin >> N;
        string cmd;
        // 큐브 초기화
        initcube();
        
        for(int i=0; i<N; i++){
            cin >> cmd;
            cubeRotate(cmd);
        }
        print(0);
    }


    // print(0);
    // print(1);
    // print(2);
    // print(3);
    // print_b_d(4);
    // print_b_d(5);
}
