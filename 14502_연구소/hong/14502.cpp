#include <iostream>

using namespace std;

int N, M;
int answer;
int lab[9][9];
int thisLab[9][9];

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void checkSafe(){
    int count = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if (thisLab[i][j] == 0) count++;
        }
    }
    if (answer < count) answer = count;
}

void onlyTwo(int y, int x){
    // 동서남북 돌면서 0이면 2로 바꾸고 넣기
    for(int i=0; i<4; i++){
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (newX >= M || newX <0 || newY >= N || newY < 0) continue; // 범위 벗어나면 제외
        if (thisLab[newY][newX] == 0){ // 빈 공간이면
            thisLab[newY][newX] = 2;
            onlyTwo(newY, newX);
        }
    }
}

void spreadingVirus(){    
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            thisLab[i][j] = lab[i][j];
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(thisLab[i][j] == 2){
                onlyTwo(i, j);
            }
        }
    }
    
    checkSafe();
}

// 0인곳에 벽을 세울 수 있다.
void making3walls(int wallCount){
    if (wallCount == 3) {
        spreadingVirus();
        return;
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if (lab[i][j] == 0){
                lab[i][j] = 1;
                making3walls(wallCount+1);
                lab[i][j] = 0;
            }
        }
    }
}


int main(){
    cin >> N >> M;

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> lab[i][j];
        }
    }

    answer = 0;
    making3walls(0);
    cout << answer << endl;
    
    return 0;
}
