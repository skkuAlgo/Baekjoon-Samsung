#include <iostream>
#include <string.h>

using namespace std;

int n, k, l, x, y;
char dir[101];
int sec[101];
int board[101][101];
int answer;
int headX, headY; 

int timeIndex;

int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};

void print(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void decrease(int X, int Y){
    // 전체 몸통 -1씩
    int len = board[Y][X];
    if(len == 0) return;

    int nextX, nextY;
    for(int i=0; i<4; i++){
        nextX = X+dx[i];
        nextY = Y+dy[i];

        if(nextX >= n || nextX < 0 || nextY >= n || nextY <0) continue;
        if(board[nextY][nextX] == len){
            board[nextY][nextX]--;
            decrease(nextX, nextY);
            break;
        }

    }
}

// dirX, dirY
// 오른쪽 1, 0 -> 왼쪽인 경우 위, 오른쪽인 경우 아래
// 왼쪽 -1, 0 -> 왼쪽인 경우 아래, 오른쪽인경우 위
// 아래쪽 0, 1 -> 왼쪽인 경우 오른쪽, 오른쪽인 경우 왼쪽
// 위쪽 0, -1 -> 왼쪽인 경우 왼쪽, 오른쪽인 경우 오른쪽

void move(int time, int dirX, int dirY){
    int len = board[headY][headX];
    // 방향대로 이동
    headX += dirX;
    headY += dirY;

    // 게임 아웃인가?
        // 1. 보드 바깥인가?
    if (headX == n || headY == n || headX == -1 || headY == -1) return;
        // 2. 몸통을 밟았는가?
    else if (board[headY][headX] > 0) return;
        // 3. 아닌 경우 최고점 갱신
    else{ 
        if(answer < time) answer = time;
    }

    // 사과가 있는가?
    if (board[headY][headX] == -1){
        board[headY][headX] = len+1;
    }else{
        board[headY][headX] = len;
        decrease(headX, headY);
    }

    // print();

    //회전이 필요한가?
    if(timeIndex < l && sec[timeIndex] == time){
        int index = timeIndex;
        timeIndex++;

        if(dir[index] == 'L'){ // 왼쪽인 경우
            if(dirY == -1) move(time+1, -1, 0);
            if(dirY == 1) move(time+1, 1, 0);
            if(dirX == 1) move(time+1, 0, -1);
            if(dirX == -1) move(time+1, 0, 1);
            return;
        }else{ // 오른쪽인 경우
            if(dirY == -1) move(time+1, 1, 0);
            if(dirY == 1) move(time+1, -1, 0);
            if(dirX == 1) move(time+1, 0, 1);
            if(dirX == -1) move(time+1, 0, -1);
            return;
        }
    }
    // 그대로 가는 경우
    move(time+1, dirX, dirY);
}

int main(){
    cin >> n; // 보드의 크기
    cin >> k; // 사과의 개수
    
    memset(board, 0, sizeof(board));

    for(int i=0; i<k; i++){
        cin >> y >> x;
        board[y-1][x-1] = -1;
    }

    cin >> l; // 방향 전환 횟수
    for(int i=0; i<l; i++){
        cin >> sec[i] >> dir[i];
    }

    answer = 0;
    timeIndex = 0;

    headX = 0;
    headY = 0;

    board[0][0] = 1;
    // print();
    move(1, 1, 0);

    // 게임이 끝나는 시간
    cout << answer+1 << endl;
    return 0;
}


// 1 X X 0 X X X 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
