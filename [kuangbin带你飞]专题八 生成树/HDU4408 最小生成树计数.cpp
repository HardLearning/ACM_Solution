#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int maxm = 1100;
const int maxn = 110;
typedef long long LL;
LL p,ans;
int n,m;

int fa[maxn],ka[maxn],vis[maxn];
LL mat[maxn][maxn],g[maxn][maxn];
vector<int>G[maxn];

struct Edge{
   int u,v,w;
   bool operator <(const Edge& rhs) const {
       return w<rhs.w;
   }
}e[maxm];

LL det(int n) {
   LL ret = 1;
   for (int i=0; i<n; i++)
     for (int j=0; j<n; j++) mat[i][j] %= p;

   bool flag = 0;
   for (int i=0; i<n; i++) {
       if (!mat[i][i]) {
           flag = 0;
           for (int j=i+1; j<n; j++) if (mat[j][i]) {
              flag = 1;
              for (int k=i; k<n; k++) swap(mat[i][k],mat[j][k]);
              ret = -ret;
              break;
           }
           if (!flag) return 0;
       }

       for (int j=i+1; j<n; j++) {
           while (mat[j][i]) {
               LL t = mat[i][i] / mat[j][i];
               for (int k=i; k<n; k++) {
                   mat[i][k] -= t*mat[j][k];
                   mat[i][k] %= p;
                   swap(mat[i][k],mat[j][k]);
               }
               ret = -ret;
           }
       }
       ret *= mat[i][i];
       ret %= p;
   }
   return (ret+p)%p;
}

int Find_fa(int x) {
    if (fa[x]==x) return x;
    return fa[x] = Find_fa(fa[x]);
}

int Find_ka(int x){
    if (ka[x]==x) return x;
    return ka[x] = Find_ka(ka[x]);
}

void matrix_tree(){
    for (int i=0; i<n; i++) G[i].clear();
    for (int i=0; i<n; i++) if (vis[i]) {
        vis[i] = 0;
        G[Find_ka(i)].push_back(i);
    }

    int u,v;
    for (int i=0; i<n; i++) {
        if (G[i].size()>1) {
            memset(mat,0,sizeof(mat));
            for (int j=0; j<G[i].size(); j++) {
                for (int k=j+1; k<G[i].size(); k++) {
                    u = G[i][j]; v = G[i][k];
                    if (g[u][v]) {
                         mat[k][j] = mat[j][k] -= g[u][v];
                         mat[k][k] += g[u][v];
                         mat[j][j] += g[u][v];
                    }
                }
            }
        }

        ans = ans*det(G[i].size()-1)%p;
        for (int j=0; j<G[i].size(); j++) fa[G[i][j]] = i;
    }
    for (int i=0; i<n; i++) ka[i] = fa[i] = Find_fa(i);
}

int main(){
    while (scanf("%d%d%I64d",&n,&m,&p)==3) {
        if (n==0 && m==0 && p==0) break;
        for (int i=0; i<n; i++) fa[i] = ka[i] = i;
        int x,y,z;
        for (int i=0; i<m; i++) {
            scanf("%d%d%d",&x,&y,&z);
            x--; y--;
            e[i] = (Edge){x,y,z};
        }
        sort(e,e+m);
        memset(g,0,sizeof(g));
        memset(vis,0,sizeof(vis));
        ans = 1;

        int u,v;
        for (int i=0; i<=m; i++) {
            if (i && e[i].w!=e[i-1].w || i==m) matrix_tree();
            if (i == m) break;

            u = Find_fa(e[i].u);
            v = Find_fa(e[i].v);
            if (u!=v) {
                 vis[v] = vis[u] = 1;
                 ka[Find_ka(u)] = Find_ka(v);
                 g[u][v]++; g[v][u]++;
            }
        }

        bool f = 1;
        for (int i=1; i<n; i++) if (fa[i]!=fa[i-1]) f = 0;
        if (f==0) printf("0\n"); else printf("%I64d\n",ans%p);

    }
    return 0;
}
