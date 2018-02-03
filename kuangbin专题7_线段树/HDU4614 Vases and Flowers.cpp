#include <cstdio>
using namespace std;

const int maxn = 50000+5;
int n,m;
struct node{
   int l,r;
   int first,last;
   int sum;
   int lazy;
};

struct Tree{
   node tr[maxn*4];
   #define lch(u) (u<<1)
   #define rch(u) (u<<1|1)
   #define Mid (tr[u].l + tr[u].r)>>1

   void build(int u,int a, int b) {
       tr[u].l = a;
       tr[u].r = b;
       tr[u].first = a;
       tr[u].last = b;
       tr[u].sum = b-a+1;
       tr[u].lazy = 0;
       if (a == b) return;

       int mid = Mid;
       build(lch(u),a,mid);
       build(rch(u),mid+1,b);
   }

   inline void push_up(int u) {
       if (tr[u].l == tr[u].r) return;
       tr[u].sum = tr[lch(u)].sum + tr[rch(u)].sum;
       tr[u].first = tr[lch(u)].first == -1?tr[rch(u)].first:tr[lch(u)].first;
       tr[u].last = tr[rch(u)].last == -1?tr[lch(u)].last:tr[rch(u)].last;
   }

   inline void push_down(int u){
      if (tr[u].l == tr[u].r) return ;
      if (tr[u].lazy == 1){
          tr[lch(u)].first = tr[lch(u)].l;
          tr[lch(u)].last = tr[lch(u)].r;
          tr[lch(u)].lazy = 1;
          tr[lch(u)].sum = tr[lch(u)].r - tr[lch(u)].l + 1;

          tr[rch(u)].first = tr[rch(u)].l;
          tr[rch(u)].last = tr[rch(u)].r;
          tr[rch(u)].lazy = 1;
          tr[rch(u)].sum = tr[rch(u)].r - tr[rch(u)].l + 1;
      }
      else if (tr[u].lazy == -1){
          tr[lch(u)].first = -1;
          tr[lch(u)].last = -1;
          tr[lch(u)].lazy = -1;
          tr[lch(u)].sum = 0;

          tr[rch(u)].first = -1;
          tr[rch(u)].last = -1;
          tr[rch(u)].lazy = -1;
          tr[rch(u)].sum = 0;
      }

      tr[u].lazy = 0;
   }

   int query_sum(int u,int a, int b){
       if (a == tr[u].l && tr[u].r == b) return tr[u].sum;
       push_down(u);
       int mid = Mid;
       int ans = 0;
       if (b<=mid) ans = query_sum(lch(u),a,b);
       else if (a>mid) ans = query_sum(rch(u),a,b);
       else {
           ans += query_sum(lch(u),a,mid);
           ans += query_sum(rch(u),mid+1,b);
       }
       return ans;
   }

   int bisearch(int u, int F){
       int ans = query_sum(1,u,n);
       if (ans == 0) return -1;
       if (ans<F) return n;

       ans = u;
       int a = u, b = n, mid;
       while (a<=b){
          mid = (a+b)>>1;
          if (query_sum(1,u,mid)>=F) {
               ans = mid;
               b = mid-1;
          }
          else a = mid+1;
       }
       return ans;
   }

   int query_first(int u, int a, int b){
       if (tr[u].l == a && tr[u].r == b) return tr[u].first;
       push_down(u);
       int mid = Mid;
       if (b<=mid) return query_first(lch(u),a,b);
       else if (a>mid) return query_first(rch(u),a,b);
       else {
           int ans = query_first(lch(u),a,mid);
           if (ans == -1) ans = query_first(rch(u),mid+1,b);
           return ans;
       }
   }

   int query_last(int u, int a, int b){
       if (tr[u].l == a && tr[u].r == b) return tr[u].last;
       push_down(u);
       int mid = Mid;
       if (b<=mid) return query_last(lch(u),a,b);
       else if (a>mid) return query_last(rch(u),a,b);
       else {
           int ans = query_last(rch(u),mid+1,b);
           if (ans == -1) ans = query_last(lch(u),a,mid);
           return ans;
       }
   }

   void update(int u, int a, int b, int val){
        if (tr[u].l == a && tr[u].r == b) {
            if (val == 1) {
                tr[u].first = a;
                tr[u].last = b;
                tr[u].sum = b-a+1;
                tr[u].lazy = 1;
            }
            else {
                tr[u].first = tr[u].last = -1;
                tr[u].sum = 0;
                tr[u].lazy = -1;
            }
            return;
        }

        push_down(u);
        int mid = Mid;
        if (b<=mid) update(lch(u),a,b,val);
        else if (a>mid) update(rch(u),a,b,val);
        else {
            update(lch(u),a,mid,val);
            update(rch(u),mid+1,b,val);
        }
        push_up(u);
   }

}T;

int main(){
    int t;
    scanf("%d",&t);
    while (t--){
        scanf("%d %d",&n,&m);
        T.build(1,1,n);

        int x,y,k;
        while (m--){
            scanf("%d %d %d",&k,&x,&y);
            if (k == 1){
               x++;
               int pos = T.bisearch(x,y);
               if (pos == -1) {
                   printf("Can not put any one.\n");
                   continue;
               }
               printf("%d %d\n",T.query_first(1,x,pos)-1,T.query_last(1,x,pos)-1);
               T.update(1,x,pos,0);
            }
            else {
                x++; y++;
                if (x>y) {int z = x; x = y; y = z;}
                printf("%d\n",y-x+1-T.query_sum(1,x,y));
                T.update(1,x,y,1);
            }
        }
        printf("\n");
    }
    return 0;
}
