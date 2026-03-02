#include <iostream>

using namespace std;
int N, M, H;
int answer;

void print(int arr[31][11]){
    for(int i=1; i<=H; i++){
        for(int j=1; j<=N; j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n"; 
    }
    cout << "\n";
}

int i_is_i(int arr[31][11], int nowH, int nowN){
    if(nowN > N){ return -1; }
    if(nowH == H+1){ 
        // cout << "return: " << nowN << endl;
        return nowN; 
    }else{
        int nextN = arr[nowH][nowN];
        // cout << "nextN: " << nextN << " nowN: " << nowN << endl;
        // 0인 경우, 그대로 다음줄로 감
        if (nextN == 0){ return i_is_i(arr, nowH+1, nowN); }
        // 0이 아닌경우, 다른 줄로 이동
        else{ return i_is_i(arr, nowH+1, nextN); }
    }
}

void check(int arr[31][11], int num){
    if (num > answer) return;
    if (num > 3) return;

    // print(arr);

    for(int i=1; i<=N; i++){
        int result = i_is_i(arr, 1, i);
        if (result != i){ return; }
    }

    if (answer > num){ answer = num; }
}

void setLine(int arr[31][11], int nowH, int num){
    // 끝줄인 경우 체크만 함
    if (nowH == H+1 || num == 3){
        check(arr, num);
    }
    else{
        // 현재 가로줄에서, 줄을 설치
        for(int i=1; i<N; i++){
            if(arr[nowH][i] == 0 && arr[nowH][i+1] == 0){            
                int newArr[31][11];
                for(int i=0; i<31; i++){
                    for(int j=0; j<11; j++){
                        newArr[i][j] = arr[i][j];
                    }
                }
                // arr에 설정
                newArr[nowH][i] = i+1;
                newArr[nowH][i+1] = i;
                check(newArr, num+1);
                setLine(newArr, nowH, num+1);
            }
        }
        // 무조건 다음줄 넘어가기. (아무것도 안그리고 넘어가기 포함)
        check(arr, num);
        setLine(arr, nowH+1, num);
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    answer = 987654321;

    cin >> N >> M >> H;
    
    int arr[31][11];
    for(int i=0; i<31; i++){
        for(int j=0; j<11; j++){
            arr[i][j] = 0;
        }
    }

    int a, b;
    for(int i=0; i<M; i++){
        cin >> a >> b;
        arr[a][b] = b+1;
        arr[a][b+1] = b;
    }

    setLine(arr, 1, 0);

    if (answer == 987654321) answer = -1;
    cout << answer << "\n";

    return 0;
}
