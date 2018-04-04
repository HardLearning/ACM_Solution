#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int maxn = 40000+10;
const int maxp = 500000+10;
bool vis[maxp];
int prime[maxp],tot;

void get_prime(int n){
   memset(vis,1,sizeof(vis));
   for (int i=2; i<n; i++) if (vis[i]) {
      for (int j=i+i; j<n; j+=i) vis[j] = 0;
   }
   tot = 0;
   for (int i=2; i<500000; i++) if (vis[i]) prime[tot++] = i;
}

int n;
int a[maxn];
vector<int> G[maxn];
vector<int> val[maxn];
int p[maxp][2];

const int INF = 1e9;
int mx[maxn],my[maxn];
int dx[maxn],dy[maxn];
int dis;
bool used[maxn];

bool BFS(){
   queue<int>que;
   dis = INF;
   memset(dx,-1,sizeof(dx));
   memset(dy,-1,sizeof(dy));
   for (int i=0; i<n; i++) {
      if (mx[i] == -1) que.push(i),dx[i] = 0;
   }

   int u,v;
   while (!que.empty()) {
      u = que.front();
      que.pop();
      if (dx[u]>dis) break;

      for (int i=0; i<G[u].size(); i++) {
          v = G[u][i];
          if (dy[v] == -1) {
              dy[v] = dx[u] + 1;
              if (my[v] == -1) dis = dy[v];
              else dx[my[v]] = dy[v] + 1, que.push(my[v]);
          }
      }
   }
   return dis < INF;
}

bool DFS(int u) {
   int v;
   for (int i=0; i<G[u].size(); i++) {
      v = G[u][i];
      if (!vis[v] && dy[v] == dx[u] + 1) {
          vis[v] = 1;
          if (my[v] != -1 && dy[v] == dis) continue;
          if (my[v] == - 1 || DFS(my[v])) {
             my[v] = u;
             mx[u] = v;
             return 1;
          }
      }
   }
   return 0;
}

int MaxMatch() {
    int ans = 0;
    memset(mx,-1,sizeof(mx));
    memset(my,-1,sizeof(my));
    while (BFS()) {
        memset(vis,0,sizeof(vis));
        for (int i=0; i<n; i++) if (mx[i]==-1 && DFS(i)) ans++;
    }
    return ans;
}

int main(){
    get_prime(maxp);
    int T;
    scanf("%d",&T);

    int kase = 0;
    while (T--) {
        scanf("%d",&n);
        for (int i=0; i<=n; i++) G[i].clear();
        for (int i=0; i<=n; i++) val[i].clear();
        memset(p,-1,sizeof(p));

        for (int i=0; i<n; i++) {
            scanf("%d",&a[i]);
            int t = a[i], cnt = 0;
            for (int j=0; prime[j]*prime[j]<=t; j++) {
                if (t%prime[j]==0) {
                    val[i].push_back(prime[j]);
                    while (t%prime[j]==0) cnt++, t/=prime[j];
                }
            }
            if (t>1) cnt++, val[i].push_back(t);
            p[a[i]][cnt&1] = i;
        }

        for (int i=0; i<n; i++) {
            if (p[a[i]][0]!=-1) {
                for (int j=0; j<val[i].size(); j++) {
                    int t = a[i]/val[i][j];
                    if (p[t][1]!=-1) G[i].push_back(p[t][1]);
                }
            }
            else {
                for (int j=0; j<val[i].size(); j++) {
                    int t = a[i]/val[i][j];
                    if (p[t][0]!=-1) G[p[t][0]].push_back(i);
                }
            }
        }

        int ans = MaxMatch();
        printf("Case %d: %d\n",++kase,n-ans);
    }
    return 0;
}
