#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 100000+5;
int a[maxn*2];
char s1[maxn*2],s2[maxn*2];
int n,len;
int c[maxn*2],t[maxn*2],t2[maxn*2];
int height[maxn*2],Rank[maxn*2],sa[maxn*2];

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

void get_Height(int n){
   int i, k = 0;
   for (i=1; i<=n; i++) Rank[sa[i]] = i;
   for (i=0; i<n; i++) {
      if (k) k--;
      int j = sa[Rank[i]-1];
      while (a[i+k]==a[j+k]) k++;
      height[Rank[i]] = k;
   }
}

int main(){
    while (scanf("%s",s1)>0){
       scanf("%s",s2);
       n = 0;
       len = strlen(s1);
       for (int i=0; i<len; i++) a[n++] = s1[i]-'a'+1;
       a[n++] = 28;
       len = strlen(s2);
       for (int i=0; i<len; i++) a[n++] = s2[i]-'a'+1;
       a[n] = 0;

       build_sa(n+1,30);
       get_Height(n);

       len = strlen(s1);
       int mx = 0;
       for (int i=2; i<=n; i++) if (height[i]>mx) {
          if (0<=sa[i-1] && sa[i-1]<len && len<sa[i]) mx = height[i];
          if (0<=sa[i] && sa[i]<len && len<sa[i-1]) mx = height[i];
       }
       printf("%d\n",mx);
    }
    return 0;
}
