#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 1000*5;
const int maxe = 1000*500+5;
struct Point{
    int x,y,p;
}city[maxn];
int n;

const double eps = 1e-8;
int dcmp(double x) {
    if (fabs(x)<eps) return 0;
    return x<0?-1:1;
}

struct Edge{
   int x,y;
   double w;
   bool operator <(const Edge& rhs) const {
      return dcmp(w-rhs.w)<0;
   }
}e[maxe];
int tot;

int fa[maxn];
int Find(int x) {
   if (fa[x]==x) return x;
   return fa[x] = Find(fa[x]);
}

double total_length;
vector<int>G;
void kruskal(){
    total_length = 0;
    G.clear();
    int num = 0;
    int tx,ty;
    for (int i=0; i<tot; i++) {
        tx = Find(e[i].x);
        ty = Find(e[i].y);
        if (tx!=ty) {
            total_length += e[i].w;
            G.push_back(i);
            num++;
            fa[tx] = ty;
        }
        if (num>=n-1) break;
    }
}

inline double Length(int i, int j) {
   return sqrt((city[i].x-city[j].x)*(city[i].x-city[j].x) + (city[i].y-city[j].y)*(city[i].y-city[j].y));
}


vector<int>g[maxn];
bool vis[maxn];

inline int Max(int x, int y) {return x>y?x:y;}
int mx1,mx2;
int dfs(int u){
   int tmp = city[u].p;
   vis[u] = 1;
   for (int i=0; i<g[u].size(); i++) if (!vis[g[u][i]]) tmp = Max(tmp,dfs(g[u][i]));
   return tmp;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        for (int i=1; i<=n; i++) scanf("%d%d%d",&city[i].x,&city[i].y,&city[i].p);
        tot = 0;
        for (int i=1; i<=n; i++) {
            for (int j=i+1; j<=n; j++) {
                e[tot].x = i; e[tot].y = j;
                e[tot].w = Length(i,j);
                tot++;
            }
        }
        sort(e,e+tot);
        for (int i=1; i<=n; i++) fa[i] = i;
        kruskal();

        double ans = 0;
        int u,v;
        for (int i=0; i<G.size(); i++) {
           for (int k=1; k<=n; k++) g[k].clear(),vis[k] = 0;
           for (int k=0; k<G.size(); k++) if (i!=k) {
              u = e[G[k]].x; v = e[G[k]].y;
              g[u].push_back(v);
              g[v].push_back(u);
           }
           u = e[G[i]].x;
           v = e[G[i]].y;
           mx1 = dfs(u);
           mx2 = dfs(v);
           ans = max(ans,1.0*(mx1+mx2)/(total_length-e[G[i]].w));
        }
        printf("%.2f\n",ans);
    }
    return 0;
}
