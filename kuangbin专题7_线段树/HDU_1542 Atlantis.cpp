#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 200+5;
struct Line{
   double x,y1,y2;
   int f;
   bool operator <(const Line &rhs) const {
       return x<rhs.x;
   }
}line[maxn];
double y[maxn];
int n,tot;

struct node{
    int l,r;
    int c;
    double len,lf,rf;
};
struct Tree{
     node tr[maxn*4];
     #define lch(u) (u<<1)
     #define rch(u) (u<<1|1)
     #define Mid (tr[u].l+tr[u].r)>>1

     void build(int u,int a, int b){
        tr[u].l = a; tr[u].r = b;
        tr[u].lf = y[a];
        tr[u].rf = y[b];
        tr[u].c = 0;
        tr[u].len = 0;
        if (a+1 == b) return;
        int mid = Mid;
        build(lch(u),a,mid);
        build(rch(u),mid,b);
     }

    inline void cal(int u){
         if (tr[u].c>0){
            tr[u].len = tr[u].rf - tr[u].lf;
         }
         else {
            if (tr[u].l +1 == tr[u].r) tr[u].len = 0;
            else tr[u].len = tr[lch(u)].len + tr[rch(u)].len;
         }
     }

     void update(int u, Line e){
        if (e.y1 == tr[u].lf && e.y2 == tr[u].rf) {
            tr[u].c += e.f;
            cal(u);
            return;
        }
        if (e.y2 <= tr[lch(u)].rf) update(lch(u),e);
        else if (e.y1 >= tr[rch(u)].lf) update(rch(u),e);
        else {
            Line tmp = e;
            tmp.y2 = tr[lch(u)].rf;
            update(lch(u),tmp);

            tmp = e;
            tmp.y1 = tr[rch(u)].lf;
            update(rch(u),tmp);
        }
        cal(u);
     }
}T;

inline void add_Line(double x, double y1, double y2,int f){
    tot++;
    line[tot].x = x;
    line[tot].y1 = y1;
    line[tot].y2 = y2;
    line[tot].f = f;
}

int main(){
    int kase = 0;
    double x1,y1,x2,y2;
    while (scanf("%d",&n)==1 &&n){
        tot = 0;
        for (int i=1; i<=n; i++) {
            scanf("%lf %lf %lf %lf",&x1,&y1,&x2,&y2);
            add_Line(x1,y1,y2,1);
            y[tot] = y1;
            add_Line(x2,y1,y2,-1);
            y[tot] = y2;
        }
        sort(line+1,line+tot+1);
        sort(y+1,y+tot+1);

        T.build(1,1,tot);
        T.update(1,line[1]);

        double ans = 0;
        for (int i=2; i<=tot; i++) {
            ans += T.tr[1].len*(line[i].x-line[i-1].x);
            T.update(1,line[i]);
        }
        printf("Test case #%d\n",++kase);
        printf("Total explored area: %.2lf\n",ans);
        printf("\n");
    }
    return 0;
}
