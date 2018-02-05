#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1000+5;
int dp[maxn][maxn];
int n,m;
char s1[maxn],s2[maxn];

inline int Max(int x, int y) { return x>y?x:y; }
int main(){
    while (scanf("%s %s",s1+1,s2+1)==2){
        n = strlen(s1+1);
        m = strlen(s2+1);
        for (int i=1; i<=n; i++) dp[i][0] = 0;
        for (int i=1; i<=m; i++) dp[0][i] = 0;
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=m; j++) {
                if (s1[i] == s2[j]) dp[i][j] = dp[i-1][j-1]+1;
                else dp[i][j] = Max(dp[i-1][j],dp[i][j-1]);
            }
        }
        printf("%d\n",dp[n][m]);
    }
    return 0;
}
