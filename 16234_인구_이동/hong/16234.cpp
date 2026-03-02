#include <iostream>
#include <vector>
#include <deque>
#include <cmath>

using namespace std;

int N, L, R;
int arr[51][51];

vector<pair<int, int>> coor[51*51];
int visited[51][51];
int cnt;
int day;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void print(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void print2(){
    for(int i=0; i<cnt; i++){
        for(int j=0; j<coor[i].size(); j++){
            cout << "(" <<coor[i][j].first << "," << coor[i][j].second << ")" << " ";
        }
        cout << "\n";
    }
}

void init(){
    for(int i=0; i<N*N; i++){
        coor[i].clear();
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            visited[i][j] = 0; 
        }
    }
    cnt = 0;
}

void open(){
    for(int i=0; i<cnt; i++){
        int total = 0;
        int num = 0;
        for(int j=0; j<coor[i].size(); j++){
            num++;
            auto a = coor[i][j];
            total += arr[a.first][a.second];
        }
        for(int j=0; j<coor[i].size(); j++){
            auto a = coor[i][j];
            arr[a.first][a.second] = total/num;
        }
    }
    init();
}

void BFS(int y, int x){
    deque<pair<int, int>> q;
    q.push_back({y,x});
    coor[cnt].push_back({y,x});

    while(!q.empty()){
        auto c = q.back();
        q.pop_back();

        // cout << "now:" << c.first << " " << c.second << endl;
        for(int i=0; i<4; i++){
            int ny = c.first + dy[i];
            int nx = c.second + dx[i];

            if(ny >= N || ny < 0 || nx >= N || nx < 0) continue;
            if(visited[ny][nx] == 0){
                int diff = abs(arr[c.first][c.second] - arr[ny][nx]);
                // cout <<c.first << " " << c.second << "  " << ny  << " " << nx <<  " diff: " << diff << endl;
                if (diff <= R && diff >= L){
                    q.push_back({ny, nx});
                    coor[cnt].push_back({ny,nx});
                    visited[ny][nx] = 1;
                    
                }
            }
        }
    }

    cnt++;
}


int main(){
    cin >> N >> L >> R; 
    day = 0;

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> arr[i][j];
        }
    }
    init();

    while(1){
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(visited[i][j] == 0){
                    visited[i][j] = 1;
                    BFS(i,j);
                }
            }
        }
        // print();
        // print2();
        // cout << cnt << endl;
        if(cnt == N*N) break;

        day++;
        open();
        // print();
    }
    cout << day << "\n";

    return 0;
}


