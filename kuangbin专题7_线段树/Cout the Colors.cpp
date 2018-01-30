#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 8000+5;
struct node{
   int left,right;
   int col;
};
int color[maxn],pre;

struct Tree{
   node tr[maxn*4];
   #define lch(u) (u<<1)
   #define rch(u) (u<<1|1)
   #define Mid (tr[u].left+tr[u].right)>>1

   void build(int u, int a, int b){
       tr[u].left = a; tr[u].right = b; tr[u].col = -1;
       if (a+1 == b) return;
       int mid = Mid;
       build(lch(u),a,mid);
       build(rch(u),mid,b);
   }

   void push_down(int u){
       if (tr[u].col <0) return;
       tr[lch(u)].col = tr[rch(u)].col = tr[u].col;
       tr[u].col = -2;
   }

   void update(int u, int a, int b, int c){
       if (a == b) return;
       if (tr[u].col == c) return;
       if (a<=tr[u].left && tr[u].right <= b) {
           tr[u].col = c;
           return;
       }

       push_down(u);
       int mid = Mid;
       if (b<=mid) update(lch(u),a,b,c);
       else if (a>mid) update(rch(u),a,b,c);
       else {
           update(lch(u),a,mid,c);
           update(rch(u),mid,b,c);
       }
       tr[u].col = -2;
   }

   void query(int u){
       if (tr[u].col == -1) { // no color
          pre = -1;
          return;
       }

       if (tr[u].col == -2) { // it means there are more than one color in this segment
           if (tr[u].left+1!=tr[u].right) {
              query(lch(u));
              query(rch(u));
           }
       }
       else {
           if (tr[u].col!=pre) { // pre records the color of the segment before u
               pre = tr[u].col;
               color[pre]++;
           }
       }
   }
}T;

int n;
int main(){
    while (scanf("%d",&n)==1){
        T.build(1,1,8001);

        int a,b,c;
        while (n--) {
            scanf("%d %d %d",&a,&b,&c);
            T.update(1,a+1,b+1,c);
        }

        memset(color,0,sizeof(color));
        pre = -1;
        T.query(1);

        for (int i=0; i<maxn; i++) if (color[i]) printf("%d %d\n",i,color[i]);
        printf("\n");
    }
    return 0;
}
