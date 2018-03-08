#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int maxn = 1e5+200;
const int maxm = 105;
int n,len,tot;
char s[maxn];
int a[maxn],sa[maxn],Rank[maxn],height[maxn];
int t[maxn],t2[maxn],c[maxn];
int solve[maxn],sz;

void build_sa(int n, int m) {
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

void get_Height(int n){
    int k = 0;
    for (int i=1; i<=n; i++) Rank[sa[i]] = i;
    for (int i=0; i<n; i++) {
        if (k) k--;
        int j = sa[Rank[i]-1];
        while (a[j+k]==a[i+k]) k++;
        height[Rank[i]] = k;
    }
}

int Length[maxm];
bool vis[maxm];
bool judge(int mid , int n) {
    int res = 0,cnt = 0;
    memset(vis,0,sizeof(vis));
    for (int i=1; i<=n; i++) {
        if (height[i]>=mid) {
            for (int j=1; j<=tot; j++) {
                if (sa[i]>Length[j-1] && sa[i]<Length[j]) cnt += (vis[j]?0:1), vis[j] = 1;
                if (sa[i-1]>Length[j-1] && sa[i-1]<Length[j]) cnt += (vis[j]?0:1), vis[j] = 1;
            }
        }
        else {
            if (cnt>tot/2) solve[res++] = sa[i-1];
            cnt = 0;
            memset(vis,0,sizeof(vis));
        }
    }
    if (cnt>tot/2) solve[res++] = sa[n];
    if (res)  { sz = res; return 1; }
    return 0;
}

int main(){
    int kase = 0;
    while (scanf("%d",&tot)==1 && tot) {
        int min_len = INF;
        n = 0;
        sz = 0;
        for (int i=1; i<=tot; i++) {
            scanf("%s",s);
            len = strlen(s);
            for (int j=0; j<len; j++) a[n++] = s[j];
            a[n++] = 'z'+i;
            min_len = min(min_len,len);
            Length[i] = n-1;
        }
        a[--n] = 0;
        build_sa(n+1,320);
        get_Height(n);

        int left = 1, right = min_len+1;
        int ans = -1, mid;
        while (left<=right) {
            mid = (left+right)>>1;
            if (judge(mid,n)) {
                ans = mid;
                left = mid+1;
            }
            else right = mid-1;
        }

        if (++kase>1) printf("\n");
        if (ans == -1) printf("?\n");
        else {
            for (int i=0; i<sz; i++) {
                int u = solve[i];
                for (int j=u; j<=u+ans-1; j++) printf("%c",a[j]);
                printf("\n");
            }
        }
    }
    return 0;
}
