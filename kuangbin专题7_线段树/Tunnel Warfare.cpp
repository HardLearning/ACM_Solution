#include <cstdio>
using namespace std;

const int maxn = 50000+5;
int n,m;
struct node{
   int left,right;
   int lenL,lenR,len;
};
struct Tree{
    node tr[maxn*4];
    #define lch(u) (u<<1)
    #define rch(u) (u<<1|1)
    #define Mid (tr[u].left+tr[u].right)>>1

    inline int Max(int x, int y) { return x>y?x:y; }

    void build(int u,int a, int b){
        tr[u].left = a; tr[u].right = b;
        tr[u].lenL = tr[u].lenR = tr[u].len = b-a+1;
        if (a == b) return;
        int mid = Mid;
        build(lch(u),a,mid);
        build(rch(u),mid+1,b);
    }

    void update(int u, int pos, int val) {
        if (tr[u].left == tr[u].right) {
            if (val==1) tr[u].lenL = tr[u].lenR = tr[u].len = 1;
            else tr[u].lenL = tr[u].lenR = tr[u].len = 0;
            return ;
        }

        int mid = Mid;
        if (pos<=mid) update(lch(u),pos,val);
        else update(rch(u),pos,val);

        tr[u].lenL = tr[lch(u)].lenL;
        tr[u].lenR = tr[rch(u)].lenR;
        tr[u].len = Max(tr[lch(u)].len,tr[rch(u)].len);
        tr[u].len = Max(tr[u].len,tr[lch(u)].lenR+tr[rch(u)].lenL);

        if (tr[lch(u)].lenL == tr[lch(u)].right - tr[lch(u)].left+1) tr[u].lenL += tr[rch(u)].lenL;
        if (tr[rch(u)].lenR == tr[rch(u)].right - tr[rch(u)].left+1) tr[u].lenR += tr[lch(u)].lenR;
    }

    int query(int u, int x){
       if (tr[u].left == tr[u].right || tr[u].len == 0 || tr[u].len == tr[u].right-tr[u].left+1)
         return tr[u].len;

       int mid = Mid;
       if (x<=mid) {
          if (x>=tr[lch(u)].right-tr[lch(u)].lenR+1)
            return query(lch(u),x) + query(rch(u),mid+1);
          else return query(lch(u),x);
       }
       else {
          if (x<=tr[rch(u)].left+tr[rch(u)].lenL-1)
            return query(rch(u),x) + query(lch(u),mid);
          else return query(rch(u),x);
       }

    }
}T;

char str[10];
int que[maxn],top;
int main(){
    while (scanf("%d %d",&n,&m)==2){
        T.build(1,1,n);
        top = 0;

        int x=-1;
        while (m--) {
            scanf("%s",str);
            if (str[0]=='D') {
                scanf("%d",&x);
                que[top++] = x;
                T.update(1,x,0);
            }
            else if (str[0]=='R') {
                if (x>0) {
                    x=que[--top];
                    T.update(1,x,1);
                }
            }
            else {
                scanf("%d",&x);
                printf("%d\n",T.query(1,x));
            }
        }
    }
    return 0;
}
