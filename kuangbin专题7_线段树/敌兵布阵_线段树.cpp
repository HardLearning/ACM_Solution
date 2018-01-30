#include <cstdio>
using namespace std;

const int maxn = 50000+5;
int a[maxn];
int n;
struct node{
   int left,right;
   int sum;
};
struct Tree{
   node tr[maxn*4];
   #define lch(u) (u<<1)
   #define rch(u) (u<<1|1)
   #define Mid (tr[u].left+tr[u].right)>>1

   inline void push_up(int u) {
      tr[u].sum = tr[lch(u)].sum + tr[rch(u)].sum;
   }

   void build(int u,int l, int r){
       tr[u].left = l; tr[u].right = r;
       if (l == r) {
           tr[u].sum = a[l];
           return ;
       }
       int mid = Mid;
       build(lch(u),l,mid);
       build(rch(u),mid+1,r);
       push_up(u);
   }

   void add(int u, int pos, int val){
       tr[u].sum += val;
       if (tr[u].left == tr[u].right) return;
       int mid = Mid;
       if (pos<=mid) add(lch(u),pos,val);
       else add(rch(u),pos,val);
   }

   int query(int u, int l, int r){
      if (l<=tr[u].left && tr[u].right<=r) return tr[u].sum;
      int mid = Mid;
      int ans = 0;

      if (r<=mid) ans += query(lch(u),l,r);
      else if (l>mid) ans += query(rch(u),l,r);
      else {
          ans += query(lch(u),l,r);
          ans += query(rch(u),l,r);
      }

      return ans;
   }
}T;

int main(){
    int t;
    scanf("%d",&t);

    int kase = 0;
    while (t--){
        scanf("%d",&n);
        for (int i=1; i<=n; i++) scanf("%d",&a[i]);
        T.build(1,1,n);
        printf("Case %d:\n",++kase);

        char str[10];
        int x,y;
        while (scanf("%s",str)==1){
            if (str[0]=='E') break;
            scanf("%d %d",&x,&y);

            if (str[0]=='A') T.add(1,x,y);
            else if (str[0]=='S') T.add(1,x,-y);
            else {
                printf("%d\n",T.query(1,x,y));
            }
        }
    }
    return 0;
}
