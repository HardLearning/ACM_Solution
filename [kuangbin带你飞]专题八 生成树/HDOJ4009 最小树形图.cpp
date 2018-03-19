#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int INF = 1e9;
const int maxn = 1000+10;
struct Point{
   int a,b,c;
}p[maxn];
int X,Y,Z,n;

struct Edge{
    int from,to,w;
}e[maxn*maxn];
int tot,root;

int in[maxn];
int pre[maxn];
int id[maxn];
int vis[maxn];

int x;
char ch;
int Read(){
   ch = getchar();
   while (ch<'0' || ch>'9') ch = getchar();
   x = 0;
   while (ch>='0' && ch<='9') x = (x<<3) + (x<<1) + ch-'0', ch = getchar();
   return x;
}

inline void addEdge(int from, int to, int w) {
    e[tot].from = from;
    e[tot].to = to;
    e[tot].w = w;
    tot++;
}

int solve(int root, int n, int m) {
    int ans = 0;
    int u,v;
    Edge E;

    while (1) {
        for (int i=0; i<n; i++) in[i] = INF;
        for (int i=0; i<m; i++) {
            E = e[i];
            if (E.from != E.to && in[E.to]>E.w) {
                 pre[E.to] = E.from;
                 in[E.to] = E.w;
            }
        }

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

            if (v!=root && id[v] == -1) {
                for (u = pre[v]; u!=v; u = pre[u]) id[u] = tn;
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
    while (scanf("%d%d%d%d",&n,&X,&Y,&Z)==4) {
        if (n==0 && X==0 && Y==0 && Z==0) break;
        tot =  root = 0;
        for (int i=1; i<=n; i++) p[i].a = Read(), p[i].b = Read(), p[i].c = Read();

        int k,idx,cost;
        for (int i=1; i<=n; i++) {
            addEdge(root,i,p[i].c*X);
            k = Read();

            for (int j=1; j<=k; j++) {
                idx = Read();
                if (idx==i) continue;
                cost= (abs(p[i].a-p[idx].a) + abs(p[i].b-p[idx].b) + abs(p[i].c-p[idx].c))*Y;
                if (p[i].c<p[idx].c) cost += Z;
                addEdge(i,idx,cost);
            }
        }

        int ans = solve(root,n+1,tot);
        printf("%d\n",ans);
    }
    return 0;
}
