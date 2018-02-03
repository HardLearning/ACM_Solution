#include <cstdio>
using namespace std;

const int maxn = 100000+5;
struct node{
   int l,r;
   int mx,lmx,rmx;
   int mx_g,lmx_g,rmx_g;
};

struct Tree{
    node tr[maxn*4];
    #define lch(u) (u<<1)
    #define rch(u) (u<<1|1)
    #define Mid (tr[u].l+tr[u].r)>>1

    inline int Max(int x, int y) { return x>y?x:y; }
    void build(int u,int a, int b){
         tr[u].l = a;
         tr[u].r = b;
         tr[u].mx  = tr[u].lmx = tr[u].rmx = b-a+1;
         tr[u].mx_g  = tr[u].lmx_g = tr[u].rmx_g = b-a+1;
         if (a == b) return ;
         int mid = Mid;
         build(lch(u),a,mid);
         build(rch(u),mid+1,b);
    }

    inline void push_up(int u){
        if (tr[u].l == tr[u].r) return;
        tr[u].lmx = tr[lch(u)].lmx;
        if (tr[lch(u)].lmx == tr[lch(u)].r-tr[lch(u)].l+1) tr[u].lmx += tr[rch(u)].lmx;
        tr[u].rmx = tr[rch(u)].rmx;
        if (tr[rch(u)].rmx == tr[rch(u)].r-tr[rch(u)].l+1) tr[u].rmx += tr[lch(u)].rmx;
        tr[u].mx = Max(tr[lch(u)].mx,tr[rch(u)].mx);
        tr[u].mx = Max(tr[u].mx,Max(tr[u].lmx,tr[u].rmx));
        tr[u].mx = Max(tr[u].mx,tr[lch(u)].rmx+tr[rch(u)].lmx);

        tr[u].lmx_g = tr[lch(u)].lmx_g;
        if (tr[lch(u)].lmx_g == tr[lch(u)].r-tr[lch(u)].l+1) tr[u].lmx_g += tr[rch(u)].lmx_g;
        tr[u].rmx_g = tr[rch(u)].rmx_g;
        if (tr[rch(u)].rmx_g == tr[rch(u)].r-tr[rch(u)].l+1) tr[u].rmx_g += tr[lch(u)].rmx_g;
        tr[u].mx_g = Max(tr[lch(u)].mx_g,tr[rch(u)].mx_g);
        tr[u].mx_g = Max(tr[u].mx_g,Max(tr[u].lmx_g,tr[u].rmx_g));
        tr[u].mx_g = Max(tr[u].mx_g,tr[lch(u)].rmx_g+tr[rch(u)].lmx_g);
    }

    inline void push_down(int u){
        if (tr[u].l == tr[u].r) return ;

        if (tr[u].mx == 0){
            tr[lch(u)].mx = tr[lch(u)].lmx = tr[lch(u)].rmx = 0;
            tr[rch(u)].mx = tr[rch(u)].lmx = tr[rch(u)].rmx = 0;
        }
        if (tr[u].mx == tr[u].r - tr[u].l + 1) {
            tr[lch(u)].mx = tr[lch(u)].lmx = tr[lch(u)].rmx = tr[lch(u)].r - tr[lch(u)].l + 1;
            tr[rch(u)].mx = tr[rch(u)].lmx = tr[rch(u)].rmx = tr[rch(u)].r - tr[rch(u)].l + 1;
        }

        if (tr[u].mx_g == 0){
            tr[lch(u)].mx_g = tr[lch(u)].lmx_g = tr[lch(u)].rmx_g = 0;
            tr[rch(u)].mx_g = tr[rch(u)].lmx_g = tr[rch(u)].rmx_g = 0;
        }
        if (tr[u].mx_g == tr[u].r - tr[u].l + 1) {
            tr[lch(u)].mx_g = tr[lch(u)].lmx_g = tr[lch(u)].rmx_g = tr[lch(u)].r - tr[lch(u)].l + 1;
            tr[rch(u)].mx_g = tr[rch(u)].lmx_g = tr[rch(u)].rmx_g = tr[rch(u)].r - tr[rch(u)].l + 1;
        }
    }

    void clean(int u, int a, int b){
        if (tr[u].l == a && tr[u].r == b){
           tr[u].mx  = tr[u].lmx = tr[u].rmx = b-a+1;
           tr[u].mx_g  = tr[u].lmx_g = tr[u].rmx_g = b-a+1;
           return;
        }

        push_down(u);
        int mid = Mid;
        if (b<=mid) clean(lch(u),a,b);
        else if (a>mid) clean(rch(u),a,b);
        else {
            clean(lch(u),a,mid);
            clean(rch(u),mid+1,b);
        }
        push_up(u);
    }

    int query(int u, int val){
       if (tr[u].mx < val) return 0;
       if (tr[u].lmx>=val) return tr[u].l;
       if (tr[lch(u)].mx>=val) return query(lch(u),val);
       if (tr[lch(u)].rmx + tr[rch(u)].lmx>=val) return tr[lch(u)].r-tr[lch(u)].rmx+1;
       return query(rch(u),val);
    }

    int query_g(int u, int val){
       if (tr[u].mx_g < val) return 0;
       if (tr[u].lmx_g>=val) return tr[u].l;
       if (tr[lch(u)].mx_g>=val) return query_g(lch(u),val);
       if (tr[lch(u)].rmx_g + tr[rch(u)].lmx_g>=val) return tr[lch(u)].r-tr[lch(u)].rmx_g+1;
       return query_g(rch(u),val);
    }

    void occupy(int u, int a, int b){
        if (tr[u].l == a && tr[u].r == b) {
            tr[u].mx = tr[u].lmx = tr[u].rmx = 0;
            return ;
        }

        push_down(u);
        int mid = Mid;
        if (b<=mid) occupy(lch(u),a,b);
        else if (a>mid) occupy(rch(u),a,b);
        else {
            occupy(lch(u),a,mid);
            occupy(rch(u),mid+1,b);
        }
        push_up(u);
    }

    void occupy_g(int u, int a, int b){
        if (tr[u].l == a && tr[u].r == b) {
            tr[u].mx = tr[u].lmx = tr[u].rmx = 0;
            tr[u].mx_g = tr[u].lmx_g = tr[u].rmx_g = 0;
            return ;
        }

        push_down(u);
        int mid = Mid;
        if (b<=mid) occupy_g(lch(u),a,b);
        else if (a>mid) occupy_g(rch(u),a,b);
        else {
            occupy_g(lch(u),a,mid);
            occupy_g(rch(u),mid+1,b);
        }
        push_up(u);
    }
}T;
int n,q;

int main(){
    int t;
    scanf("%d",&t);

    int kase  = 0;
    while (t--){
        scanf("%d %d",&n,&q);
        T.build(1,1,n);
        printf("Case %d:\n",++kase);

        char str[20];
        int x,y;
        while (q--){
            scanf("%s",str);
            if (str[0]=='S') {
                scanf("%d %d",&x,&y);
                T.clean(1,x,y);
                printf("I am the hope of chinese chengxuyuan!!\n");
            }
            else if (str[0]=='D'){
                scanf("%d",&x);
                int p = T.query(1,x);
                if (p == 0) printf("fly with yourself\n");
                else {
                    T.occupy(1,p,p+x-1);
                    printf("%d,let's fly\n",p);
                }
            }
            else {
                scanf("%d",&x);
                int p = T.query(1,x);
                if (p!=0) {
                    T.occupy_g(1,p,p+x-1);
                    printf("%d,don't put my gezi\n",p);
                    continue;
                }
                p = T.query_g(1,x);
                if (p!=0) {
                    T.occupy_g(1,p,p+x-1);
                    printf("%d,don't put my gezi\n",p);
                }
                else printf("wait for me\n");
            }
        }
    }
    return 0;
}
