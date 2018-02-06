#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 100+5;
int dp[maxn][maxn];
int n;
char s[maxn];
int ans;

inline int Max(int x, int y) { return x>y?x:y; }

int DP(int i, int j){
   if (dp[i][j]!=-1) return dp[i][j];
   if (j<=i) return dp[i][j] = 0;
   else if (i+1 == j) {
      if  ( (s[i]=='(' && s[j]==')') || (s[i]=='[' && s[j]==']') ) return dp[i][j]=2;
      return dp[i][j] = 0;
   }
   dp[i][j] = DP(i+1,j);
   for (int k=i+1; k<=j; k++)
     if ( (s[i]=='(' && s[k]==')') || (s[i]=='[' && s[k]==']') )
        dp[i][j] = Max(dp[i][j],DP(i+1,k-1)+DP(k+1,j)+2);
   return dp[i][j];
}

int main(){
    while (scanf("%s",s+1)) {
        if (s[1] == 'e') break;
        memset(dp,-1,sizeof(dp));
        n = strlen(s+1);
        printf("%d\n",DP(1,n));
    }
    return 0;
}
