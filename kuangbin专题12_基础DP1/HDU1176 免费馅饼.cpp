#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100000+5;
int n;
int dp[maxn][11];

inline int Max(int x, int y) {return x>y?x:y; }
int main(){
    while (scanf("%d",&n)==1 && n){
        memset(dp,0,sizeof(dp));
        int max_t = -1;

        int x,y;
        while (n--){
            scanf("%d %d",&x,&y);
            dp[y][x]++;
            max_t = Max(y,max_t);
        }

        for (int t=max_t-1; t>=0; t--){
            for (int pos=0; pos<=10; pos++) {
                if (pos == 0) dp[t][pos] += Max(dp[t+1][0],dp[t+1][1]);
                else if (pos == 10) dp[t][10] += Max(dp[t+1][10],dp[t+1][9]);
                else dp[t][pos] += Max(Max(dp[t+1][pos-1],dp[t+1][pos]),dp[t+1][pos+1]);
            }
        }
        printf("%d\n",dp[0][5]);
    }
    return 0;
}
