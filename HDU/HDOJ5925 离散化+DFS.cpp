#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

const int maxn = 200+5;
typedef long long LL;
int R,C,n;
int xx,yy;
map<pair<int,int>,int>vis;
int x[maxn*3],totx;
int y[maxn*3],toty;

int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
LL sum;
vector<LL>solve;

struct node{
    LL val;
    bool flag;
}mark[maxn][maxn];

void dfs(int x, int y) {
    mark[x][y].flag = 1;
    sum += mark[x][y].val;

    int tx,ty;
    for (int i=0; i<4; i++) {
        tx = x+dx[i];
        ty = y+dy[i];
        if (tx<0 || tx>=totx || ty<0 || ty>=toty) continue;
        if (mark[tx][ty].flag==1) continue;
        dfs(tx,ty);
    }
}

int main(){
    int T;
    scanf("%d",&T);

    int kase = 0;
    while (T--){
        solve.clear();
        vis.clear();
        totx = toty = 0;
        scanf("%d%d%d",&R,&C,&n);

        x[totx++] = R;
        y[toty++] = C;
        for (int i=1; i<=n; i++) {
            scanf("%d%d",&xx,&yy);
            vis[make_pair(xx,yy)] = 1;
            x[totx++] = xx;
            y[toty++] = yy;
            if (xx>1) x[totx++] = xx-1;
            if (xx<R) x[totx++] = xx+1;
            if (yy>1) y[toty++] = yy-1;
            if (yy<C) y[toty++] = yy+1;
        }
        sort(x,x+totx); totx = unique(x,x+totx)-x;
        sort(y,y+toty); toty = unique(y,y+toty)-y;

        int u,v;
        for (int i=0; i<totx; i++) {
            for (int j=0; j<toty; j++) {
                 if (i==0) u = 1; else u = x[i-1]+1;
                 if (j==0) v = 1; else v = y[j-1]+1;
                 mark[i][j].val = 1LL*(x[i]-u+1)*(y[j]-v+1);
                 if (vis[make_pair(x[i],y[j])]) mark[i][j].flag = 1;
                 else mark[i][j].flag = 0;
            }
        }

        for (int i=0; i<totx; i++) {
            for (int j=0; j<toty; j++) if (mark[i][j].flag==0) {
                sum = 0;
                dfs(i,j);
                solve.push_back(sum);
            }
        }

        printf("Case #%d:\n",++kase);
        printf("%d\n",solve.size());
        sort(solve.begin(),solve.end());
        printf("%I64d",solve[0]);
        for (int i=1; i<solve.size(); i++) printf(" %I64d",solve[i]);
        printf("\n");
    }
    return 0;
}
