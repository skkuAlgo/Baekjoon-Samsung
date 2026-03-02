#include <iostream>

using namespace std;

int A[1000001];

int main(){
    int N, B, C;
    cin >> N; // 전체 시험관 수
    for(int i=0; i<N; i++){
        cin >> A[i]; // 시험관 하나에 있는 사람 수
    }
    cin >> B >> C; // 총감독관, 부감독관

    long long count = 0;

    for(int i=0; i<N; i++){
        int people = A[i];
        people -= B;
        count++;
        if(people > 0) {
            count += (people / C);
            people = (people % C);
        }
        if (people > 0) count += 1;
    }
    cout << count << endl;

    return 0;
}
