#include <iostream>

using namespace std;

int N, L;
int arr[101][101];
int answer;

void printCol(int col){
    cout << "Col: " << col << endl;
    for(int i=0; i<N; i++){
        cout << arr[i][col] << " ";
    }
    cout << endl;
}
void printRow(int row){
    cout << "Row: " << row << endl;
    for(int i=0; i<N; i++){
        cout << arr[row][i] << " ";
    }
    cout << endl;
}

int is1step(int a, int b){
    if (a-b == 1) return 1;
    else return 0; 
}


void findInclinationRow(int row){
    int temp[101] = {0,};

    // 기울기 계산용
    for(int i=0; i<N-1; i++){
        if (arr[row][i] == arr[row][i+1]){
            // 그대로 0으로 둔다
        }
        else if (arr[row][i] < arr[row][i+1]){
            if (!(is1step(arr[row][i+1], arr[row][i]))) return;
            if (temp[i] == -1) return; // 안되는 길
            temp[i] = 1;
        }
        else if (arr[row][i] > arr[row][i+1]){
            if (!(is1step(arr[row][i], arr[row][i+1]))) return;
            temp[i+1] = -1;
        }
    }

    // 개수 확인용 (+1용)
    int num[101] = {0,};
    num[0] = 1;
    for(int i=1; i<N; i++){
        if (arr[row][i] == arr[row][i-1]){
            num[i] = num[i-1] + 1;
        }else{
            num[i] = 1;
        }
    }

    int copy[101] = {0,};
    for(int i=0; i<N; i++){
        copy[i] = arr[row][i];
    }

    for(int i=0; i<N; i++){
        if(temp[i] == 1){
            if(num[i] >= L){
                for(int j=i; j>i-L;j--){
                    copy[j] = -1;
                }
            }
            else return;
        }
    }

    // 개수 확인용 (-1용)
    int reverseNum[101] = {0,};
    reverseNum[N-1] = 1;
    for(int i=N-2; i>=0; i--){
        if (copy[i] == -1) continue;
        else if (copy[i] == copy[i+1]){
            reverseNum[i] = reverseNum[i+1] + 1;
        }else{
            reverseNum[i] = 1;
        }
    }

    for(int i=0; i<N; i++){
        if(temp[i] == -1){
            if(reverseNum[i] >= L) continue;
            else return;
        }
    }

    answer += 1;
    // printRow(row);
    return;
}

void findInclinationCol(int col){
    int temp[101] = {0,};

    for(int i=0; i<N-1; i++){
        if (arr[i][col] == arr[i+1][col]){
            // 그대로 0으로 둔다
        }
        else if (arr[i][col] < arr[i+1][col]){
            if (!(is1step(arr[i+1][col], arr[i][col]))) return;
            if (temp[i] == -1) return; // 안되는 길
            temp[i] = 1;
        }
        else if (arr[i][col] > arr[i+1][col]){
            if (!(is1step(arr[i][col], arr[i+1][col]))) return;
            temp[i+1] = -1;
        }
    }

    int num[101] = {0,};
    num[0] = 1;
    for(int i=1; i<N; i++){
        if (arr[i][col] == arr[i-1][col]){
            num[i] = num[i-1] + 1;
        }else{
            num[i] = 1;
        }
    }

    int copy[101] = {0,};
    for(int i=0; i<N; i++){
        copy[i] = arr[i][col];
    }

    for(int i=0; i<N; i++){
        if(temp[i] == 1){
            if(num[i] >= L){
                for(int j=i; j>i-L; j--){
                    copy[j] = -1;
                }
            }
            else return;
        }
    }

    int reverseNum[101] = {0,};
    reverseNum[N-1] = 1;
    for(int i=N-2; i>=0; i--){
        if (copy[i] == -1) continue;
        else if (copy[i] == copy[i+1]){
            reverseNum[i] = reverseNum[i+1] + 1;
        }else{
            reverseNum[i] = 1;
        }
    }

    for(int i=0; i<N; i++){
        if (temp[i] == -1){
            if(reverseNum[i] >= L) continue;
            else return;
        }
    }

    answer += 1;
    // printCol(col);
    return;
}


int main(){
    cin >> N >> L;
    answer = 0;

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> arr[i][j];
        }
    }

    for(int i=0; i<N; i++){
        findInclinationRow(i);
        findInclinationCol(i);
    }

    cout << answer << endl;

    return 0;
}
