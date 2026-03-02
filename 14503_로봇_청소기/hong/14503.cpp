#include <iostream>
#include <string.h>

using namespace std;

int N, M;
int arr[51][51];

// 0: 남, 1: 서, 2: 북, 3: 동
int backdy[4] = {1, 0, -1, 0};
int backdx[4] = {0, -1, 0, 1};

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int answer;

void print(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void cleaning(int x, int y, int dir){

    // 1. 현재 칸이 아직 청소되지 않은 경우, 현재 칸을 청소한다.
    if(arr[y][x] == 0){
        arr[y][x] = 2;
        answer += 1;
        // print();
    }

    int cond = 0;
    for(int i=0; i<4; i++){
        int newX = x+dx[i];
        int newY = y+dy[i];

        if (newX >= M || newX < 0 || newY >= N || newY < 0) continue;
        if (arr[newY][newX] == 0) cond = 1;
    }

    // 2. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 없는 경우,
        // 바라보는 방향을 유지한 채로 한 칸 후진할 수 있다면 한 칸 후진하고 1번으로 돌아간다.
        // 바라보는 방향의 뒤쪽 칸이 벽이라 후진할 수 없다면 작동을 멈춘다.
    
    if (!cond){
        // 후진 가능?
        int newX = x+backdx[dir];
        int newY = y+backdy[dir];
        if(newX >= M || newX < 0 || newY >= N || newY < 0) return;
        if(arr[newY][newX] == 1) return;
        cleaning(newX, newY, dir);
    }
    
    // 3. 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 있는 경우,
        // 반시계 방향으로 90도 회전한다.
        // 바라보는 방향을 기준으로 앞쪽 칸이 청소되지 않은 빈 칸인 경우 한 칸 전진한다.
        // 1번으로 돌아간다.
    else{
        // 회전
        dir -= 1;
        if (dir == -1) dir = 3;

        // 앞쪽 칸
        int newX = x+dx[dir];
        int newY = y+dy[dir];

        if(arr[newY][newX] == 0){
            cleaning(newX, newY, dir);
        }else{
            cleaning(x, y, dir);
        }
    }
}

int main(){
    int r, c, d;

    cin >> N >> M;
    cin >> r >> c >> d;

    answer = 0;

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> arr[i][j];
        }
    }

    cleaning(c, r, d);

    cout << answer << endl;

    return 0;
}
