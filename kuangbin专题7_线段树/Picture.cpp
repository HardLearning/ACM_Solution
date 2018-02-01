#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn = 5000+5;
struct Line{
   int x1,x2,y;
   int f;
   bool operator <(const Line &rhs) const {
       return y<rhs.y;
   }
}line[maxn*2];
int x[maxn*2],tot_x;

struct node{
   int l,r;
   int lf,rf,len;
   int seg,c;
   bool lcover,rcover;
};
struct Tree{
   node tr[maxn*8];
   #define lch(u) (u<<1)
   #define rch(u) (u<<1|1)
   #define Mid (tr[u].l + tr[u].r )>>1

   void build(int u, int a, int b){
       tr[u].l = a; tr[u].r = b;
       tr[u].lf = x[a]; tr[u].rf = x[b];
       tr[u].len = tr[u].c = tr[u].seg = 0;
       tr[u].rcover = tr[u].lcover = 0;
       if (a+1 == b) return;

       int mid = Mid;
       build(lch(u),a,mid);
       build(rch(u),mid,b);
   }

   void push_up(int u){
      if (tr[u].c>0){
         tr[u].len = tr[u].rf - tr[u].lf;
         tr[u].seg = 1;
         tr[u].lcover = tr[u].rcover = 1;
         return;
      }

      if (tr[u].l + 1 == tr[u].r){
         tr[u].len = tr[u].seg = 0;
         tr[u].lcover = tr[u].rcover = 0;
      }
      else {
         tr[u].len = tr[lch(u)].len + tr[rch(u)].len;
         tr[u].lcover = tr[lch(u)].lcover;
         tr[u].rcover = tr[rch(u)].rcover;
         tr[u].seg = tr[lch(u)].seg + tr[rch(u)].seg;
         if (tr[lch(u)].rcover && tr[rch(u)].lcover) tr[u].seg--;
      }
   }

   void update(int u, Line e){
      if (tr[u].lf == e.x1 && tr[u].rf == e.x2) {
          tr[u].c += e.f;
          push_up(u);
          return;
      }
      if (e.x2 <= tr[lch(u)].rf) update(lch(u),e);
      else if (e.x1>=tr[rch(u)].lf) update(rch(u),e);
      else {
        Line tmp = e;
        tmp.x2 = tr[lch(u)].rf;
        update(lch(u),tmp);

        tmp = e;
        tmp.x1 = tr[rch(u)].lf;
        update(rch(u),tmp);

      }
      push_up(u);
   }

}T;
int n,tot;

inline void add_Line(int x1, int x2, int y, int f){
    line[tot].x1 = x1;
    line[tot].x2 = x2;
    line[tot].y = y;
    line[tot].f = f;
}

int main(){
    int x1,y1,x2,y2;
    while (scanf("%d",&n)==1){
        tot = 0;
        for (int i=1; i<=n; i++) {
            scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
            add_Line(x1,x2,y1,1); x[tot] = x1; tot++;
            add_Line(x1,x2,y2,-1); x[tot] = x2; tot++;
        }
        sort(line,line+tot);
        sort(x,x+tot);
        tot_x = unique(x,x+tot)-x;
        T.build(1,0,tot_x-1);

        int parimeter = 0;
        int last = 0;
        for (int i=0; i<tot-1; i++){
               T.update(1,line[i]);
               parimeter += 2*T.tr[1].seg*(line[i+1].y-line[i].y);
               parimeter += abs(T.tr[1].len-last);
               last = T.tr[1].len;
        }
        T.update(1,line[tot-1]);
        parimeter += abs(T.tr[1].len-last);
        printf("%d\n",parimeter);
    }
    return 0;
}
