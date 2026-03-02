#include <iostream>

#define max(a,b) a>b? a:b

using namespace std;

int n;
int T[17];
int P[17];
int maxCost;

void dfs(int end, int cost){
    if(end>n) return;
    if (cost > maxCost) maxCost = cost;

    for(int i=end+1; i<=n; i++){
        int endDay = i+T[i]-1;
        dfs(endDay, cost+P[i]);
    }
}

int main(){
    maxCost = 0;
    
    cin >> n;

    for(int i=1; i<=n; i++){
        cin >> T[i] >> P[i];
    }

    for(int i=1; i<=n; i++){
        dfs(i+T[i]-1, P[i]);
    }

    cout << maxCost << endl;

}
