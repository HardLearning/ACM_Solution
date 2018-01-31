#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 50000+10;
struct Edge{
   int to,next;
}edge[maxn];
int head[maxn];
int n,m;
int tot,cnt;
bool vis[maxn];
int start[maxn],End[maxn];

void DFS(int u){
    int v;
    start[u] = ++cnt;
    for (int i=head[u]; i!=-1; i=edge[i].next){
        v = edge[i].to;
        DFS(v);
    }
    End[u] = cnt;
}

void init(){
    int u,v;

    tot = cnt = 0;
    scanf("%d",&n);
    memset(vis,0,sizeof(vis));
    memset(head,-1,sizeof(head));
    for (int i=1; i<n; i++) {
        scanf("%d %d",&u,&v);
        edge[i].to = u;
        edge[i].next = head[v];
        head[v] = i;
        vis[u] = 1;
    }

    for (int i=1; i<=n; i++) if (!vis[i]) {
         DFS(i);
         break;
    }
}

struct node{
   int left,right;
   int lazy,val;
};
struct Tree{
   node tr[maxn*4];
   #define lch(u) (u<<1)
   #define rch(u) (u<<1|1)
   #define Mid (tr[u].left+tr[u].right)>>1

   void build(int u, int a, int b){
       tr[u].left = a; tr[u].right = b;
       tr[u].lazy = 0; tr[u].val = -1;
       if (a == b) return;
       int mid = Mid;
       build(lch(u),a,mid);
       build(rch(u),mid+1,b);
   }

   inline void same(int u, int val){
       if (!u) return;
       tr[u].val = val;
       tr[u].lazy = 1;
   }

   void push_down(int u){
      if (tr[u].lazy == 0) return;
      same(lch(u),tr[u].val);
      same(rch(u),tr[u].val);
      tr[u].lazy = 0;
   }

   void update(int u, int a, int b, int task){
       if (tr[u].left == a && tr[u].right == b) {
           same(u,task);
           return;
       }
       push_down(u);
       int mid = Mid;
       if (b<=mid) update(lch(u),a,b,task);
       else if (a>mid) update(rch(u),a,b,task);
       else {
           update(lch(u),a,mid,task);
           update(rch(u),mid+1,b,task);
       }
   }

   int query(int u, int pos){
       if (tr[u].left == pos && tr[u].right == pos) return tr[u].val;
       push_down(u);
       int mid = Mid;
       if (pos<=mid) return query(lch(u),pos);
       else return query(rch(u),pos);
   }

}T;

int main(){
    int t;
    scanf("%d",&t);

    int kase = 0;
    while (t--){
        init();
        T.build(1,1,cnt);
        printf("Case #%d:\n",++kase);
        scanf("%d",&m);

        char str[5];
        int a,b;
        while (m--){
           scanf("%s",str);
           if (str[0]=='C') {
              scanf("%d",&a);
              printf("%d\n",T.query(1,start[a]));
           }
           else {
               scanf("%d %d",&a,&b);
               T.update(1,start[a],End[a],b);
           }
        }
    }
    return 0;
}
