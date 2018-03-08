#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

const int INF = 1e9;
const int maxn = 10000+10;
int n,m,k;
struct Edge{
   int x,y;
   Edge(int x=0, int y=0):x(x),y(y){}
}e[maxn];
int x,y;
bool flag;
int s,t;

queue<int>que;
int d[maxn];
bool inq[maxn];

void spfa(){
    memset(inq,0,sizeof(inq));
    while (!que.empty()) que.pop();
    for (int i=1; i<=k; i++) d[i] = INF;
    que.push(s);
    d[s] = 0;
    inq[s] = 1;

    int dx,dy;
    int val;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        inq[u] = 0;
        for (int i=1; i<=k; i++) if (i!=u) {
            dx = abs(e[u].x-e[i].x);
            dy = abs(e[u].y-e[i].y);
            if (dx+dy==1) val = 0;
            else if (dx<=2 || dy<=2) val = 1;
            else val = INF;

            if (val<=1 && d[i]>d[u]+val) {
                 d[i] = d[u]+val;
                 if (!inq[i]) inq[i] = 1, que.push(i);
            }
        }
    }
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    flag = 0;
    for (int i=1; i<=k; i++) {
        scanf("%d%d",&x,&y);
        e[i] = Edge(x,y);
        if (x==1 && y==1) s = i;
        if (x==n && y==m) { flag = 1; t = i; }
    }
    if (!flag) {
        k++;
        e[k] = Edge(n+1,m+1);
        t = k;
    }

    spfa();
    if (d[t]<INF) printf("%d\n",d[t]);
    else printf("-1\n");
    return 0;
}
