#include <iostream>

using namespace std;

int abs(int num){
    if (num < 0) return -num;
    else return num;
}


int N;
int S[21][21];
int answer;
int visited[21];
int pass[21];

void print(){
    for(int i=0; i<N; i++){
        if(visited[i] == 1){
            cout << i << " ";
        }
    }
    cout << endl;
}

void check(){
    int sum1 = 0;
    int sum2 = 0;

    for(int i=0; i<N; i++){
        if (visited[i] == 1){
            for(int j=0; j<N; j++){
                if (visited[j] == 1){
                    sum1 += S[i][j];
                }
            }
        }else{
            for(int j=0; j<N; j++){
                if(visited[j] == 0){
                    sum2 += S[i][j];
                }
            }
        }
    }
    
    int difference = abs(sum1 - sum2);
    if (difference < answer){
        // cout << "sum: " << sum1 << endl;
        // print();
        answer = difference;
    }
}

void teamsplit(int start, int num){
    if(num == N/2){
        check();
        return;
    }

    for(int i=start; i<N; i++){
        if(visited[i] == 0){
            visited[i] = 1;
            teamsplit(i+1, num+1);
            visited[i] = 0;
        }
    }
}

int main(){
    cin >> N;
    answer = 200000;

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> S[i][j];
        }
    }
    
    for(int i=0; i<N; i++){
        visited[i] = 0;
    }


    visited[0] = 1;
    teamsplit(1, 1);

    

    cout << answer << endl;

    return 0;
}
