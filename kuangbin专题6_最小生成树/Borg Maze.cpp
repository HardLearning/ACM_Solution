#include <stdio.h>
#include <cstring>
#include <queue>
using namespace std;

const int INF  =1e9;
const int maxn = 100+5;
char g[maxn][maxn];
int w[maxn][maxn]; // cost
int n,m,num_p;
int num[maxn][maxn];

struct node{
   int x,y,step;
}p,q;
bool vis[maxn][maxn];
int dx[]={-1,0,1,0};
int dy[]={0,-1,0,1};
queue<node>que;

void BFS(int sx, int sy){
    memset(vis,0,sizeof(vis));
    while (!que.empty()) que.pop();
    que.push((node){sx,sy,0});
    vis[sx][sy] = 1;

    while (!que.empty()){
        p = que.front();
        que.pop();
        if (g[p.x][p.y]=='A' || g[p.x][p.y]=='S') {
              w[num[sx][sy]][num[p.x][p.y]] = p.step;
              w[num[p.x][p.y]][num[sx][sy]] = p.step;
        }
        for (int i=0; i<4; i++) {
            q.x = p.x+dx[i];
            q.y = p.y+dy[i];
            if (q.x<0 || q.y<0 || q.x>=m || q.y>=n) continue;
            if (vis[q.x][q.y] || g[q.x][q.y]=='#') continue;
            vis[q.x][q.y] = 1;
            q.step = p.step+1;
            que.push(q);
        }
    }
}

inline int Min(int x, int y) { return x<y?x:y; }
int dis[maxn];
bool v[maxn];
void Prim(){
    memset(v,0,sizeof(v));
    int ans = 0;
    for (int i=0; i<num_p; i++) dis[i] = w[0][i];
    for (int i=1; i<num_p; i++) {
        int d = INF;
        int tmp = -1;
        for (int i=1; i<num_p; i++) if (!v[i] && dis[i]<d) {
            d = dis[i];
            tmp = i;
        }
        ans += d;
        v[tmp] = 1;
        for (int i=0; i<num_p; i++) dis[i] = Min(dis[i],w[tmp][i]);
    }
    printf("%d\n",ans);
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--){
        num_p = 0;
        memset(num,-1,sizeof(num));

        scanf("%d %d",&n,&m);
        gets(g[0]);
        for (int i=0; i<m; i++) {
            gets(g[i]);
            for (int j=0; j<n; j++) if (g[i][j]=='A' || g[i][j]=='S') {
                num[i][j] = num_p;
                num_p++;
            }
        }

        for (int i=0; i<m; i++){
            for (int j=0; j<n; j++) if (num[i][j]!=-1) BFS(i,j);
        }

        Prim();
    }
    return 0;
}
