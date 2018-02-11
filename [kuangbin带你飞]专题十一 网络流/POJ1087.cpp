#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

const int INF = 1e8;
const int maxn = 600;
const int maxm = 200+5;

struct Edge{
   int from,to,cap,flow;
};

struct Dicnic{
   int m,s,t;
   vector<Edge>edges;
   vector<int>G[maxn];
   int d[maxn];
   int cur[maxn];
   bool vis[maxn];
   #define pb push_back

   void init(int N, int M){
      s = 0; t = N+M+1;
      edges.clear();
      for (int i=s; i<=t; i++) G[i].clear();
   }

   void addEdge(int from, int to, int cap){
      edges.pb((Edge){from,to,cap,0});
      edges.pb((Edge){to,from,0,0});
      m = edges.size();
      G[from].pb(m-2);
      G[to].pb(m-1);
   }

   bool BFS(){
      memset(vis,0,sizeof(vis));
      d[s] = 0;
      vis[s] = 1;
      queue<int>que;
      que.push(s);

      int x;
      while (!que.empty()){
         x = que.front();
         que.pop();
         for (int i=0; i<G[x].size(); i++) {
            Edge &e = edges[G[x][i]];
            if (!vis[e.to] && e.cap > e.flow){
                vis[e.to] = 1;
                d[e.to] = d[x] + 1;
                que.push(e.to);
            }
         }
      }
      return vis[t];
   }

   int DFS(int x,int a){
      if (x==t || a==0) return a;
      int flow = 0,f;
      for (int &i = cur[x]; i<G[x].size(); i++){
         Edge& e  = edges[G[x][i]];
         if (d[e.to] == d[x]+1 && (f=DFS(e.to,min(a,e.cap-e.flow)))>0 ) {
             flow += f;
             a -= f;
             e.flow += f;
             edges[G[x][i]^1].flow -= f;
             if (a == 0) break;
         }
      }
      return flow;
   }

   int Maxflow(){
      int flow = 0;
      while (BFS()){
         memset(cur,0,sizeof(cur));
         flow += DFS(s,INF);
      }
      return flow;
   }
}dinic;

map<string,int>mp1,mp2;
int tot1,tot2;
int n,m,k;
string s1[maxm];
string s2[maxm][2];
string s3[maxm][2];

int main(){
    while (cin>>n){
       mp1.clear(); tot1 = 0;
       mp2.clear(); tot2 = 0;

       for (int i=1; i<=n; i++) { cin >> s1[i]; mp1[s1[i]] = ++tot1; }

       cin >> m;
       for (int i=1; i<=m; i++) {
            cin >> s2[i][0] >> s2[i][1];
            mp2[s2[i][0]] = ++tot2;
            if (!mp1[s2[i][1]]) mp1[s2[i][1]] = ++tot1;
       }

       cin >> k;
       for (int i=1; i<=k; i++) {
           cin >> s3[i][0] >> s3[i][1];
           if (!mp1[s3[i][0]]) mp1[s3[i][0]] = ++tot1;
           if (!mp1[s3[i][1]]) mp1[s3[i][1]] = ++tot1;
       }

       dinic.init(tot1,tot2);
       for (int i=1; i<=m; i++) {
            dinic.addEdge(dinic.s,mp2[s2[i][0]],1);
            dinic.addEdge(mp2[s2[i][0]],mp1[s2[i][1]]+tot2,1);
       }
       for (int i=1; i<=n; i++) dinic.addEdge(mp1[s1[i]]+tot2,dinic.t,1);
       for (int i=1; i<=k; i++) dinic.addEdge(mp1[s3[i][0]]+tot2,mp1[s3[i][1]]+tot2,INF);
       cout << m-dinic.Maxflow() << endl;
    }
    return 0;
}
