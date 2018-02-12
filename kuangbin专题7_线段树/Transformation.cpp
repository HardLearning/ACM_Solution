#include <cstdio>
using namespace std;

const int maxn = 100000+5;
const int mod = 10007;
struct node{
   int l,r;
   int sum1,sum2,sum3;
   int lazy1,lazy2,lazy3;
};

struct Tree{
    node tr[maxn*4];
    #define lch(u) (u<<1)
    #define rch(u) (u<<1|1)
    #define Mid (tr[u].l + tr[u].r)>>1

    inline void push_up(int u){
       if (tr[u].l == tr[u].r) return;
       tr[u].sum1 = (tr[lch(u)].sum1 + tr[rch(u)].sum1)%mod;
       tr[u].sum2 = (tr[lch(u)].sum2 + tr[rch(u)].sum2)%mod;
       tr[u].sum3 = (tr[lch(u)].sum3 + tr[rch(u)].sum3)%mod;
    }

    inline int Length(int u){ return (tr[u].r-tr[u].l+1)%mod; }
    void push_down(int u){
        if (tr[u].l == tr[u].r) return;

        int len_l = Length(lch(u));
        int len_r = Length(rch(u));
        if (tr[u].lazy3 != 0) {
            tr[lch(u)].lazy3 = tr[rch(u)].lazy3 = tr[u].lazy3;
            tr[lch(u)].lazy1 = tr[rch(u)].lazy1 = 0;
            tr[lch(u)].lazy2 = tr[rch(u)].lazy2 = 1;

            tr[lch(u)].sum1 = len_l*tr[lch(u)].lazy3%mod;
            tr[lch(u)].sum2 = tr[lch(u)].sum1*tr[lch(u)].lazy3%mod;
            tr[lch(u)].sum3 = tr[lch(u)].sum2*tr[lch(u)].lazy3%mod;

            tr[rch(u)].sum1 = len_r*tr[rch(u)].lazy3%mod;
            tr[rch(u)].sum2 = tr[rch(u)].sum1*tr[rch(u)].lazy3%mod;
            tr[rch(u)].sum3 = tr[rch(u)].sum2*tr[rch(u)].lazy3%mod;
            tr[u].lazy3 = 0;
        }

        if (tr[u].lazy1 !=0 || tr[u].lazy2 != 1){
            tr[lch(u)].lazy1 = (tr[u].lazy2*tr[lch(u)].lazy1%mod + tr[u].lazy1)%mod;
            tr[lch(u)].lazy2 = tr[lch(u)].lazy2*tr[u].lazy2%mod;

            int s1,s2,s3;
            s1 = (tr[lch(u)].sum1*tr[u].lazy2%mod + len_l*tr[u].lazy1%mod)%mod;
            s2 = (tr[u].lazy2*tr[u].lazy2%mod*tr[lch(u)].sum2%mod +2*tr[u].lazy1*tr[u].lazy2%mod*tr[lch(u)].sum1%mod
                  +len_l*tr[u].lazy1%mod*tr[u].lazy1%mod)%mod;
            s3 = tr[u].lazy2*tr[u].lazy2%mod*tr[u].lazy2%mod*tr[lch(u)].sum3%mod;
            s3 = (s3+3*tr[u].lazy2%mod*tr[u].lazy2%mod*tr[u].lazy1%mod*tr[lch(u)].sum2%mod)%mod;
            s3 = (s3+3*tr[u].lazy2%mod*tr[u].lazy1%mod*tr[u].lazy1%mod*tr[lch(u)].sum1%mod)%mod;
            s3 = (s3+len_l*tr[u].lazy1%mod*tr[u].lazy1%mod*tr[u].lazy1%mod)%mod;
            tr[lch(u)].sum1 = s1;
            tr[lch(u)].sum2 = s2;
            tr[lch(u)].sum3 = s3;

            tr[rch(u)].lazy1 = (tr[u].lazy2*tr[rch(u)].lazy1%mod + tr[u].lazy1)%mod;
            tr[rch(u)].lazy2 = tr[rch(u)].lazy2*tr[u].lazy2%mod;

            s1 = (tr[rch(u)].sum1*tr[u].lazy2%mod + len_r*tr[u].lazy1%mod)%mod;
            s2 = (tr[u].lazy2*tr[u].lazy2%mod*tr[rch(u)].sum2%mod +2*tr[u].lazy1*tr[u].lazy2%mod*tr[rch(u)].sum1%mod
                  +len_r*tr[u].lazy1%mod*tr[u].lazy1%mod)%mod;
            s3 = tr[u].lazy2*tr[u].lazy2%mod*tr[u].lazy2%mod*tr[rch(u)].sum3%mod;
            s3 = (s3+3*tr[u].lazy2%mod*tr[u].lazy2%mod*tr[u].lazy1%mod*tr[rch(u)].sum2%mod)%mod;
            s3 = (s3+3*tr[u].lazy2%mod*tr[u].lazy1%mod*tr[u].lazy1%mod*tr[rch(u)].sum1%mod)%mod;
            s3 = (s3+len_r*tr[u].lazy1%mod*tr[u].lazy1%mod*tr[u].lazy1%mod)%mod;
            tr[rch(u)].sum1 = s1;
            tr[rch(u)].sum2 = s2;
            tr[rch(u)].sum3 = s3;

            tr[u].lazy1 = 0;
            tr[u].lazy2 = 1;
        }
    }

    void build(int u,int a,int b){
        tr[u].l = a;
        tr[u].r = b;
        tr[u].sum1 = tr[u].sum2 = tr[u].sum3 = 0;
        tr[u].lazy1 = tr[u].lazy3 = 0;
        tr[u].lazy2 = 1;

        if (a == b) return ;
        int mid = Mid;
        build(lch(u),a,mid);
        build(rch(u),mid+1,b);
    }


    void update(int u, int a, int b,int type,int val){
        if (tr[u].l == a && tr[u].r == b) {
             val %= mod;
             int len = Length(u);

             if (type == 1){
                 tr[u].lazy1 += val;
                 tr[u].lazy1 %= mod;
                 tr[u].sum3 = (tr[u].sum3 + 3*tr[u].sum2%mod*val%mod +
                               3*tr[u].sum1%mod*val%mod*val%mod + len*val%mod*val%mod*val%mod)%mod;
                 tr[u].sum2 = (tr[u].sum2 + 2*tr[u].sum1%mod*val%mod +
                               len*val%mod*val%mod)%mod;
                 tr[u].sum1 = (tr[u].sum1 + len*val%mod)%mod;
             }
             else if (type == 2){
                  tr[u].lazy1 = tr[u].lazy1*val%mod;
                  tr[u].lazy2 = tr[u].lazy2*val%mod;
                  tr[u].sum1 = tr[u].sum1*val%mod;
                  tr[u].sum2 = tr[u].sum2*val%mod*val%mod;
                  tr[u].sum3 = tr[u].sum3*val%mod*val%mod*val%mod;
             }
             else {
                 tr[u].lazy1 = 0;
                 tr[u].lazy2 = 1;
                 tr[u].lazy3 = val%mod;
                 tr[u].sum1 = len*val%mod;
                 tr[u].sum2 = tr[u].sum1*val%mod;
                 tr[u].sum3 = tr[u].sum2*val%mod;
             }
             return;
        }

        push_down(u);
        int mid = Mid;
        if (b<=mid) update(lch(u),a,b,type,val);
        else if (a>mid) update(rch(u),a,b,type,val);
        else {
            update(lch(u),a,mid,type,val);
            update(rch(u),mid+1,b,type,val);
        }
        push_up(u);
    }

    int query(int u, int a, int b,int type) {
        if (tr[u].l == a && tr[u].r == b) {
            if (type == 1) return tr[u].sum1;
            if (type == 2) return tr[u].sum2;
            return tr[u].sum3;
        }
        push_down(u);
        int mid = Mid;
        if (b<=mid) return query(lch(u),a,b,type);
        else if (a>mid) return query(rch(u),a,b,type);
        else return (query(lch(u),a,mid,type)+query(rch(u),mid+1,b,type))%mod;
    }
}T;

int n,m;

int main(){
    while (scanf("%d %d",&n,&m)==2) {
        if (n == 0 && m == 0) break;
        T.build(1,1,n);

        int k,a,b,c;
        while(m--){
            scanf("%d %d %d %d",&k,&a,&b,&c);
            if (k == 4) printf("%d\n",T.query(1,a,b,c));
            else T.update(1,a,b,k,c);
        }
    }
    return 0;
}
