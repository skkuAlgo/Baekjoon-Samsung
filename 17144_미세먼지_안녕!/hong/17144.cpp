#include <bits/stdc++.h>

using namespace std;

int R, C, T;
int arr[55][55];
bool v[55][55];

// 북 동 남 서
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};


void print(){
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool isinrange(int y, int x){
    return 0<= y && y<R && 0<=x && x<C;
}

// 미세먼지 확산
void spread(){
    int temp[55][55] = {0};

    for(int y=0; y<R; y++){
        for(int x=0; x<C; x++){
            if (arr[y][x] > 0){
                int q = arr[y][x];

                for(int i=0; i<4; i++){
                    int ny = y+dy[i];
                    int nx = x+dx[i];
                    if(!isinrange(ny,nx)) continue; // 범위 벗어나면
                    if(arr[ny][nx] == -1) continue; // 공기청정기가 있으면 
                    temp[ny][nx] += q / 5;
                    arr[y][x] -= q / 5;
                }
            }
        }
    }

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            arr[i][j] += temp[i][j];
        }
    }
}


// 시작 지점, 현재 지점, 방향, 시계/반시계
void move(int sy, int sx, int y, int x, int dir, int clock){
    v[y][x] = true;
    // 다음 좌표 구하기
    int ny = y + dy[dir];
    int nx = x + dx[dir];

    // -1 만날 경우 -> 공기 청정기, 끝나는 조건
    if(ny == sy && nx == sx) return;

    // cout << y << " " << x << " " << ny << " " << nx << endl;
    // print();
    // 범위 벗어나는 경우, dir 변경
    if(!isinrange(ny, nx) || (clock == 1 && ny > sy) || (clock == -1 && ny < sy)){
        // cout << ny << " " << nx << endl;
        dir += clock;
        if(dir < 0) dir = 3;
        if(dir == 4) dir = 0;
        move(sy, sx, y, x, dir, clock);
    }else{
        arr[y][x] = arr[ny][nx];
        move(sy, sx, ny, nx, dir, clock);
    }

}


int main(){
    cin >> R >> C >> T;

    int y1, y2, x1, x2;

    for(int r=0; r<R; r++){
        for(int c=0; c<C; c++){
            cin >> arr[r][c];
            if(arr[r][c] == -1){
                y1 = r-1;
                x1 = c;
                y2 = r;
                x2 = c;
            }
        }
    }

    // T초 지난후 미세먼지 양
    for(int t=0; t<T; t++){
        spread();
        move(y1, x1, y1-1, x1, 0, 1);
        move(y2, x2, y2+1, x2, 2, -1);
        arr[y1][x1+1] = 0;
        arr[y2][x2+1] = 0;
    }
    

    // print();

    int count = 0;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(arr[i][j] > 0) count += arr[i][j];
        }
    }
    cout << count << "\n";

    return 0;
}
