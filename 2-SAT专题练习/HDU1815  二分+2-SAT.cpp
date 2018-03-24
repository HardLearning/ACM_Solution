#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

const int INF = 1e7;
const int maxn = 510;
const int maxm = 1000+10;
struct TwoSAT{
   int n;
   int S[maxn*2],c;
   bool mark[maxn*2];
   vector<int> G[maxn*2];

   void init(int n) {
      this->n = n;
      memset(mark,0,sizeof(mark));
      for (int i=0; i<n*2; i++) G[i].clear();
   }

   void add(int x, int xval, int y, int yval) {
        x = x*2 + xval;
        y = y*2 + yval;
        G[x^1].push_back(y);
        G[y^1].push_back(x);
   }

   bool dfs(int x) {
      if (mark[x^1]) return 0;
      if (mark[x]) return 1;
      mark[x] = 1;
      S[c++] = x;

      for (int i=0; i<G[x].size(); i++)
        if (!dfs(G[x][i])) return 0;
      return 1;
   }

   bool solve() {
      for (int i=0; i<n*2; i+=2)
         if (!mark[i] && !mark[i+1]) {
            c = 0;
            if (!dfs(i)) {
                while (c>0) mark[S[--c]] = 0;
                if (!dfs(i+1)) return 0;
            }
       }
      return 1;
   }

}solver;

int n,A,B;
struct Point {
   int x,y;
};
Point s1,s2;
Point p[maxn];

struct Edge{
   int u,v;
   Edge (int u=0, int v=0): u(u), v(v) {}
};
Edge hate[maxm],like[maxm];

int d1[maxn],d2[maxn],Len;
inline int Length(Point a, Point b) {
   return abs(a.x-b.x) + abs(a.y-b.y);
}

void build(int mid){
   for (int i=0; i<A; i++) solver.add(hate[i].u,0,hate[i].v,0), solver.add(hate[i].u,1,hate[i].v,1);
   for (int i=0; i<B; i++) solver.add(like[i].u,1,like[i].v,0), solver.add(like[i].u,0,like[i].v,1);
   for (int i=0; i<n; i++) {
      for (int j=i+1; j<n; j++) {
          if (d1[i]+d1[j]>mid) solver.G[i*2].push_back(j*2+1), solver.G[j*2].push_back(i*2+1);
          if (d2[i]+d2[j]>mid) solver.G[i*2+1].push_back(j*2), solver.G[j*2+1].push_back(i*2);
          if (d1[i]+Len+d2[j]>mid) solver.G[i*2].push_back(j*2), solver.G[j*2+1].push_back(i*2+1);
          if (d2[i]+Len+d1[j]>mid) solver.G[i*2+1].push_back(j*2+1), solver.G[j*2].push_back(i*2);
      }
   }
}

int main(){
    while (scanf("%d%d%d",&n,&A,&B)==3) {
        scanf("%d%d%d%d",&s1.x,&s1.y,&s2.x,&s2.y);
        Len = Length(s1,s2);
        for (int i=0; i<n; i++) scanf("%d%d",&p[i].x,&p[i].y);
        for (int i=0; i<n; i++) d1[i] = Length(p[i],s1), d2[i] = Length(p[i],s2);
        int u,v;
        for (int i=0; i<A; i++) {
            scanf("%d%d",&u,&v);
            u--; v--;
            hate[i] = Edge(u,v);
        }
        for (int i=0; i<B; i++) {
            scanf("%d%d",&u,&v);
            u--; v--;
            like[i] = Edge(u,v);
        }

        int left = 0, right = INF;
        int mid, ans = -1;
        while (left<=right) {
            mid = (left+right)>>1;
            solver.init(n);
            build(mid);
            if (solver.solve()) {right = mid-1; ans = mid;}
            else left = mid+1;
        }

        printf("%d\n",ans);
    }
    return 0;
}
