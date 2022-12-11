#include <iostream>
using namespace std;

#define INF 100

int main() {
    int dp[4][4] = {{0, 5, INF, INF}, {INF, 0, 1, INF}, {8, INF, 0, 3}, {2, INF, INF, 0}};

    for(int k = 0; k < 4; k++) {
        cout<<"k = "<<k<<":"<<endl;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                cout<<dp[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    return 0;
}