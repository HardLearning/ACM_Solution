 #include <cstdio>
 #include <cstring>
 using namespace std;

 const int maxn = 1000+5;
 char s[maxn][maxn];
 int dp[maxn][maxn];
 int n;
 inline int Max(int x, int y) { return x>y?x:y; }

 int main(){
     while (scanf("%d",&n)==1 && n){
        for (int i=0; i<n; i++) scanf("%s",s[i]);
        int ans = 1;

        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (i ==0 || j == n-1) {
                     dp[i][j] = 1;
                     continue;
                }

                int tx = i, ty = j;
                while (tx>=0 && ty<n && s[tx][j] == s[i][ty]) {
                    tx--;
                    ty++;
                }

                int tmp = i-tx;
                if (tmp > dp[i-1][j+1]+1) dp[i][j] = dp[i-1][j+1]+1; else dp[i][j] = tmp;
                ans = Max(ans,dp[i][j]);
            }
        }
        printf("%d\n",ans);
     }
     return 0;
 }
