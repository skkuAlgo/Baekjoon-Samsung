#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N, M;
int arr[52][52];
vector<pair<int, int>> Homelst;
vector<pair<int, int>> Chickenlst;
int answer;

int calDis(int r1, int c1, int r2, int c2){
    int a =  abs(r1-r2) + abs(c1-c2);
    return a;
}

void check(vector<pair<int, int>> tlst){
    // 거리 배열 초기화
    vector<int> HomeDst(Homelst.size(), 1000);

    // 거리 길이 업데이트
    while(!tlst.empty()){
        auto v = tlst.back();
        int r1 = v.first;
        int c1 = v.second;
        tlst.pop_back();
        for(int i=0; i<Homelst.size(); i++){
            int r2 = Homelst[i].first;
            int c2 = Homelst[i].second;
            if (HomeDst[i] > calDis(r1,c1,r2,c2)){
                HomeDst[i] = calDis(r1,c1,r2,c2);
            }
        }
    }

    // 전체 길이 합
    int totalDst = 0;
    for(int i=0; i<Homelst.size(); i++){
        // cout << HomeDst[i] << " ";
        totalDst += HomeDst[i];
    }

    if(answer > totalDst) answer = totalDst;
}

void dfs(int n, int s, int cnt, vector<pair<int, int>> tlst){
    // 가지치기
    if(cnt > M) return;
 
    // cout << n << " " <<  Chickenlst.size() << endl;

    if(n == Chickenlst.size()){
        check(tlst);
        return;
    }

    for(int i=s; i<Chickenlst.size(); i++){
        // 포함
        vector<pair<int, int>> ttlst(tlst);
        ttlst.push_back(Chickenlst[i]);

        // for(int i=0; i<ttlst.size(); i++){
        //     cout << ttlst[i].first << " " << ttlst[i].second << endl;
        // }

        dfs(n+1, i+1, cnt+1, ttlst);

        // 포함 X
        dfs(n+1, i+1, cnt, tlst);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    answer = 987654321;

    cin >> N >> M;

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> arr[i][j]; 
        }
    }

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            int t = arr[i][j];
            if(t == 1){
                Homelst.push_back({i,j});
            }else if (t==2){
                Chickenlst.push_back({i,j});
            }
        }
    }

    vector<pair<int, int>> tlst;
    dfs(0, 0, 0, tlst);
    cout << answer << "\n";
} 
