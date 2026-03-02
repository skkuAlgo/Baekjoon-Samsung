#include <iostream>
#include <vector>

using namespace std;

int N;

int arr[101][101];

int reverseD[4] = {2, 3, 0, 1};

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

void print(){
    cout <<"\n";
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}


// 1x1 정사각형 확인
int checkAnswer(){
    // 101까지 확인하지 않는다. 정사각형이므로 반드시 x+1, y+1까지 1이어야함
    int answer = 0;
    for(int i=0; i<100; i++){
        for(int j=0; j<100; j++){
            if (arr[i][j] > 0){
                if(arr[i+1][j] > 0 && arr[i][j+1] > 0 && arr[i+1][j+1] > 0){
                    answer++;
                }
            }
        }
    }

    return answer;
}


// 1세대 이상부터 적용
void fill_arr(int g, int nowg, vector<int> d, int y, int x){
    if(g < nowg) return;

    vector<int> newGen;
    vector<int> nextD;

    for(int i=0; i< d.size(); i++){
        
        // -1
        int dir = d[i] - 1;
        if(dir == -1) dir = 3;

        // 표시
        int nextX = x + dx[dir];
        int nextY = y + dy[dir];
        if(nextX <= 100 && nextX >= 0 && nextY <= 100 && nextY >= 0){
            arr[nextY][nextX]++;
            y = nextY;
            x = nextX;
        }
        
        // Rev
        int nextdir = reverseD[dir];
        if(nextdir == -1) nextdir = 3;
        newGen.push_back(nextdir);
    }

    for(int i=newGen.size()-1; i>=0; i--){
        nextD.push_back(newGen[i]);
    }
    for(int i=0; i<d.size(); i++){
        nextD.push_back(d[i]);
    }

    fill_arr(g, nowg+1, nextD, y, x);
}

// 0세대
void zero_gen_fill_arr(int g, int nowg, int d, int y, int x){
    // 표시
    int nextX = x + dx[d];
    int nextY = y + dy[d];
    if(nextX <= 100 && nextX >= 0 && nextY <= 100 && nextY >= 0){
        arr[nextY][nextX]++;
        y = nextY;
        x = nextX;
    }
    
    // Rev
    int nextdir = reverseD[d];
    if(nextdir == -1) nextdir = 3;

    vector<int> nextD;
    nextD.push_back(nextdir);

    fill_arr(g, nowg+1, nextD, y, x);
}



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    
    int x, y, d, g;
    for(int i=0; i<N; i++){
        cin >> x >> y >> d >> g;
        arr[y][x]++;
        zero_gen_fill_arr(g, 0, d, y, x);
        // print();
    }

    int answer = checkAnswer();
    // print();
    cout << answer << "\n";
}
