#include <bits/stdc++.h>

using namespace std;

int N;
int arr[25][25];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, -1, 0, 1};
int sharkSize = 2; // 상어 사이즈


void print(){
    for(int i =0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout <<endl;
}

bool isinrange(int y, int x){
    return 0<=y && y<N && 0<=x && x<N;
}

tuple<int, int, int> findFish(int r, int c){
    bool v[25][25] = {false};
    deque<tuple<int, int, int>> dq;

    dq.push_back({r,c,0});
    v[r][c] = true;

    int answerX = -1;
    int answerY = -1;
    int answerDist = 987654321;

    while(!dq.empty()){
        auto c = dq.front();
        dq.pop_front();

        int y = get<0>(c);
        int x = get<1>(c);
        int dist = get<2>(c);

        // 나보다 작거나 같은 물고기의 경우만 큐에 들어옴  ///// 여기 shark Size 조건 빼먹었다가 오래걸림!!!!!!!!!!!!!!!!!!!!!1
        if (arr[y][x] > 0 && arr[y][x] < sharkSize && dist!=0 && dist < answerDist){ // arr 조건 안넣었을때 왜 무한루프?
            answerDist = dist;
            answerX = x;
            answerY = y;
        }
        else if(arr[y][x] > 0 && arr[y][x] <sharkSize && dist!= 0 && dist == answerDist){
            if(answerY > y){
                answerDist = dist;
                answerY = y;
                answerX = x;
            }
            else if(answerY == y){
                if(answerX > x){
                    answerDist = dist;
                    answerY = y;
                    answerX = x;
                }
            }
        }
        // cout << answerY << " " << answerX << " "<< y << " " << x << endl;

        // 탐색
        for(int i=0; i<4; i++){
            int ny = y+dy[i];
            int nx = x+dx[i];

            if(!isinrange(ny,nx)) continue; // 범위체크
            if(v[ny][nx]) continue; // 방문체크
            v[ny][nx] = true;

            // 더 큰경우 못지나감
            if(arr[ny][nx] <= sharkSize) dq.push_back({ny,nx, dist+1});
        }
    }

    return {answerY, answerX, answerDist};
}

void move(int sr, int sc, int dr, int dc){
    arr[sr][sc] = 0;
    arr[dr][dc] = 9;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    int startR, startC;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> arr[i][j];
            if (arr[i][j] == 9){
                startR = i;
                startC = j;
            }
        }
    }

    int second = 0;
    int count = 0; // 상어가 먹은 수


    while(true){
        // 먹을 수 있는 물고기 위치 리턴
        auto coor = findFish(startR, startC);
        // cout << get<0>(coor) << " " << get<1>(coor) << " " << get<2>(coor) << endl;
        // 만약 -1 (없는 경우) => 도움 요청
        if (get<0>(coor) == -1){
            break;
        }
        else{
            // 해당 위치로 이동, 섭취
            move(startR, startC, get<0>(coor), get<1>(coor));
            startR = get<0>(coor);
            startC = get<1>(coor);
            second += get<2>(coor);
            count += 1;

            // cout << "nowSecond: " << second << endl; 
        }

        if(sharkSize == count){
            // cout << "shark up: " << sharkSize+1 << endl;
            sharkSize += 1;
            count = 0;
        }

        // print();

    }

    cout << second << "\n";
    
    return 0;
}
