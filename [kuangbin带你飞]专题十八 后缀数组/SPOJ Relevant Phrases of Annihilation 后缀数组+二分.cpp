#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int maxn = 100000+1000;
char s[maxn];
int a[maxn],sa[maxn],Rank[maxn],height[maxn],idx[maxn];
int t[maxn],t2[maxn],c[maxn];
int tot,len,n;
int mx;

void build_sa(int n, int m){
   int *x = t, *y = t2;

   for (int i=0; i<m; i++) c[i] = 0;
   for (int i=0; i<n; i++) c[x[i] = a[i]]++;
   for (int i=1; i<m; i++) c[i] += c[i-1];
   for (int i=n-1; i>=0; i--) sa[--c[x[i]]] = i;

   for (int k=1; k<=n; k<<=1) {
       int p = 0;
       for (int i=n-k; i<n; i++) y[p++] = i;
       for (int i=0; i<n; i++) if (sa[i]>=k) y[p++] = sa[i]-k;

       for (int i=0; i<m; i++) c[i] = 0;
       for (int i=0; i<n; i++) c[x[y[i]]]++;
       for (int i=1; i<m; i++) c[i] += c[i-1];
       for (int i=n-1; i>=0; i--) sa[--c[x[y[i]]]] = y[i];

       swap(x,y);
       p = 1;
       x[sa[0]] = 0;
       for (int i=1; i<n; i++)
         x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k] ? p-1:p++;
       if (p>=n) break;
       m = p;
   }
}

void get_Height(int n){
   int k = 0;
   for (int i=1; i<=n; i++) Rank[sa[i]] = i;
   for (int i=0; i<n; i++) {
      if (k) k--;
      int j = sa[Rank[i]-1];
      while (a[i+k]==a[j+k]) k++;
      height[Rank[i]] = k;
   }
}

int dp[20][2];

bool judge(int mid, int n){
    int L,R;
    for (int i=1; i<=n; i++) {
        L = i;
        while (L<=n && height[L]<mid) L++;
        R = L;
        while (R<=n && height[R]>=mid) R++;
        for (int j=1; j<=tot; j++) dp[j][0] = INF, dp[j][1] = -INF;

        int tmp;
        for (int j=L-1; j<=R-1; j++) {
             tmp = idx[sa[j]];
             if (tmp>tot) continue;
             dp[tmp][0] = min(dp[tmp][0],sa[j]);
             dp[tmp][1] = max(dp[tmp][1],sa[j]);
        }

        int k = 0;
        for (k=1; k<=tot; k++) {
            if (dp[k][0]==INF) break;
            if (dp[k][1]-dp[k][0]<mid) break;
        }
        if (k>tot) return 1;
        i = R;
    }
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&tot);
        n = 0;
        mx = -INF;
        for (int i=1; i<=tot; i++) {
            scanf("%s",s);
            len = strlen(s);
            mx = max(len,mx);
            for (int k=0; k<len; k++) a[n] = s[k], idx[n++] = i;
            a[n] = 290+i; idx[n++] = tot+1;
        }
        n--; a[n] = 0;
        build_sa(n+1,310);
        get_Height(n);

        int left = 1, right = mx+1;
        int ans = 0, mid;
        while (left<=right) {
            mid = (left+right)>>1;
            if (judge(mid,n)) {
                ans = mid;
                left = mid+1;
            }
            else right = mid-1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
