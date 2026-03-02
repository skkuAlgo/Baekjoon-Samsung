#include <iostream>
#include <string.h>

using namespace std;

int N, M;
int paper[501][501];
int answer;


void updateAnswer(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    int sum = 0;
    sum = paper[y1][x1] + paper[y2][x2] + paper[y3][x3] + paper[y4][x4];
    if (sum > answer) answer = sum;
}

int isPossible(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    if(x1 < 0 || x1 >= M || y1 < 0 || y1 >= N) return 0;
    if(x2 < 0 || x2 >= M || y2 < 0 || y2 >= N) return 0;
    if(x3 < 0 || x3 >= M || y3 < 0 || y3 >= N) return 0;
    if(x4 < 0 || x4 >= M || y4 < 0 || y4 >= N) return 0;
    else return 1;
}


// ㅡ, ㅣ
void poly1(int y, int x){
    if (isPossible(x, y, x+1, y, x+2, y, x+3, y)) updateAnswer(x, y, x+1, y, x+2, y, x+3, y);
    if (isPossible(x, y, x, y+1, x, y+2, x, y+3)) updateAnswer(x, y, x, y+1, x, y+2, x, y+3);
}

// ㅁ
void poly2(int y, int x){
    if (isPossible(x, y, x+1, y+1, x, y+1, x+1, y)) updateAnswer(x, y, x+1, y+1, x, y+1, x+1, y);
}

// L, ㄴ, ㄱ, ...
void poly3(int y, int x){
    if (isPossible(x, y, x+1, y, x+2, y, x+2, y+1)) updateAnswer(x, y, x+1, y, x+2, y, x+2, y+1);
    if (isPossible(x, y, x, y+1, x+1, y+1, x+2, y+1)) updateAnswer(x, y, x, y+1, x+1, y+1, x+2, y+1);
    if (isPossible(x, y, x, y+1, x, y+2, x-1, y+2)) updateAnswer(x, y, x, y+1, x, y+2, x-1, y+2);
    if (isPossible(x, y, x, y+1, x, y+2, x+1, y+2)) updateAnswer(x, y, x, y+1, x, y+2, x+1, y+2);
    if (isPossible(x, y, x+1, y, x+2, y, x, y+1)) updateAnswer(x, y, x+1, y, x+2, y, x, y+1);
    if (isPossible(x, y, x, y+1, x-1, y+1, x-2, y+1)) updateAnswer(x, y, x, y+1, x-1, y+1, x-2, y+1);
    if (isPossible(x,y, x+1, y, x+1, y+1, x+1, y+2)) updateAnswer(x,y, x+1, y, x+1, y+1, x+1, y+2);
    if (isPossible(x,y, x+1, y, x, y+1, x, y+2)) updateAnswer(x,y, x+1, y, x, y+1, x, y+2);
}

// 
void poly4(int y, int x){
    if (isPossible(x,y, x+1, y, x, y+1, x-1, y+1)) updateAnswer(x,y, x+1, y, x, y+1, x-1, y+1);
    if (isPossible(x, y, x, y+1, x+1, y+1, x+1, y+2)) updateAnswer(x, y, x, y+1, x+1, y+1, x+1, y+2);
    if (isPossible(x, y, x+1, y, x+1, y+1, x+2, y+1)) updateAnswer(x, y, x+1, y, x+1, y+1, x+2, y+1);
    if (isPossible(x,y, x, y+1, x-1, y+1, x-1, y+2)) updateAnswer(x,y, x, y+1, x-1, y+1, x-1, y+2);
}

// ㅗ, ㅜ, ㅓ, ㅏ
void poly5(int y, int x){
    if (isPossible(x,y, x, y+1, x+1, y+1, x, y+2)) updateAnswer(x,y, x, y+1, x+1, y+1, x, y+2);
    if (isPossible(x, y, x, y+1, x, y+2, x-1, y+1)) updateAnswer(x, y, x, y+1, x, y+2, x-1, y+1);
    if (isPossible(x,y, x, y+1, x-1, y+1, x+1, y+1)) updateAnswer(x,y, x, y+1, x-1, y+1, x+1, y+1);
    if (isPossible(x, y, x+1, y, x+2, y, x+1, y+1)) updateAnswer(x, y, x+1, y, x+2, y, x+1, y+1);
}

int main(){
    cin >> N >> M;
    answer = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> paper[i][j];
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            poly1(i, j);
            poly2(i, j);
            poly3(i, j);
            poly4(i, j);
            poly5(i, j);
        }
    }

    cout << answer << endl;

    return 0;
}
