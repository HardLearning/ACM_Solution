#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

typedef long long LL;
const int maxn = 2e5+10;
LL a[maxn];
int n,m;

struct Edge{
   int from,to;
   LL dist;
};

struct HeapNode{
   LL d;
   int u;
   bool operator <(const HeapNode &rhs) const{
       return d>rhs.d;
   }
};

struct Dijkstra{
     int n,m;
     vector<Edge>edges;
     vector<int>G[maxn];
     bool done[maxn];
     LL d[maxn];
     #define pb push_back

     void init(int n){
        this->n = n;
        for (int i=1; i<=n; i++) G[i].clear();
        edges.clear();
     }

     void addEdge(int from, int to, LL dist){
        edges.pb((Edge){from,to,dist});
        edges.pb((Edge){to,from,dist});
        m = edges.size();
        G[from].pb(m-2);
        G[to].pb(m-1);
     }

     void dijkstra(){
        priority_queue<HeapNode>que;
        for (int i=1; i<=n; i++) d[i] = a[i];
        memset(done,0,sizeof(done));
        for (int i=1; i<=n; i++) que.push((HeapNode){a[i],i});

        HeapNode x;
        while (!que.empty()){
            x = que.top();
            que.pop();
            int u = x.u;
            if (done[u]) continue;
            done[u] = 1;
            for (int i=0; i<G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if (d[e.to]>d[u]+e.dist){
                    d[e.to] = d[u] + e.dist;
                    que.push((HeapNode){d[e.to],e.to});
                }
            }
        }

        for (int i=1; i<n; i++) printf("%I64d ",d[i]);
        printf("%I64d\n",d[n]);
     }
}D;

int main(){
    while (scanf("%d%d",&n,&m)==2){
         D.init(n);

         int u,v;
         LL w;
         while (m--){
            scanf("%d%d%I64d",&u,&v,&w);
            D.addEdge(u,v,w*2);
         }
         for (int i=1; i<=n; i++) scanf("%I64d",&a[i]);

         D.dijkstra();
    }
    return 0;
}
