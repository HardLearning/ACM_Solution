#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1<<25;
const int maxn = 20005;
int n,K,m;
int s[maxn],sa[maxn];
int t[maxn],t2[maxn],c[maxn];

void build_sa(int n, int m){
   int i, *x = t, *y = t2;
   for (int i=0; i<m; i++) c[i] = 0;
   for (int i=0; i<n; i++) c[x[i] = s[i] ]++;
   for (int i=1; i<m; i++) c[i] += c[i-1];
   for (int i=n-1; i>=0; i--) sa[--c[x[i]]] = i;
   for (int k=1; k<=n; k<<=1) {
       int p = 0;
       for (int i=n-k; i<n; i++) y[p++] = i;
       for (int i=0; i<n; i++) if (sa[i]>=k) y[p++] = sa[i] - k;
       for (int i=0; i<m; i++) c[i] = 0;
       for (int i=0; i<n; i++) c[x[y[i]]]++;
       for (int i=0; i<m; i++) c[i] += c[i-1];
       for (int i=n-1; i>=0; i--) sa[--c[x[y[i]]]] = y[i];
       swap(x,y);
       p = 1; x[sa[0]] = 0;
       for (int i=1; i<n; i++)
         x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k] ? p-1:p++;
       if (p>=n) break;
       m = p;
   }
}

inline int Min(int x, int y) {return x<y?x:y; }
inline int Max(int x, int y) {return x>y?x:y; }

int Rank[maxn],height[maxn];
void getHeight(int n){
    int i,k = 0;
    for ( i=1; i<=n; i++) Rank[sa[i]] = i;
    for ( i=0; i<n; i++) {
        if (k) k--;
        int j = sa[Rank[i]-1];
        while (s[i+k]==s[j+k]) k++;
        height[Rank[i]] = k;
    }
}

bool judge(int d){
     int cnt = 1;
     for (int i=2; i<=n; i++) {
        if (cnt>=K) return 1;
        if (height[i]>=d) cnt++;
        else {
            cnt = 1;
        }
     }
     return cnt>=K;
}

int Binary_Search(int n){
   int left = 1, right = n;
   int mid, ans = 1;
   while (left<=right) {
       mid = (left+right)>>1;
       if (judge(mid)) {
          ans = mid;
          left = mid+1;
       }
       else right = mid-1;
   }
   return ans;
}

int main(){
    while (scanf("%d%d",&n,&K)==2){
        m = -INF;
        for (int i=0; i<n; i++) scanf("%d",&s[i]),m = Max(m,s[i]);
        s[n] = 0;
        build_sa(n+1,m+1);
        getHeight(n);
        printf("%d\n",Binary_Search(n));
    }
    return 0;
}
