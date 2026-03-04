#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<pair<int, int>> virus;
int arr[55][55];
int answer;

// 북 서 남 동
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, -1, 0, 1};

void print(int newarr[55][55]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << setw(2) << newarr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool isinrange(int y, int x){
    return 0<=y && y<N && 0<=x && x<N;
}

int time(int newarr[55][55]){
    int maxTime = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(newarr[i][j] == 0) return -1;
            if(newarr[i][j] > maxTime) maxTime = newarr[i][j];
        }
    }
    return maxTime-1;
}

void spread(vector<pair<int, int>> sv){
    int newarr[55][55];
    for(int i=0; i<N;i++){
        for(int j=0; j<N; j++){
            newarr[i][j] = arr[i][j];
        }
    }

    
    deque <tuple<int, int, int>> dq;
    bool v[55][55] = {false};

    for(int i=0; i<M; i++){
        int y = sv[i].first;
        int x = sv[i].second;
        dq.push_back({y,x,1});
        v[y][x] = true;
    }

    while(!dq.empty()){
        auto coor = dq.front();
        dq.pop_front();
        int y = get<0>(coor);
        int x = get<1>(coor);
        int dist = get<2>(coor);

        // 비활성은 -2로 고정
        if(newarr[y][x] != -2) newarr[y][x] = dist;
        
        for(int i=0; i<4; i++){
            int ny = y+dy[i];
            int nx = x+dx[i];
            if(!isinrange(ny,nx)) continue;
            if(v[ny][nx]) continue;
            v[ny][nx] = true;

            // 활성 바이러스가 비활성 바이러스가 있는 칸으로 가면 비활성 바이러스가 활성으로 변한다. => -2, 즉 바이러스가 있는 부분도 확장 대상에 고려해야한다.
            if(newarr[ny][nx] == -1) continue;

            dq.push_back({ny,nx, dist+1});
        }
    }

    int t = time(newarr);
    if(t>=0 && answer > t) answer = t;
    // print(newarr);
}


void select(int nextIndex, int count, vector<pair<int, int>> select_virus){
    // 인덱스가 끝에 도달한 경우   
    // cout << nextIndex << " " << virus.size() << " "<< M << "\n";
    
    // M개를 다 고른 경우
    if(count == M){
        // cout <<"?";
        spread(select_virus);
        return;
    }
    if(nextIndex == virus.size()) return;

    // 해당 바이러스 안넣는 경우
    select(nextIndex+1, count, select_virus);
    
    // 해당 바이러스 넣는 경우
    select_virus.push_back(virus[nextIndex]);
    select(nextIndex+1, count+1, select_virus);
}

int main(){
    answer = 987654321;
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> arr[i][j];
            if(arr[i][j] == 1) arr[i][j] = -1;
            if(arr[i][j] == 2){
                virus.push_back({i,j});
                arr[i][j] = -2;
            } 
        }
    }

    vector<pair<int, int>> sv;
    select(0, 0, sv);

    if(answer == 987654321) answer = -1;
    cout << answer << "\n";
    
    return 0;
}

// 3 2
// 1 1 1
// 1 2 2
// 1 1 1
