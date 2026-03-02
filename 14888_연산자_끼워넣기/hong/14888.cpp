#include <iostream>

using namespace std;

int N;
int A[101];
int command[4];

long long minAnswer;
long long maxAnswer;

long long calculate(int oper, int num1, int num2){
    if (oper == 0) return num1 + num2;
    if (oper == 1) return num1 - num2;
    if (oper == 2) return num1 * num2;
    if (oper == 3) return num1 / num2;
    return 0;
}

void dfs(int index, long long result){
    if (index == N){
        if (result < minAnswer) minAnswer = result;
        if (result > maxAnswer) maxAnswer = result;
        return;
    }

    for(int i=0; i<4; i++){
        if(command[i] > 0){
            command[i]--;
            long long newResult = calculate(i, result, A[index]);
            dfs(index+1, newResult);
            command[i]++;
        }
    }
}

int main(){
    minAnswer = 1000000000;
    maxAnswer = -1000000000;
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> A[i];
    }

    for(int i=0; i<4; i++){
        cin >> command[i];
    }

    dfs(1, A[0]);

    cout << maxAnswer << endl;
    cout << minAnswer << endl;

    return 0;
}
