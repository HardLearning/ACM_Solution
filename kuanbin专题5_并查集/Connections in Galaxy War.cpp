#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

bool isfirst;
int n;
const int maxn = 10000+10;
const int maxm = 20000+10;
map<int,int>mp[maxn];
int fa[maxn];
int idx[maxn]; // the index of the largest value
int val[maxn]; // the largest val
int p[maxn];

inline void init(){
    memset(fa,-1,sizeof(fa));
    for (int i=0; i<n; i++) {
         scanf("%d",&p[i]);
         val[i] = p[i];
         idx[i] = i;
         mp[i].clear();
    }
}

int m;
int u,v;
struct Edge{
    int x,y;
}e[maxm];
bool vis[maxm];

int Q;
const int maxq = 50000+5;
struct node{
    int x,y;
    int op;
}q[maxq];
int ans[maxq];


inline void Swap(int &a, int &b) {int c = a; a = b; b = c; }

int Find(int x){
   if (fa[x] == -1) return x;
   return fa[x] = Find(fa[x]);
}

void Merge(int x, int y){
    x = Find(x); y = Find(y);
    if (x == y) return ;
    fa[x] = y;
    if (val[x]>val[y]) {
        val[y] = val[x];
        idx[y] = idx[x];
    }
    else if (val[x] == val[y] && idx[y]>idx[x]) idx[y] = idx[x];
}

int main(){
    isfirst = 1;
    while (scanf("%d",&n)==1) {
         init();
         scanf("%d",&m);
         for (int i=1; i<=m; i++) {
              scanf("%d %d",&u,&v);
              if (u>v) Swap(u,v);
              e[i].x = u;
              e[i].y = v;
              mp[u][v] = i;
         }
         memset(vis,0,sizeof(vis));

         char str[20];
         scanf("%d",&Q);
         for (int i=1; i<=Q; i++) {
            scanf("%s",str);
            if (str[0]=='q') {
                scanf("%d",&q[i].x);
                q[i].op = 0;
            }
            else {
                q[i].op = 1;
                scanf("%d %d",&u,&v);
                if (u>v) Swap(u,v);
                q[i].x = u;
                q[i].y = v;
                vis[mp[u][v]] = 1;
             }
         }

         for (int i=1; i<=m; i++) if (!vis[i]) Merge(e[i].x,e[i].y);

         int tot = 1;
         for (int i=Q; i>=1; i--) {
            if (q[i].op == 1) Merge(q[i].x,q[i].y);
            else {
                u = Find(q[i].x);
                if (val[u]>p[q[i].x]) ans[tot] = idx[u]; else ans[tot] = -1;
                tot++;
            }
         }

         if (isfirst) isfirst = 0; else printf("\n");
         for (int i=tot-1; i>=1; i--) printf("%d\n",ans[i]);
    }
    return 0;
}
