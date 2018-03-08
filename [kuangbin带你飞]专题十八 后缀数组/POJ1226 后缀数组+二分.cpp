#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int maxn = 3e4+10;
int c[maxn],t[maxn],t2[maxn];
char s[200];
int a[maxn],Rank[maxn],height[maxn],sa[maxn],idx[maxn];
int n,len,tot;

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
        p = 1; x[sa[0]] = 0;
        for (int i=1; i<n; i++)
          x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k] ? p-1:p++;
        if (p>=n) break;
        m = p;
    }
}

void get_Height(int n) {
    int k = 0;
    for (int i=1; i<=n; i++) Rank[sa[i]] = i;
    for (int i=0; i<n; i++) {
        if (k) k--;
        int j = sa[Rank[i]-1];
        while (a[j+k]==a[i+k]) k++;
        height[Rank[i]] = k;
    }
}

const int maxm = 100+5;
bool vis[maxm];

bool judge(int mid, int n) {
    int L,R;
    for (int i=1; i<=n; i++) {
       L = i;
       while (L<=n && height[L]<mid) L++;
       R = L;
       while (R<=n && height[R]>=mid) R++;
       for (int j=1; j<=tot; j++) vis[j] = 0;

       int tmp;
       for (int j=L-1; j<=R-1; j++) {
          tmp = idx[sa[j]];
          if (tmp>tot) continue;
          vis[tmp] = 1;
       }

       int j;
       for (j=1; j<=tot; j++) if (!vis[j]) break;
       if (j>tot) return 1;
       i = R;
    }
    return 0;
}

int main(){
    int T;
    int x,min_len;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&tot);
        n = 0;
        x = 1; min_len = INF;
        for (int i=1; i<=tot; i++) {
            scanf("%s",s);
            len = strlen(s);
            for (int j=0; j<len; j++) a[n] = s[j], idx[n++] = i;
            a[n] = 'z'+x; idx[n++] = tot+2; x++;

            for (int j=len-1; j>=0; j--) a[n] = s[j], idx[n++] = i;
            a[n] = 'z'+x; idx[n++] = tot+2; x++;

            min_len = min(min_len,len);
        }
        a[--n] = 0;
        build_sa(n+1,400);
        get_Height(n);

        int left = 1, right = min_len+1;
        int ans = 0, mid;
        while (left <= right) {
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
