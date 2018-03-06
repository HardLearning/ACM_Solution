#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int maxm = 300;
const int maxn = 50000+10;
int n;
char s[maxn];
int sa[maxn];
int t[maxn],t2[maxn],c[maxm];
int Rank[maxn],height[maxn];

void build_sa(int n, int m){
    int i, *x = t, *y = t2;
    for (int i=0; i<m; i++) c[i] = 0;
    for (int i=0; i<n; i++) c[x[i] = s[i]]++;
    for (int i=1; i<m; i++) c[i] += c[i-1];
    for (int i=n-1; i>=0; i--) sa[--c[x[i]]] = i;

    for (int k=1; k<=n; k<<=1){
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

void getHeight(int n) {
   int i, k = 0;
   for (int i=1; i<=n; i++) Rank[sa[i]] = i;
   for (int i=0; i<n; i++) {
      if (k) k--;
      int j = sa[Rank[i]-1];
      while (s[i+k]==s[j+k]) k++;
      height[Rank[i]] = k;
   }
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%s",s);
        n = strlen(s);
        s[n] = 0;
        build_sa(n+1,200);
        getHeight(n);

        LL tot = LL(n)*LL(n+1)/2;
        LL sum = 0;
        for (int i=1; i<=n; i++) sum += LL(height[i]);
        printf("%I64d\n",tot-sum);
    }
    return 0;
}
