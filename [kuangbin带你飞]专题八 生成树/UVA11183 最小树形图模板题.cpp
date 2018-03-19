#include <cstdio>
#include <cstring>
using namespace std;

const int INF = 1e9;
const int maxn = 1000+10;
const int maxm = 40000+10;
struct Edge{
   int from,to,w;
}e[maxm];

int pre[maxn];
int in[maxn];
int id[maxn];
int vis[maxn];
int n,m;

int x;
char ch;
int Read(){
   ch = getchar();
   while (ch<'0' || ch>'9') ch = getchar();
   x = 0;
   while (ch>='0' && ch<='9') x = x*10+ch-'0', ch = getchar();
   return x;
}

int solve(int root, int n, int m){
    int ans = 0;
    int u,v;
    Edge E;

    while (1) {
        for (int i=0; i<n; i++) in[i] = INF;
        for (int i=0; i<m; i++) {
            E = e[i];
            if (E.from != E.to && E.w < in[E.to]) {
                in[E.to] = E.w;
                pre[E.to] = E.from;
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

        if (tn == 0 ) break;
        for (int i=0; i<n; i++) if (id[i]==-1) id[i] = tn++;
        for (int i=0; i<m; i++) {
            v = e[i].to;
            u = e[i].from;
            e[i].from = id[u];
            e[i].to = id[v];
            if (e[i].from!=e[i].to) e[i].w -= in[v];
        }

        n = tn;
        root = id[root];
    }
    return ans;
}

int main(){
    int T;
    scanf("%d",&T);
    for (int kase = 1; kase<=T; kase++) {
        scanf("%d%d",&n,&m);
        for (int i=0; i<m; i++) {
            e[i].from = Read();
            e[i].to = Read();
            e[i].w = Read();
        }

        int root = 0;
        int ans = solve(root,n,m);
        if (ans == - 1) printf("Case #%d: Possums!\n",kase);
        else printf("Case #%d: %d\n",kase,ans);
    }
    return 0;
}
