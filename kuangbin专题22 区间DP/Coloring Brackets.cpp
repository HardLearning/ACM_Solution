#include <cstdio>
#include <stack>
#include <cstring>
using namespace std;

typedef long long LL;
const LL mod = 1e9+7;
const int maxn = 700+5;
int n;
char s[maxn];
LL dp[maxn][maxn][3][3];
int a[maxn];

void init(){
    n = strlen(s+1);

    int cnt = 0,p;
    stack<int>st;
    while (!st.empty()) st.pop();
    for (int i=1; i<=n; i++) {
        if (s[i]=='(') st.push(i);
        else {
           p = st.top();
           st.pop();
           a[p] = a[i] = ++cnt;
        }
    }
}

LL DP(int l, int r, int p, int q){
    if (dp[l][r][p][q]!=-1) return dp[l][r][p][q];
    if (l+1 == r) {
        if ((p==0 && q==0) || (p!=0 && q!=0)) return dp[l][r][p][q] = 0;
        return dp[l][r][p][q] = 1;
    }

    dp[l][r][p][q] = 0;
    if (a[l] == a[r]) {
        if ((p==0 && q==0) || (p!=0 && q!=0)) return 0;
        for (int i=0; i<=2; i++)
          for (int j=0; j<=2; j++) {
             if ((p==i && p) || (q==j && q) ) continue;
             dp[l][r][p][q] += DP(l+1,r-1,i,j);
             dp[l][r][p][q] %= mod;
        }
    }
    else {
        int k = l+1;
        while (a[l]!=a[k] && k<r) k++;

        for (int i=0; i<=2; i++)
          for (int j=0; j<=2; j++) {
             if (i!=j || (i==0 && j==0))
                dp[l][r][p][q] = (dp[l][r][p][q] + (DP(l,k,p,i)*DP(k+1,r,j,q))%mod)%mod;
        }

    }
    return dp[l][r][p][q]%mod;
}

int main(){
        scanf("%s",s+1);
        init();
        memset(dp,-1,sizeof(dp));

        LL ans = 0;
        for (int i=0; i<=2; i++) {
            for (int j=0; j<=2; j++)
                ans += DP(1,n,i,j);
                ans %= mod;
        }
        printf("%I64d\n",ans);
    return 0;
}
