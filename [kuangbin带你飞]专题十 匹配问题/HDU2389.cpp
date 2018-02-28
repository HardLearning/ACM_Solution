#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;

struct Point{
   double x,y;
   Point (double x=0, double y=0):x(x),y(y){}
};

typedef Point Vector;
Vector operator -(Vector A,Vector B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator +(Vector A,Vector B) { return Vector(A.x+B.x,A.y+B.y); }
double Dot(Vector A,Vector B) {return A.x*B.x+A.y*B.y;}
double Length(Vector A) {return sqrt(Dot(A,A)); }

const int INF = 1e9;
const int maxn = 3000+5;
Point guest[maxn];
double s[maxn];
double t;
int n,m;

vector<int>G[maxn];
int mx[maxn],my[maxn];
int dx[maxn],dy[maxn];
bool vis[maxn];
int dis;

bool BFS(){
   queue<int>que;
   dis = INF;
   memset(dx,-1,sizeof(dx));
   memset(dy,-1,sizeof(dy));
   for (int i=1; i<=m; i++)
     if (mx[i]==-1) {
         que.push(i);
         dx[i] = 0;
     }

   int u,v;
   while (!que.empty()){
       u = que.front();
       que.pop();
       if (dx[u]>dis) break;

       for (int i=0; i<G[u].size(); i++) {
            v = G[u][i];
            if (dy[v]==-1) {
                dy[v] = dx[u]+1;
                if (my[v]==-1) dis = dy[v];
                else {
                  dx[my[v]] = dy[v]+1;
                  que.push(my[v]);
                }
            }
       }
   }
   return dis!=INF;
}

bool DFS(int u){
    int v;
    for (int i=0; i<G[u].size(); i++) {
        v = G[u][i];
        if (!vis[v] && dy[v]==dx[u]+1) {
            vis[v] = 1;
            if (my[v]!=-1 && dy[v]==dis) continue;
            if (my[v]==-1 || DFS(my[v])) {
                my[v] = u;
                mx[u] = v;
                return 1;
            }
        }
    }
    return 0;
}

int HK(){
    int ans = 0;
    memset(mx,-1,sizeof(mx));
    memset(my,-1,sizeof(my));
    while (BFS()){
        memset(vis,0,sizeof(vis));
        for (int i=1; i<=m; i++)
            if (mx[i]==-1 && DFS(i)) ans++;
    }
    return ans;
}

int main(){
    int T;
    scanf("%d",&T);

    int kase = 0;
    while (T--){
       scanf("%lf",&t);
       scanf("%d",&m);

       double x,y;
       Point umbrella;
       for (int i=1; i<=m; i++) {
           scanf("%lf%lf%lf",&x,&y,&s[i]);
           guest[i] = Point(x,y);
           G[i].clear();
       }

       scanf("%d",&n);
       for (int i=1; i<=n; i++) {
          scanf("%lf%lf",&x,&y);
          umbrella = Point(x,y);
          for (int j=1; j<=m; j++) if (Length(guest[j]-umbrella)<=t*s[i]) G[j].push_back(i);
       }

       int ans = HK();
       printf("Scenario #%d:\n",++kase);
       printf("%d\n\n",ans);

    }
    return 0;
}
