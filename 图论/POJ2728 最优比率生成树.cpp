#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const double INF = 1e9;
const double eps = 1e-8;
const int maxn = 1000+10;
double len[maxn][maxn],cost[maxn][maxn],f[maxn][maxn];
double x[maxn],y[maxn],z[maxn];
bool vis[maxn];
double dis[maxn];
int p[maxn];
int n;

double sum,cx,dx;
void Prim(double L){
    sum = cx = dx = 0;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) f[i][j] = cost[i][j] - len[i][j]*L;
    }
    for (int i=1; i<=n; i++) dis[i] = INF, vis[i] = 0;
    int  now = 1;
    dis[now] = 0; p[now] = now;

    for (int cnt = 1; cnt<=n; cnt++) {
        cx += cost[p[now]][now];
        dx += len[p[now]][now];
        vis[now] = 1;
        sum += dis[now];

        for (int i=1; i<=n; i++) if (!vis[i] && dis[i]>f[now][i]) {
            dis[i] = f[now][i];
            p[i] = now;
        }

        double minn = INF;
        for (int i=1; i<=n; i++) if (!vis[i] && dis[i]<minn) {
            minn = dis[i];
            now = i;
        }
    }
}

int main(){
    while (scanf("%d",&n)==1 && n) {
        for (int i=1; i<=n; i++) scanf("%lf%lf%lf",&x[i],&y[i],&z[i]);

        double maxx = -INF;
        for (int i=1; i<=n; i++) {
            for (int j=i; j<=n; j++) {
                cost[i][j] = cost[j][i] = fabs(z[i]-z[j]);
                maxx = max(maxx,cost[i][j]);
                len[i][j] = len[j][i] = sqrt( (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]) );
            }
        }

        double L = maxx*n;
        Prim(L);
        while (fabs(sum)>eps) {
            L = cx/dx;
            Prim(L);
        }

        printf("%.3f\n",L);
    }
    return 0;
}
