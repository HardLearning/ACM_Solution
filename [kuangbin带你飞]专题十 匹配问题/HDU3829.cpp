#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 500+5;
int n,m,p;
vector<int>G[maxn];
bool vis[maxn];
int cy[maxn];

int DFS(int u){
   int v;
   for (int i=0; i<G[u].size(); i++) {
      v = G[u][i];
      if (vis[v]) continue;
      vis[v] = 1;
      if (cy[v]==-1 || DFS(cy[v])) {
          cy[v] = u;
          return 1;
      }
   }
   return 0;
}

int KM(){
   int ans = 0;
   memset(cy,-1,sizeof(cy));
   for (int i=1; i<=p; i++) {
      memset(vis,0,sizeof(vis));
      ans += DFS(i);
   }
   return ans;
}

char s1[maxn][10],s2[maxn][10];

int main(){
    while (scanf("%d%d%d",&n,&m,&p)==3){
        for (int i=1; i<=p; i++) G[i].clear();
        for (int i=1; i<=p; i++) scanf("%s%s",s1[i],s2[i]);
        for (int i=1; i<=p; i++)
          for (int j=1; j<=p; j++) {
              if (strcmp(s1[i],s2[j])==0 ||strcmp(s2[i],s1[j])==0) G[i].push_back(j);
          }

        int ans = KM();
        printf("%d\n",p-ans/2);
    }
    return 0;
}
