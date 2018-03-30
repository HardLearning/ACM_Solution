#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int maxn = 100+5;
struct TwoSAT{
    int S[maxn*2],c;
    bool mark[maxn*2];
    vector<int> G[maxn*2];
    int n;

    bool dfs(int x) {
       if (mark[x^1]) return 0;
       if (mark[x]) return 1;
       mark[x] = 1;
       S[c++] = x;

       for (int i=0; i<G[x].size(); i++)
          if (!dfs(G[x][i])) return 0;
       return 1;
    }

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



    bool solve() {
         for (int i=0; i<n*2; i+=2) {
            if (!mark[i] && !mark[i^1]) {
               c = 0;
               if (!dfs(i)) {
                  while (c>0) mark[S[--c]] = 0;
                  if (!dfs(i+1)) return 0;
               }
            }
         }
         return 1;
    }
};
TwoSAT solver;

int n;
struct Point{
   int x,y;
}p[maxn];

bool judge(int r) {
    solver.init(n);

    int up,down;
    for (int i=0; i<n; i++) {
        for (int j=0; j<i; j++) if (abs(p[i].x-p[j].x)<r){
              if (p[i].y > p[j].y) up = i, down = j;
              else up = j, down = i;
              if (p[up].y == p[down].y) {
                  solver.add(up,0,down,0);
                  solver.add(up,1,down,1);
                  continue;
              }

              if (p[up].y - p[down].y < 2*r) {
                  if (p[up].y - p[down].y < r) {
                      solver.add(up,0,up,0);
                      solver.add(down,1,down,1);
                  }
                  else {
                      solver.add(up,0,down,1);
                  }
              }
        }
    }

    return solver.solve();
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--) {
       scanf("%d",&n);
       for (int i=0; i<n; i++) scanf("%d%d",&p[i].x,&p[i].y);

       int left = 0, right = 10000;
       int mid , ans = 0;
       while (left<=right) {
          mid = (left+right)>>1;
          if (judge(mid)) left = mid+1, ans = mid;
          else right = mid-1;
       }
       printf("%d\n",ans);
    }
    return 0;
}
