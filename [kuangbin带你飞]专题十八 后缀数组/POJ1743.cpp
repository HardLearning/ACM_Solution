#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1<<25;
const int maxn = 20000+5;
int s[maxn],n;
int sa[maxn];
int t[maxn],t2[maxn],c[maxn];

void build_sa(int n, int m){
   int i, *x = t, *y = t2;

   for (int i=0; i<m; i++) c[i] = 0;
   for (int i=0; i<n; i++) c[x[i]=s[i]]++;
   for (int i=1; i<m; i++) c[i]+=c[i-1];
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
        x[sa[i]] = y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k] ? p-1:p++;
      if (p>=n) break;
      m = p;
   }
}

int rank[maxn],height[maxn];
void getHeight(){
    int i,k = 0;
    for ( i=1; i<=n; i++) rank[sa[i]] = i;
    for ( i=0; i<n; i++) {
        if (k) k--;
        int j = sa[rank[i]-1];
        while (s[i+k]==s[j+k]) k++;
        height[rank[i]] = k;
    }
}

inline int Max(int x, int y) {return x>y?x:y; }
inline int Min(int x, int y) {return x<y?x:y; }


bool judge(int k){
    int mx = -INF, mn = INF;
    for (int i=2; i<=n; i++) {
       if (height[i]>=k) {
           mx = Max(mx,Max(sa[i],sa[i-1]));
           mn = Min(mn,Min(sa[i],sa[i-1]));
           if (mx-mn>k) return 1;
       }
       else {
          mx = -INF; mn = INF;
       }
    }
    return 0;
}

int main(){
    while (scanf("%d",&n)==1 && n){
        for (int i=0; i<n; i++) scanf("%d",&s[i]);
        for (int i=0; i<n-1; i++) s[i] = s[i+1]-s[i]+88;
        s[--n] = 0;
        build_sa(n+1,176);
        getHeight();

        int left = 0, right = (n+1)/2;
        int mid;
        while (right>left){
              mid = (left+right+1)>>1;
              if (judge(mid)) left = mid;
              else right = mid-1;
        }
        if (left>=4) printf("%d\n",left+1); else printf("0\n");
    }
    return 0;
}
