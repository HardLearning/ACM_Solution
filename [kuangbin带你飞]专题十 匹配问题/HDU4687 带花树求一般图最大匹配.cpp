#include <vector>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

#define pb push_back
const int maxn = 50;
const int maxm = 130;
int match[maxn];
int fa[maxn],base[maxn];
int inq[maxn],inpath[maxn],inblossom[maxn];
bool G[maxn][maxn],g[maxn][maxn];
int start,finish,newbase;
int n,m;
queue<int>que;

struct Edge{
    int u,v;
    Edge(){}
    Edge(int u, int v):u(u),v(v){};
}e[maxm];

void reset(int u){
    int v;
    while (base[u]!=newbase){
        v = match[u];
        inblossom[base[u]] = inblossom[base[v]] = 1;
        u = fa[v];
        if (base[u]!=newbase) fa[u] = v;
    }
}

int LCA(int u, int v){
    memset(inpath,0,sizeof(inpath));
    while (1) {
        u = base[u];
        inpath[u] = 1;
        if (u==start) break;
        u = fa[match[u]];
    }
    while (1) {
        v = base[v];
        if (inpath[v]) break;
        v = fa[match[v]];
    }
    return v;
}

void BlossomContract(int u, int v){
    newbase = LCA(u,v);
    memset(inblossom,0,sizeof(inblossom));
    reset(u);
    reset(v);
    if (base[u]!=newbase) fa[u] = v;
    if (base[v]!=newbase) fa[v] = u;
    for (int i=1; i<=n; i++) {
        if (inblossom[base[i]]) {
            base[i] = newbase;
            if (!inq[i]) que.push(i);
        }
    }
}

void FindAugmentPath(){
    memset(inq,0,sizeof(inq));
    memset(fa,0,sizeof(fa));
    for (int i=1; i<=n; i++) base[i] = i;
    while (!que.empty()) que.pop();
    que.push(start);
    finish = 0;

    while (!que.empty()){
        int u = que.front(); que.pop();
        for (int v=1; v<=n; v++) {
            if (G[u][v] && base[u]!=base[v] && match[u]!=v){
                if (v==start || match[v]>0 && fa[match[v]]>0){
                    BlossomContract(u,v);
                }
                else if (fa[v]==0){
                    fa[v] = u;
                    if (match[v]>0) que.push(match[v]);
                    else {finish = v; return ; }
                }
            }
        }
    }
}

void AugmentPath(){
    int u,v,w;
    u = finish;
    while (u>0) {
        v = fa[u];
        w = match[v];
        match[v] = u;
        match[u] = v;
        u = w;
    }
}

int Edmonds(){
    memset(match,0,sizeof(match));
    for (int u=1; u<=n; u++)
    if (match[u]==0) {
         start = u;
         FindAugmentPath();
         if (finish>0) AugmentPath();
    }

    int ans = 0;
    for (int i=1; i<=n; i++) if (match[i]>0) ans++;
    return ans;
}

vector<int>a;

int main(){
    while (scanf("%d%d",&n,&m)==2){
        memset(G,0,sizeof(G));
        int x,y;
        for (int i=1; i<=m; i++) {
            scanf("%d%d",&x,&y);
            G[x][y] = G[y][x] = 1;
            e[i] = Edge(x,y);
        }

        memcpy(g,G,sizeof(G));
        int cnt = Edmonds()/2;

        a.clear();
        for (int i=1; i<=m; i++) {
            memcpy(G,g,sizeof(g));
            int u = e[i].u;
            int v = e[i].v;
            for (int j=1; j<=n; j++) G[u][j] = G[j][u] = G[v][j] = G[j][v] = 0;
            int tmp = Edmonds()/2;
            if (tmp<cnt-1) a.pb(i);
        }

        printf("%d\n",a.size());
        if (a.size()==0) { printf("\n"); continue; }
        printf("%d",a[0]);
        for (int i=1; i<a.size(); i++) printf(" %d",a[i]);
        printf("\n");

    }
    return 0;
}
