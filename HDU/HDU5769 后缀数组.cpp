#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1e5+10;
char s[maxn];
int sa[maxn],Rank[maxn],height[maxn];
int t[maxn],t2[maxn],c[maxn];
int n;

void build_sa(int n, int m) {
   int *x = t, *y = t2;
   for (int i=0; i<m; i++) c[i] = 0;
   for (int i=0; i<n; i++) c[x[i] = s[i]]++;
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

void get_Height(int n) {
   int k = 0;
   for (int i=1; i<=n; i++) Rank[sa[i]] = i;
   for (int i=0; i<n; i++) {
      if (k) k--;
      int j = sa[Rank[i]-1];
      while (s[j+k]==s[i+k]) k++;
      height[Rank[i]] = k;
   }
}

int pos[maxn],tot;
long long solve(int n){
    long long sum = 0;
    int idx,len;
    for (int i=1; i<=n; i++) {
        idx = lower_bound(pos,pos+tot,sa[i])-pos;
        if (idx>=tot) idx = n; else idx = pos[idx];
        len = idx - sa[i];
        if (height[i]>=len) sum += n-idx - (height[i]-len);
        else sum += n-idx;
    }
    return sum;
}

int main(){
    int T;
    scanf("%d",&T);

    int kase = 0;
    char p[5];
    while (T--){
        scanf("%s%s",p,s);
        n = strlen(s);
        s[n] = 0;
        build_sa(n+1,270);
        get_Height(n);

        tot = 0;
        for (int i=0; i<n; i++) if (s[i]==p[0]) pos[tot++] = i;
        printf("Case #%d: %I64d\n",++kase,solve(n));
    }
    return 0;
}
