#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long LL;
const int maxn = 1000+5;
struct Line{
    int x,y1,y2,z1,z2;
    int f;
    bool operator <(const Line &rhs) const {
       return x<rhs.x;
    }
}line[maxn*2];
Line L[maxn*2];
int y[maxn*2],z[maxn*2];
int tot,tot_y,tot_z;
int n;

inline void add_Line(int x, int y1, int y2, int z1, int z2,int f){
      line[tot].x = x;  line[tot].f = f;
      line[tot].y1 = y1; line[tot].y2 = y2;
      line[tot].z1 = z1; line[tot].z2 = z2;
}

struct node{
   int l,r;
   int lf,rf;
   int c;
   int once,twice,more;
};

struct Tree{
     node tr[maxn*8];
     #define lch(u) (u<<1)
     #define rch(u) (u<<1|1)
     #define Mid (tr[u].l+tr[u].r)>>1

     void build(int u,int a, int b){
         tr[u].l = a; tr[u].r = b;
         tr[u].lf = y[a]; tr[u].rf = y[b];
         tr[u].c = 0;
         tr[u].once = tr[u].twice = tr[u].more = 0;
         if (a+1==b) return;

         int mid = Mid;
         build(lch(u),a,mid);
         build(rch(u),mid,b);
     }

     void push_up(int u){
        if (tr[u].c > 2){
             tr[u].more = tr[u].rf - tr[u].lf;
             tr[u].once = tr[u].twice = 0;
             return;
        }
        else if (tr[u].c == 2){
           if (tr[u].l+1 == tr[u].r) {
              tr[u].twice = tr[u].rf - tr[u].lf;
              tr[u].more = tr[u].once = 0;
           }
           else {
              tr[u].more = tr[lch(u)].once + tr[lch(u)].twice + tr[lch(u)].more
                         + tr[rch(u)].once + tr[rch(u)].twice + tr[rch(u)].more;
              tr[u].twice = tr[u].rf - tr[u].lf - tr[u].more;
              tr[u].once = 0;
           }
        }
        else if (tr[u].c == 1){
            if (tr[u].l+1 == tr[u].r) {
                tr[u].more = tr[u].twice = 0;
                tr[u].once = tr[u].rf - tr[u].lf;
            }
            else {
                tr[u].more = tr[lch(u)].more + tr[lch(u)].twice
                           + tr[rch(u)].more + tr[rch(u)].twice;
                tr[u].twice = tr[lch(u)].once + tr[rch(u)].once;
                tr[u].once = tr[u].rf - tr[u].lf - tr[u].more - tr[u].twice;
            }
        }
        else {
            if (tr[u].l+1 == tr[u].r) {
                tr[u].more = tr[u].twice = tr[u].once = 0;
            }
            else {
              tr[u].more = tr[lch(u)].more + tr[rch(u)].more;
              tr[u].twice = tr[lch(u)].twice + tr[rch(u)].twice;
              tr[u].once = tr[lch(u)].once + tr[rch(u)].once;
            }
        }
     }

     void update(int u, Line e){
        if (e.y1 <= tr[u].lf && tr[u].rf <= e.y2) {
             tr[u].c += e.f;
             push_up(u);
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
        push_up(u);
     }

}T;

int main(){
    int t;
    scanf("%d",&t);

    int kase = 0;
    while (t--){
        scanf("%d",&n);
        tot = 0;

        int x1,y1,z1,x2,y2,z2;
        for (int i=1; i<=n; i++) {
            scanf("%d %d %d %d %d %d",&x1,&y1,&z1,&x2,&y2,&z2);
            add_Line(x1,y1,y2,z1,z2,1);
            y[tot] = y1; z[tot] = z1; tot++;
            add_Line(x2,y1,y2,z1,z2,-1);
            y[tot] = y2; z[tot] = z2; tot++;
        }
        sort(line,line+tot);
        sort(y,y+tot); tot_y = unique(y,y+tot)-y;
        sort(z,z+tot); tot_z = unique(z,z+tot)-z;
        T.build(1,0,tot-1);

        LL ans = 0;
        LL area = 0;
        for (int i=0; i<tot_z-1; i++) {
            int m = 0;
            for (int j=0; j<tot; j++)
                if (line[j].z1 <= z[i] && z[i] < line[j].z2) L[m++] = line[j];

            area = 0;
            T.update(1,L[0]);
            for (int j=1; j<m; j++) {
                area += (LL)T.tr[1].more*(L[j].x-L[j-1].x);
                T.update(1,L[j]);
            }
            ans += area*(z[i+1]-z[i]);
        }

        printf("Case %d: %I64d\n",++kase,ans);
    }
    return 0;
}
