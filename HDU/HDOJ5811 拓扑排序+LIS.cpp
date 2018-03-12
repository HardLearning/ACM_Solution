#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1000+10;
int n,m,x;
int  a[maxn][maxn];

bool vis[maxn];
int t1[maxn],t2[maxn];
int tot1,tot2;

bool cmp(int x, int y) {return a[x][y] == 1;}

bool judge() {
   for (int i=0; i<tot1; i++) {
      for (int j=i+1; j<tot1; j++) if (a[t1[i]][t1[j]]==0) return 0;
   }

   for (int i=0; i<tot2; i++)  {
      for (int j=i+1; j<tot2; j++) if (a[t2[i]][t2[j]]==0) return 0;
   }
   return 1;
}

int f[maxn];
int g[maxn];

void solve(){
    int j;
    memset(f,-1,sizeof(f));
    for (int i=0; i<tot2; i++) {
        for (j = 0; j<tot1; j++) if (a[t2[i]][t1[j]]==0) continue;
        else break;
        f[i] = j;
        for (; j<tot1; j++) if (a[t2[i]][t1[j]]==0) { f[i] = -1; break; }
    }

    int tot = 0;
    for (int i=0; i<tot2; i++) if (f[i]!=-1) {
        if (!tot || f[i]>=g[tot]) g[++tot] = f[i];
        else *(upper_bound(g+1,g+tot+1,f[i])) = f[i];
    }
    printf("%d\n",tot);
}

char ch;
inline int Read(){
   ch = getchar();
   while (ch<'0' || ch>'9') ch = getchar();
   return ch-'0';
}

int main(){
    while (scanf("%d%d",&n,&m)==2) {
        if (n==0 && m==0) break;
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) a[i][j] = Read();
        }

        for (int i=1; i<=n; i++) vis[i] = 0;
        for (int i=1; i<=m; i++) { scanf("%d",&x); vis[x] = 1; }
        tot1 = tot2 = 0;
        for (int i=1; i<=n; i++) if (vis[i]) t1[tot1++] = i; else t2[tot2++] = i;
        sort(t1,t1+tot1,cmp);
        sort(t2,t2+tot2,cmp);

        if (!judge()) {
            printf("NO\n");
        }
        else {
            printf("YES ");
            solve();
        }
    }
    return 0;
}
