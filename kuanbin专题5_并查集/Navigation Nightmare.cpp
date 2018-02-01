#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxk = 10000+10;
const int maxn = 40000+10;
int n,m,K;
int fa[maxn];
int f1[maxn],f2[maxn],L[maxn];
char D[maxn][5];
int dx[maxn],dy[maxn];
int ans[maxk];

struct node{
    int x,y;
    int idx;
    int I;
    bool operator <(const node &rhs) const {
         return I<rhs.I;
    }
}q[maxk];

int Find(int x){
    if (fa[x] == -1) return x;
    int tmp = Find(fa[x]);
    dy[x] += dy[fa[x]];
    dx[x] += dx[fa[x]];
    return fa[x] = tmp;
}

int main(){
    while (scanf("%d %d",&n,&m)==2){
        for (int i=1; i<=m; i++) scanf("%d %d %d %s",&f1[i],&f2[i],&L[i],D[i]);
        scanf("%d",&K);
        for (int i=1; i<=K; i++) scanf("%d %d %d",&q[i].x,&q[i].y,&q[i].I),q[i].idx = i;
        sort(q+1,q+K+1);
        memset(fa,-1,sizeof(fa));
        memset(dx,0,sizeof(dx));
        memset(dy,0,sizeof(dy));

        int pt = 1;
        int ra,rb;
        int a,b;
        for (int i=1; i<=K; i++) {
           while (pt<=m && q[i].I>=pt){
                a = f1[pt]; b = f2[pt];
                ra = Find(a); rb = Find(b);
                if (ra!=rb){
                    fa[rb] = ra;
                    if (D[pt][0]=='N') {
                        dy[rb] = dy[a] - dy[b] + L[pt];
                        dx[rb] = dx[a] - dx[b];
                    }
                    else if (D[pt][0]=='S') {
                        dy[rb] = dy[a] - dy[b] - L[pt];
                        dx[rb] = dx[a] - dx[b];
                    }
                    else if (D[pt][0]=='E') {
                        dx[rb] = dx[a] - dx[b] + L[pt];
                        dy[rb] = dy[a] - dy[b];
                    }
                    else {
                        dx[rb] = dx[a] - dx[b] - L[pt];
                        dy[rb] = dy[a] - dy[b];
                    }
                }
                pt++;
           }

           if (Find(q[i].x) != Find(q[i].y)) ans[q[i].idx] = -1;
           else ans[q[i].idx] = abs(dx[q[i].x]-dx[q[i].y]) + abs(dy[q[i].x]-dy[q[i].y]);
        }

        for (int i=1; i<=K; i++) printf("%d\n",ans[i]);
    }
    return 0;
}
