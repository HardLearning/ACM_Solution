#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 1000+5;
struct TwoSAT{
   int n;
   int S[maxn*2],c;
   bool mark[maxn*2];
   vector<int> G[maxn*2];

   void init(int n) {
      this-> n = n;
      memset(mark,0,sizeof(mark));
      for (int i=0; i<n*2; i++) G[i].clear();
   }

   void add(int x, int xval, int y, int yval) {
      x = x*2 + xval;
      y = y*2 + yval;
      G[x].push_back(y);
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
       for (int i=0; i<n*2; i+=2) {
          if (!mark[i] && !mark[i+1]) {
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
int n,m;
int a,b,c;
char s[5];

int main(){
    while (scanf("%d%d",&n,&m)==2) {
        solver.init(n);
        while (m--) {
            scanf("%d%d%d%s",&a,&b,&c,s);
            if (s[0]=='A') {
               if (c == 1) solver.add(a,0,a,1),solver.add(b,0,b,1);
               else solver.add(a,1,b,0),solver.add(b,1,a,0);
            }
            else if (s[0]=='O') {
                  if (c == 1) solver.add(a,0,b,1),solver.add(b,0,a,1);
                  else solver.add(a,1,a,0),solver.add(b,1,b,0);
            }
            else {
                  if (c == 1) solver.add(a,1,b,0),solver.add(a,0,b,1),solver.add(b,1,a,0),solver.add(b,0,a,1);
                  else solver.add(a,0,b,0),solver.add(a,1,b,1),solver.add(b,0,a,0),solver.add(b,1,a,1);
            }
        }

        if (solver.solve()) printf("YES\n"); else printf("NO\n");
    }
    return 0;
}
