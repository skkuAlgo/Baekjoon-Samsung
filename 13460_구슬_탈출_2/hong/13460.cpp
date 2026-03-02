#include <iostream>

using namespace std;

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

int n, m; // 세로 가로
int B_x, B_y;
int R_x, R_y;
int O_x, O_y;
int smallest;

void print(char arr[10][10]){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout << arr[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

void dfs(char arr[10][10], int B_x, int B_y, int R_x, int R_y, int count){
    if(count > 10) return;
    int nR_x, nR_y, nB_x, nB_y;

    for(int i=0; i<4; i++){
        char tempArr[10][10];
        for(int j=0; j<n; j++){
            for(int k=0; k<m; k++){
                tempArr[j][k] = arr[j][k];
            }
        }

        nR_x = R_x + dx[i];
        nR_y = R_y + dy[i];
        nB_x = B_x + dx[i];
        nB_y = B_y + dy[i];

        // 반드시 B가 먼저 움직여야 하는 경우?
        // 위쪽 이동, B가 더 작은 경우 || 왼쪽 이동, B가 더 작은경우 || 아래쪽 이동, B가 더 큰 경우 || 오른쪽 이동, B가 더 큰경우
        if ((i==0 && (B_y < R_y)) || (i==2 && (B_x < R_x)) || (i==1 && (B_y > R_y)) || (i==3 && (B_x > R_x))){

            while(tempArr[nB_y][nB_x] == '.'){
                nB_x += dx[i];
                nB_y += dy[i];
            }
            tempArr[B_y][B_x] = '.';
            tempArr[nB_y - dy[i]][nB_x - dx[i]] = 'B';

            while(tempArr[nR_y][nR_x] == '.'){
                nR_x += dx[i];
                nR_y += dy[i];
            }
            tempArr[R_y][R_x] = '.';
            tempArr[nR_y-dy[i]][nR_x-dx[i]] = 'R';
        } else {
            while(tempArr[nR_y][nR_x] == '.'){
                nR_x += dx[i];
                nR_y += dy[i];
            }
            tempArr[R_y][R_x] = '.';
            if(tempArr[nR_y][nR_x] != 'O') tempArr[nR_y-dy[i]][nR_x-dx[i]] = 'R';

            while(tempArr[nB_y][nB_x] == '.'){
                nB_x += dx[i];
                nB_y += dy[i];
            }
            tempArr[B_y][B_x] = '.';
            tempArr[nB_y - dy[i]][nB_x - dx[i]] = 'B';
        }
        
        if (tempArr[nB_y][nB_x] != 'O'){
            if(tempArr[nR_y][nR_x] == 'O'){
                if(smallest > count) smallest = count;
            }
            else if (nR_x != R_x || nR_y != R_y || nB_x != B_x || nB_y != B_y){
                dfs(tempArr, nB_x-dx[i], nB_y-dy[i], nR_x-dx[i], nR_y-dy[i], count + 1);
            }
        }
    }
}

int main(){
    cin >> n >> m;
    smallest = 10000000;
    char arr[10][10];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> arr[i][j];
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(arr[i][j] == 'B'){
                B_x = j;
                B_y = i;
            }
            else if(arr[i][j] == 'R'){
                R_x = j;
                R_y = i;
            }
        }
    }

    // print(arr);
    dfs(arr, B_x, B_y, R_x, R_y, 1);

    if (smallest == 10000000){
        cout << -1 << "\n";
    }
    else{
        cout << smallest << "\n";
    }
}
