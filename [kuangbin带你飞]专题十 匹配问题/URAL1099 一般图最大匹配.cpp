#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int maxn = 230;
int match[maxn];
int fa[maxn],base[maxn];
int inq[maxn],inpath[maxn],inblossom[maxn];
queue<int>que;
bool G[maxn][maxn];
int start,finish,newbase;
int n;

void CreatePath(){
     int u,v;
     memset(G,0,sizeof(G));
     scanf("%d",&n);
     while (scanf("%d%d",&u,&v)==2){
        G[u][v] = G[v][u] = 1;
     }
}

int LCA(int u, int v){
    memset(inpath,0,sizeof(inpath));
    while (1){
        u = base[u];
        inpath[u] = 1;
        if (u==start) break;
        u = fa[match[u]];
    }
    while (1){
        v = base[v];
        if (inpath[v]) break;
        v = fa[match[v]];
    }
    return v;
}

void reset(int u){
    int v;
    while (base[u]!=newbase){
        v = match[u];
        inblossom[base[u]] = inblossom[base[v]] = 1;
        u = fa[v];
        if (base[u]!=newbase) fa[u] = v;
    }
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
            if (G[u][v] && base[u]!=base[v] && match[u]!=v) {
               if (v==start || match[v]>0 && fa[match[v]]>0) {
                   BlossomContract(u,v);
               }
               else if (fa[v]==0) {
                   fa[v] = u;
                   if (match[v]>0) que.push(match[v]);
                   else {
                      finish = v;
                      return ;
                   }
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

void Edmonds(){
    memset(match,0,sizeof(match));
    for (int u=1; u<=n; u++) {
        if (match[u]==0) {
            start = u;
            FindAugmentPath();
            if (finish>0) AugmentPath();
        }
    }
}

void Print(){
    int cnt = 0;
    for (int i=1; i<=n; i++) if (match[i]>0) cnt++;
    printf("%d\n",cnt);
    for (int i=1; i<=n; i++) if (i<match[i]) printf("%d %d\n",i,match[i]);
}

int main(){
    CreatePath();
    Edmonds();
    Print();
    return 0;
}
