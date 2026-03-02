#include <iostream>
#include <string.h>

using namespace std;

int N, M, x, y, K;
int map[21][21];
int order[1001];
int dice[6];

void printDice(){
    cout << endl;
    cout << "   "<< dice[3] << endl;
    cout <<  " " << dice[1] << " " << dice[0] << " " << dice[2] << endl; 
    cout << "   "  << dice[4] << endl;
    cout << "   " << dice[5] << endl;
    cout << endl;
}

void printMap(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void swap(int a, int b, int c, int d){
    
    int temp = dice[d];
    dice[d] = dice[c];
    dice[c] = dice[b];
    dice[b] = dice[a];
    dice[a] = temp;
}

// 0: 바닥, 1: 왼쪽, 2: 오른쪽, 3: 위, 4: 아래, 5: 천장
void down(){
    // 바닥 -> 위, 위-> 천장, 천장 -> 아래, 아래 -> 바닥
    swap(0, 3, 5, 4);
}

void up(){
    //  위 -> 바닥, 바닥 ->아래, 아래->천장, 천장-> 위
    swap(3, 0, 4, 5);
}

void right(){
    // 오른쪽 -> 바닥, 바닥 -> 왼쪽, 왼쪽 -> 천장, 천장 -> 오른쪽
    swap(2, 0, 1, 5);
}

void left(){
    // 왼쪽 -> 바닥, 바닥 -> 오른쪽, 오른쪽 -> 천장, 천장-> 왼쪽
    swap(1, 0, 2, 5);
}

void move(int dir){
    int newX = x;
    int newY = y;
    if(dir==1) newX+=1;
    if(dir==2) newX-=1;
    if(dir==3) newY-=1;
    if(dir==4) newY+=1;

    // 맵을 벗어나는 경우?
    if (newX >= M || newX < 0 || newY >= N || newY < 0) return;
    x = newX;
    y = newY;
    if(dir==1) right();
    if(dir==2) left();
    if(dir==3) up();
    if(dir==4) down();

    if(map[y][x]==0){
        map[y][x] = dice[0];
    }else{
        dice[0] = map[y][x];
        map[y][x] = 0;
    }

    cout << dice[5] << endl;
}

int main(){
    memset(dice, 0, sizeof(dice));

    cin >> N >> M >> y >> x >> K;

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> map[i][j];
        }
    }

    for(int i=0; i<K; i++){
        cin >> order[i];
    }

    // printDice();
    // printMap();
    
    for(int i=0; i<K; i++){
        // cout << "order: " << order[i] << endl;
        move(order[i]);
        // printDice();
        // printMap();
    }

    return 0;
}

// 4 2 0 0 8
// 0 2
// 3 4
// 5 6
// 7 8
// 4 4 4 1 3 3 3 2

// 남 남 남 동 북 북 북 서
// 0  0 3 0  0  8 6 3
