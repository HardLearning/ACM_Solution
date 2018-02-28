#include <cstdio>
#include <cstring>
using namespace std;

const int INF = (1<<30);
const int maxn = 20;
int w[maxn][maxn],n;
int Lx[maxn],Ly[maxn];
bool vis[maxn];

char str[maxn][maxn];
int idx[maxn][maxn],idy[maxn][maxn];
int totx,toty;

inline int Min(int x, int y) { return x<y?x:y; }
inline int Max(int x, int y) { return x>y?x:y; }

int DFS(int u) {
   for (int v=1; v<=toty; v++) {
      if (w[u][v] && !vis[v]) {
         vis[v] = 1;
         if (Ly[v]==-1 || DFS(Ly[v])) {
             Ly[v]= u;
             return 1;
         }
      }
   }
   return 0;
}

int KM(){
   memset(Ly,-1,sizeof(Ly));
   memset(Lx,-1,sizeof(Lx));

   int ans = 0;
   for (int i=1; i<=totx; i++) {
      memset(vis,0,sizeof(vis));
      ans += DFS(i);
   }
   return ans;
}

int main(){
    while (scanf("%d",&n)==1 && n) {
        for (int i=1; i<=n; i++) scanf("%s",str[i]+1);
        memset(idx,0,sizeof(idx));
        memset(idy,0,sizeof(idy));

        totx=0; toty=0;
        for (int i=1; i<=n; i++)
          for (int j=1; j<=n; j++) {
               if (str[i][j]!='.') continue;
               if (idx[i][j]==0) {
                   totx++;
                   int k = j;
                   while (k<=n && str[i][k]=='.') idx[i][k++] = totx;
               }
               if (idy[i][j]==0) {
                  toty++;
                  int k = i;
                  while (k<=n && str[k][j]=='.') idy[k++][j] = toty;
               }
          }

        memset(w,0,sizeof(w));
        for (int i=1; i<=n; i++)
          for (int j=1; j<=n; j++) {
               if (str[i][j]=='.') w[idx[i][j]][idy[i][j]] = 1;
          }

        printf("%d\n",KM());
    }
    return 0;
}
