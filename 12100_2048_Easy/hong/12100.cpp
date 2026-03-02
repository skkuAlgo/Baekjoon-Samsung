#include <iostream>

using namespace std;
int n;
int answer;

// Forward Declaration (전방선언)
void moveUp(int arr[21][21], int count);
void moveDown(int arr[21][21], int count);
void moveRight(int arr[21][21], int count);
void moveLeft(int arr[21][21], int count);


void print(int arr[21][21]){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << arr[i][j] << " "; 
        }
        cout << endl;
    }
    cout << endl;
}

void checkMax(int arr[21][21]){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if (arr[i][j] > answer) answer = arr[i][j];
        }
    }
}


void moveUp(int inputArr[21][21], int count){
    if (count == 5) {
        checkMax(inputArr);
        return;
    }

    int arr[21][21];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            arr[i][j] = inputArr[i][j];
        }
    }

    for(int i=0; i<n; i++){
        int temp[21] = {0,};
        
        // columns을 저장
        for(int j=0; j<n; j++){ 
            temp[j] = arr[j][i]; 
        }
    
        // 위부터 합치기
        int limit = 0;
        for(int j=1; j<n; j++){
            if(temp[j]==0) continue;
            for(int k=j-1; k>=limit; k--){
                if(temp[k] == 0) continue;

                if(temp[j]==temp[k]){
                    temp[k] *= 2;
                    temp[j] = 0;
                    limit = k+1;
                }else{
                    break;
                }
            }
        }

        // 합친 결과
        int newtemp[21] = {0,};
        int index = 0;
        for(int j=0; j<n; j++){
            if(temp[j] == 0) continue;
            newtemp[index++] = temp[j];
        }

        // arr에 덮어쓰기
        for(int j=0; j<n; j++){ 
            arr[j][i] = newtemp[j]; 
        }
    }

    moveUp(arr, count+1);
    moveDown(arr, count+1);
    moveLeft(arr, count+1);
    moveRight(arr, count+1);
}

void moveDown(int inputArr[21][21], int count){
    if (count == 5) {
        checkMax(inputArr);
        return;
    }

    int arr[21][21];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            arr[i][j] = inputArr[i][j];
        }
    }

    for(int i=0; i<n; i++){
        int temp[21] = {0,};
        
        // columns을 저장
        for(int j=n-1; j>=0; j--){ 
            temp[n-j-1] = arr[j][i]; 
        }
    
        // 합치기
        int limit = 0;
        for(int j=1; j<n; j++){
            if(temp[j]==0) continue;
        
            for(int k=j-1; k>=limit; k--){
                if(temp[k] == 0) continue;
                if(temp[j]==temp[k]){
                    temp[k] *= 2;
                    temp[j] = 0;
                    limit = k+1; // 이미 합친걸 또 합치지 않게 하는 용도
                }else{
                    break;
                }
            }
        }

        // 합친 결과
        int newtemp[21] = {0,};
        int index = 0;
        for(int j=0; j<n; j++){
            if(temp[j] == 0) continue;
            newtemp[index++] = temp[j];
        }

        // arr에 덮어쓰기
        for(int j=n-1; j>=0; j--){ 
            arr[j][i] = newtemp[n-j-1]; 
        }
    }

    moveUp(arr, count+1);
    moveDown(arr, count+1);
    moveLeft(arr, count+1);
    moveRight(arr, count+1);
    
}

void moveLeft(int inputArr[21][21], int count){
    if (count == 5) {
        checkMax(inputArr);
        return;
    }

    
    int arr[21][21];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            arr[i][j] = inputArr[i][j];
        }
    }

    for(int i=0; i<n; i++){
        int temp[21] = {0,};
        
        // columns을 저장
        for(int j=0; j<n; j++){ 
            temp[j] = arr[i][j]; 
        }
    
        // 합치기
        int limit = 0;
        for(int j=1; j<n; j++){
            if(temp[j]==0) continue;
            
            for(int k=j-1; k>=limit; k--){
                if(temp[k] == 0) continue;
                if(temp[j]==temp[k]){
                    temp[k] *= 2;
                    temp[j] = 0;
                    limit = k+1;
                }else{
                    break;
                }
            }
        }

        // 합친 결과
        int newtemp[21] = {0,};
        int index = 0;
        for(int j=0; j<n; j++){
            if(temp[j] == 0) continue;
            newtemp[index++] = temp[j];
        }

        // arr에 덮어쓰기
        for(int j=0; j<n; j++){ 
            arr[i][j] = newtemp[j]; 
        }
    }

    moveUp(arr, count+1);
    moveDown(arr, count+1);
    moveLeft(arr, count+1);
    moveRight(arr, count+1);
}

void moveRight(int inputArr[21][21], int count){
    if (count == 5) {
        checkMax(inputArr);
        return;
    }

    int arr[21][21];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            arr[i][j] = inputArr[i][j];
        }
    }

    for(int i=0; i<n; i++){
        int temp[21] = {0,};
        
        // columns을 저장
        for(int j=n-1; j>=0; j--){ 
            temp[n-j-1] = arr[i][j]; 
        }
    
        // 합치기
        int limit = 0;
        for(int j=1; j<n; j++){
            if(temp[j]==0) continue;
            
            for(int k=j-1; k>=limit; k--){
                if(temp[k] == 0) continue;
                if(temp[j]==temp[k]){
                    temp[k] *= 2;
                    temp[j] = 0;
                    limit = k+1;
                }else{
                    break;
                }
            }
        }

        // 합친 결과
        int newtemp[21] = {0,};
        int index = 0;
        for(int j=0; j<n; j++){
            if(temp[j] == 0) continue;
            newtemp[index++] = temp[j];
        }

        // arr에 덮어쓰기
        for(int j=n-1; j>=0; j--){ 
            arr[i][j] = newtemp[n-j-1]; 
        }
    }

    moveUp(arr, count+1);
    moveDown(arr, count+1);
    moveLeft(arr, count+1);
    moveRight(arr, count+1);
}

int main(){
    cin >> n;
    answer = 0;

    int arr[21][21];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
        cin >> arr[i][j];
        }
    }

    moveUp(arr, 0);
    moveDown(arr, 0);
    moveLeft(arr, 0);
    moveRight(arr, 0);

    cout << answer << endl;

    return 0;
}
