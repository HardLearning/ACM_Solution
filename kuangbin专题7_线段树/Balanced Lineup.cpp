#include <cstdio>
using namespace std;

const int maxn = 50000+5;
int h[maxn];
struct node{
   int left,right;
   int mx,mn;
};
struct Tree{
   node tr[maxn*4];
   #define lch(u) (u<<1)
   #define rch(u) (u<<1|1)
   #define Mid (tr[u].left+tr[u].right)>>1

   inline int Max(int x, int y){ return x>y?x:y; }
   inline int Min(int x, int y){ return x<y?x:y; }

   void push_up(int u){
       tr[u].mx = Max(tr[lch(u)].mx,tr[rch(u)].mx);
       tr[u].mn = Min(tr[lch(u)].mn,tr[rch(u)].mn);
   }

   void build(int u, int a, int b){
      tr[u].left = a; tr[u].right = b;
      if (a == b) {
          tr[u].mx = tr[u].mn = h[a];
          return;
      }
      int mid = Mid;
      build(lch(u),a,mid);
      build(rch(u),mid+1,b);
      push_up(u);
   }

   int query_max(int u,int a, int b){
      if (a<=tr[u].left && tr[u].right<=b) return tr[u].mx;
      int mid = Mid;
      if (b<=mid) return query_max(lch(u),a,b);
      else if (a>mid) return query_max(rch(u),a,b);
      else return Max(query_max(lch(u),a,mid),query_max(rch(u),mid+1,b));
   }

   int query_min(int u,int a, int b){
      if (a<=tr[u].left && tr[u].right<=b) return tr[u].mn;
      int mid = Mid;
      if (b<=mid) return query_min(lch(u),a,b);
      else if (a>mid) return query_min(rch(u),a,b);
      else return Min(query_min(lch(u),a,mid),query_min(rch(u),mid+1,b));
   }
}T;
int n,q;

int main(){
    while (scanf("%d %d",&n,&q)==2){
        for (int i=1; i<=n; i++) scanf("%d",&h[i]);
        T.build(1,1,n);

        int a,b;
        while (q--){
            scanf("%d %d",&a,&b);
            printf("%d\n",T.query_max(1,a,b)-T.query_min(1,a,b));
        }
    }
    return 0;
}
