#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 4e5+10;
int a[maxn],sa[maxn],Rank[maxn],height[maxn];
int t[maxn],t2[maxn],c[maxn];
struct node{
   int val,idx;
   bool operator <(const node & rhs) const {
       return val<rhs.val || val == rhs.val && idx<rhs.idx;
   }
}d[maxn];
int n,cnt;

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

int main(){
    scanf("%d",&n);
    for (int i=n-1; i>=0; i--) {
        scanf("%d",&d[i].val);
        d[i].idx = i;
    }
    sort(d,d+n);
    for (int i=0; i<n; i++) {
        if (i && d[i].val == d[i-1].val) a[d[i].idx] = a[d[i-1].idx];
        else a[d[i].idx] = i+1;
    }
    a[n] = 0;
    build_sa(n+1,n+10);

    int i = 1;
    while (i<=n && sa[i]<=1) i++;
    int t = sa[i];
    for (int j=t; j<n; j++) printf("%d\n",d[a[j]-1].val);

    for (int j=0; j<t; j++) a[t+j] = a[j];
    t <<= 1;
    a[t] = 0;
    build_sa(t+1,n+10);

    i = 1; while (i<t && (!sa[i] || sa[i]>=t/2)) i++;
    int k = sa[i];
    for (int j=k; j<t/2; j++) printf("%d\n",d[a[j]-1].val);
    for (int j=0; j<k; j++) printf("%d\n",d[a[j]-1].val);

    return 0;
}
