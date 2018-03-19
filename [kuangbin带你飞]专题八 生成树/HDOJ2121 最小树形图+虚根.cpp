#include <cstring>
#include <cstdio>
using namespace std;

const int INF = 1e9;
const int maxn = 1100;
const int maxm = 20000;
struct Edge{
   int from,to,w;
}e[maxm];

int pre[maxn];
int in[maxn];
int vis[maxn];
int id[maxn];
int n,m;
int real_root;

int x;
char ch;
int Read(){
   ch = getchar();
   while (ch<'0' || ch>'9') ch = getchar();
   x = 0;
   while (ch>='0' && ch<='9') x = (x<<3) + (x<<1) + ch-'0', ch = getchar();
   return x;
}

int solve(int root, int n, int m){
   int ans = 0;
   int u,v;
   Edge E;

   while (1) {
      for (int i=0; i<n; i++) in[i] = INF;
      for (int i=0; i<m; i++) {
          if (e[i].from != e[i].to && e[i].w<in[e[i].to]) {
              pre[e[i].to] = e[i].from;
              in[e[i].to] = e[i].w;
              if (e[i].from == root) real_root = i;
          }
      }

      for (int i=0; i<n; i++) if (i!=root && in[i]==INF) return -1;
      int tn = 0;
      memset(vis,-1,sizeof(vis));
      memset(id,-1,sizeof(id));
      in[root] = 0;

      for (int i=0; i<n; i++) {
          ans += in[i];
          v = i;
          while (vis[v]!=i && id[v]==-1 && v!=root) {
             vis[v] = i;
             v = pre[v];
          }

          if (v!=root && id[v]==-1) {
             for (u = pre[v]; u!=v; u=pre[u]) id[u] = tn;
             id[v] = tn++;
          }
      }
      if (tn == 0) break;
      for (int i=0; i<n; i++) if (id[i]==-1) id[i] = tn++;
      for (int i=0; i<m; i++) {
        v = e[i].to;
        e[i].from = id[e[i].from];
        e[i].to = id[e[i].to];
        if (e[i].from != e[i].to) e[i].w -= in[v];
      }

      n = tn;
      root = id[root];
   }
   return ans;
}


int main(){
    while (scanf("%d%d",&n,&m)==2) {
        int sum = 0, tot = 0;
        for (int i=0; i<m; i++) {
            e[tot].from = Read();
            e[tot].to = Read();
            e[tot].w = Read();
            sum += e[tot++].w;
        }
        sum++;
        for (int i=0; i<n; i++) e[tot].from = n, e[tot].to = i, e[tot].w = sum, tot++;

        int ans = solve(n,n+1,tot);
        if (ans == - 1 || ans>=2*sum) printf("impossible\n\n"); else printf("%d %d\n\n",ans-sum,real_root-m);
    }
    return 0;
}
