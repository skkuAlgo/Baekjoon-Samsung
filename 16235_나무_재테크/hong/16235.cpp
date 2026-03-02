#include <iostream>
#include <deque>

using namespace std;

int N, M, K;
int A[11][11];
int totalA[11][11];

deque<int> tree[11][11];

void spring_and_summer(int r, int c){
    if(tree[r][c].size() == 0) return;
    int dead = 0;
    
    // spring
    // 딱 있는 개수만큼만. deque에는 항상 내림차순으로 정렬되어있다고 가정
    // cout << "양분: " << totalA[r][c] << ", 개수: " << tree[r][c].size()<< "/";
    int size = tree[r][c].size();
    for(int i=0; i<size; i++){
        int b = tree[r][c].back();
        tree[r][c].pop_back();
        
        // cout << " " << b;

        if (totalA[r][c] >= b){
            totalA[r][c] -= b;
            tree[r][c].push_front(b+1);
        }else{
            // cout << "(dead)";
            dead += b/2;
        }
    }
    // cout << endl;
    // summer
    totalA[r][c] += dead;
}

int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

void autumn(int r, int c){
    if(tree[r][c].size() == 0) return;

    for(int i=0; i<tree[r][c].size(); i++){
        int b = tree[r][c][i]; // deque 이렇게 접근 가능? 
        // 5의 배수인가?
        if(b%5 == 0){
            for(int j=0; j<8; j++){
                int nr = dy[j]+r;
                int nc = dx[j]+c;
                if(nr<=N && nr>0 && nc<=N && nc>0) tree[nr][nc].push_back(1);
            }
        }
    }
}


int main(){
    cin >> N >> M >> K;

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> A[i][j];
        }
    }

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            totalA[i][j] = 5;
        }
    }

    for(int i=0; i<M; i++){
        int x, y, z;
        cin >> x >> y >> z;
        tree[x][y].push_back(z);
    }

    for(int t=1; t<=K; t++){
        // for(int i=1; i<=N; i++){
        //     for(int j=1; j<=N; j++){
        //         cout << totalA[i][j] << " ";
        //     }
        //     cout << "\n";
        // }
        // cout <<"\n";
        
        // int totalTree = 0;
        // for(int i=1; i<=N; i++){
        //     for(int j=1; j<=N; j++){
        //         cout << tree[i][j].size() << " ";
        //         totalTree += tree[i][j].size();
        //     }
        //     cout << "\n";
        // }
        // cout <<"\n";
        // cout << "totalTree: " <<totalTree << "\n";

        // // 봄 여름
        // cout << t << "년차: " << endl;
        for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++){
                spring_and_summer(i,j);
            }
        }

        // 가을
        for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++){
                autumn(i,j);
            }
        }
        // 겨울
        for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++){
                totalA[i][j] += A[i][j];
            }
        }
    }

    int totalTree = 0;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            // cout << tree[i][j].size() << " ";
            totalTree += tree[i][j].size();
        }
        // cout << "\n";
    }
    // cout <<"\n";
    cout << totalTree << "\n";
    return 0;
}
