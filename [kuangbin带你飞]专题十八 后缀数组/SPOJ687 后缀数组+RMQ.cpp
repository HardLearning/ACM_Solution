#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1e5+10;
int s[maxn],sa[maxn],Rank[maxn],height[maxn];
int c[maxn],t[maxn],t2[maxn];
int n;

void build_sa(int n, int m) {
   int *x = t, *y = t2;
   for (int i=0; i<m; i++) c[i] = 0;
   for (int i=0; i<n; i++) c[x[i] = s[i]]++;
   for (int i=1; i<m; i++) c[i] += c[i-1];
   for (int i=n-1; i>=0; i--) sa[--c[x[i]]] = i;

   for (int k=1; k<=n; k<<=1) {
      int p =0;
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
      while (s[i+k] == s[j+k]) k++;
      height[Rank[i]] = k;
   }
}

int f[maxn][20];
inline int Min(int x, int y) {return x<y?x:y; }
inline int Max(int x, int y) {return x>y?x:y; }
void RMQ_init(int n) {
   for (int i=1; i<=n; i++) f[i][0] = height[i];
   for (int j=1; (1<<j)<=n; j++) {
     for (int i=1; i+(1<<j)-1<=n; i++)
        f[i][j] = Min(f[i][j-1],f[i+(1<<j-1)][j-1]);
   }
}

int RMQ(int L, int R){
   L = Rank[L];
   R = Rank[R];
   if (L>R) swap(L,R);
   L++;
   int k = 0;
   while ((1<<(k+1)) <= R-L+1) k++;
   return Min(f[L][k],f[R-(1<<k)+1][k]);
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&n);
        char p[5];
        for (int i=0; i<n; i++) scanf("%s",p), s[i] = p[0]-'a'+1;
        s[n] = 0;
        build_sa(n+1,5);
        get_Height(n);
        RMQ_init(n);

        int mx = 1;
        int t0, z, times;
        for (int L = 1; L<n; L++) {
            for (int i=0; i+L<n; i+=L) {
                z = RMQ(i,i+L);
                times = z/L+1;
                t0 = i-(L-z%L);

                if (t0>=0 && z%L) {
                    if (RMQ(t0,t0+L)>=z) times++;
                }

                mx = Max(mx,times);
            }
        }
        printf("%d\n",mx);

    }
    return 0;
}
