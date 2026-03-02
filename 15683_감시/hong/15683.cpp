#include <iostream>
#include <vector>

using namespace std;

int N, M;
int A[9][9];
int minSpace = 1000;


void fill(vector<pair<int, int>> cctv);

void print(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout << A[i][j] << "   ";
        }
        cout << endl;
    }
    cout << endl;
}

void up(int y, int x){
    for(int i = y; i>=0; i--){
        if (A[i][x] == 6) break;
        else if (A[i][x] > 0) continue;
        else A[i][x]--; 
    }
}

void upback(int y, int x){
    for(int i = y; i>=0; i--){
        if (A[i][x] == 6) break;
        else if (A[i][x] > 0) continue;
        else A[i][x]++; 
    }
}

void down(int y, int x){
    for(int i = y; i<N; i++){
        if (A[i][x] == 6) break;
        else if (A[i][x] > 0) continue;
        else A[i][x]--; 
    }
}

void downback(int y, int x){
    for(int i = y; i<N; i++){
        if (A[i][x] == 6) break;
        else if (A[i][x] > 0) continue;
        else A[i][x]++; 
    }
}

void right(int y, int x){
    for(int i = x; i<M; i++){
        if (A[y][i] == 6) break;
        else if (A[y][i] > 0) continue;
        else A[y][i]--; 
    }
}

void rightback(int y, int x){
    for(int i = x; i<M; i++){
        if (A[y][i] == 6) break;
        else if (A[y][i] > 0) continue;
        else A[y][i]++; 
    }
}

void left(int y, int x){
    for(int i = x; i>=0; i--){
        if (A[y][i] == 6) break;
        else if (A[y][i] > 0) continue;
        else A[y][i]--; 
    }
}

void leftback(int y, int x){
    for(int i = x; i>=0; i--){
        if (A[y][i] == 6) break;
        else if (A[y][i] > 0) continue;
        else A[y][i]++; 
    }
}


void one(int y, int x, vector<pair<int, int>> cctv){
    up(y,x);
    fill(cctv);
    upback(y,x);


    down(y,x);
    fill(cctv);
    downback(y,x);

    right(y,x);
    fill(cctv);
    rightback(y,x);

    left(y,x);
    fill(cctv);
    leftback(y,x);
}   

void two(int y, int x, vector<pair<int, int>> cctv){
    up(y,x);
    down(y,x);
    fill(cctv);
    upback(y,x);
    downback(y,x);

    right(y,x);
    left(y,x);
    fill(cctv);
    rightback(y,x);
    leftback(y,x);
}   

void three(int y, int x, vector<pair<int, int>> cctv){
    up(y,x);
    right(y,x);
    fill(cctv);
    upback(y,x);
    rightback(y,x);

    right(y,x);
    down(y,x);
    fill(cctv);
    rightback(y,x);
    downback(y,x);

    left(y,x);
    down(y,x);
    fill(cctv);
    leftback(y,x);
    downback(y,x);

    left(y,x);
    up(y,x);
    fill(cctv);
    leftback(y,x);
    upback(y,x);
}   


void four(int y, int x, vector<pair<int, int>> cctv){
    left(y,x);
    up(y,x);
    right(y,x);
    fill(cctv);
    leftback(y,x);
    upback(y,x);
    rightback(y,x);

    up(y,x);
    right(y,x);
    down(y,x);
    fill(cctv);
    upback(y,x);
    rightback(y,x);
    downback(y,x);

    left(y,x);
    down(y,x);
    right(y,x);
    fill(cctv);
    rightback(y,x);
    leftback(y,x);
    downback(y,x);

    left(y,x);
    up(y,x);
    down(y,x);
    fill(cctv);
    downback(y,x);
    leftback(y,x);
    upback(y,x);
}   


void five(int y, int x, vector<pair<int, int>> cctv){
    up(y,x);
    right(y,x);
    down(y,x);
    left(y,x);
    fill(cctv);
    upback(y,x);
    rightback(y,x);
    downback(y,x);
    leftback(y,x);
}   


void check(){
    int sumSpace = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(A[i][j] == 0){
                sumSpace++;
            }
        } 
    }
    if(minSpace > sumSpace) {
        minSpace = sumSpace;
        // print();
    }
}

void fill(vector<pair<int, int>> cctv){
    if (cctv.empty()) {
        check();
        return;
    }
    pair<int, int> newCCTV = cctv.back();
    cctv.pop_back();
    int y = newCCTV.first;
    int x = newCCTV.second;

    int op = A[y][x];
    if(op == 1){
        one(y,x, cctv);
    }
    else if (op == 2){
        two(y,x, cctv);
    }
    else if (op == 3){
        three(y,x, cctv);
    }
    else if (op == 4){
        four(y,x, cctv);
    }
    else if (op == 5){
        five(y,x, cctv);
    }
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> A[i][j];
        }
    }

    vector<pair<int,int>> cctv;

    for(int i=0;i<N; i++){
        for(int j=0; j<M; j++){
            if(A[i][j] > 0 && A[i][j] < 6){
                cctv.push_back({i,j});
            }
        }
    }

    fill(cctv);
    cout << minSpace << "\n";
}
