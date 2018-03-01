#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1<<30;
const int maxn = 1500+5;
vector<int>G[maxn];
int dx[maxn],dy[maxn];
int mx[maxn],my[maxn];
bool vis[maxn];
int ans,dis,n;

bool BFS(){
   queue<int>que;
   dis = INF;
   memset(dx,-1,sizeof(dx));
   memset(dy,-1,sizeof(dy));
   for (int i=1; i<=n; i++) {
       if (mx[i]==-1) {
         que.push(i);
         dx[i] = 0;
       }
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
        if (!vis[v] && dy[v]==dx[u]+1){
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
        for (int i=1; i<=n; i++)
            if (mx[i]==-1 && DFS(i)) ans++;
    }
    return ans;
}

int main(){
    while (scanf("%d",&n)==1) {
       for (int i=1; i<=n; i++) G[i].clear();

       int x,y,num;
       for (int i=1; i<=n; i++) {
          scanf("%d:(%d)",&x,&num);
          x++;
          while (num--){
             scanf("%d",&y);
             G[x].push_back(y+1);
             G[y+1].push_back(x);
          }
       }

       ans = HK();
       printf("%d\n",ans/2);

    }
    return 0;
}
