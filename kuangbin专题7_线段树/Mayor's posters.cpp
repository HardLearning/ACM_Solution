#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 10000+10;
const int maxh = 10000000+10;

struct node{
    int l,r;
    bool covered;
};
struct Tree{
    node tr[maxn*8];
    #define lch(u) (u<<1)
    #define rch(u) (u<<1|1)
    #define Mid (tr[u].l+tr[u].r)>>1

    void build(int u, int a, int b){
       tr[u].l = a; tr[u].r = b;
       tr[u].covered = 0;
       if (a == b) return;
       int mid = Mid;
       build(lch(u),a,mid);
       build(rch(u),mid+1,b);
    }

    bool judge(int u, int a, int b){
       if (tr[u].covered) return 0;
       if (tr[u].l == a && tr[u].r == b) {
           tr[u].covered = 1;
           return 1;
       }

       int mid = Mid;
       bool re;
       if (b<=mid) re = judge(lch(u),a,b);
       else if (a>mid) re = judge(rch(u),a,b);
       else {
           bool b1 = judge(lch(u),a,mid);
           bool b2 = judge(rch(u),mid+1,b);
           re = b1 || b2;
       }

       tr[u].covered = tr[lch(u)].covered && tr[rch(u)].covered;
       return re;
    }
}T;
int n;

struct Node{
   int l,r;
}poster[maxn];
int a[maxn*2],tot;
int Hash[maxh];

int main(){
    int t;
    scanf("%d",&t);
    while (t--){
        scanf("%d",&n);

        tot = 0;
        for (int i=1; i<=n; i++) {
            scanf("%d %d",&poster[i].l,&poster[i].r);
            a[tot++] = poster[i].l;
            a[tot++] = poster[i].r;
        }
        sort(a,a+tot);
        tot = unique(a,a+tot) - a;
        for (int i=0; i<tot; i++) Hash[a[i]] = i;

        T.build(1,0,tot-1);
        int ans = 0;
        for (int i=n; i>=1; i--) {
            if (T.judge(1,Hash[poster[i].l],Hash[poster[i].r])) ans++;
        }

        printf("%d\n",ans);
    }
    return 0;
}
