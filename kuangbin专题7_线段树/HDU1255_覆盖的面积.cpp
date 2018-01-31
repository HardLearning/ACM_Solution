#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 2000+5;
struct Line{
   double x,y1,y2;
   int f;
   bool operator <(const Line &rhs) const {
       return x<rhs.x;
   }
}line[maxn];
double y[maxn];
int tot,n;

inline void add_Line(double x,double y1,double y2,int f){
    tot++;
    line[tot].x = x;
    line[tot].y1 = y1;
    line[tot].y2 = y2;
    line[tot].f = f;
}

struct node{
   int l,r;
   int c;
   double lf,rf;
   double one,more;
};

struct Tree{
    node tr[maxn*4];
    #define lch(u) (u<<1)
    #define rch(u) (u<<1|1)
    #define Mid (tr[u].l+tr[u].r)>>1

    void build(int u,int a, int b){
        tr[u].l = a; tr[u].r = b;
        tr[u].one = tr[u].more = 0;
        tr[u].lf = y[a];
        tr[u].rf = y[b];
        tr[u].c = 0;
        if (a+1==b) return;
        int mid = Mid;
        build(lch(u),a,mid);
        build(rch(u),mid,b);
    }

    void cal(int u){
        if (tr[u].c >= 2) {
            tr[u].more = tr[u].one = tr[u].rf - tr[u].lf;
            return ;
        }
        else if (tr[u].c == 1) {
             tr[u].one = tr[u].rf - tr[u].lf;
             if (tr[u].l+1==tr[u].r) tr[u].more = 0;
             else tr[u].more = tr[lch(u)].one + tr[rch(u)].one;
        }
        else {
            if (tr[u].l+1 == tr[u].r) tr[u].one = tr[u].more = 0;
            else {
                tr[u].one = tr[lch(u)].one + tr[rch(u)].one;
                tr[u].more = tr[lch(u)].more + tr[rch(u)].more;
            }
        }
    }

    void update(int u, Line e){
        if (e.y1 == tr[u].lf && e.y2 == tr[u].rf) {
            tr[u].c += e.f;
            cal(u);
            return ;
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

int main(){
    int t;
    double x1,y1,x2,y2;

    scanf("%d",&t);
    while (t--){
        tot = 0;
        scanf("%d",&n);
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
            ans += T.tr[1].more*(line[i].x-line[i-1].x);
            T.update(1,line[i]);
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}
