#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 500+5;
struct TwoSAT{
   int n;
   bool mark[maxn*2];
   int S[maxn*2],c;
   vector<int> G[maxn*2];

   void init(int n) {
       this->n = n;
       memset(mark,0,sizeof(mark));
       for (int i=0; i<n*2; i++) G[i].clear();
   }

   void add(int x, int xval, int y, int yval) {
       x = x*2 + xval; y = y*2 + yval;
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
int n;
int mat[maxn][maxn];

inline bool judge(){
   for (int i=0; i<n; i++) {
       if (mat[i][i]!=0) return 0;
       for (int j=i+1; j<n; j++) if (mat[i][j] != mat[j][i]) return 0;
   }
   return 1;
}

int main(){
    while (scanf("%d",&n)==1) {
       for (int i=0; i<n; i++)
         for (int j=0; j<n; j++) scanf("%d",&mat[i][j]);

       if (!judge()) {
           printf("NO\n");
           continue;
       }

       bool flag = 1;
       for (int k=0; k<31; k++) {
           solver.init(n);
           for (int i=0; i<n; i++) {
              for (int j=i+1; j<n; j++) {
                   if (i%2==1 && j%2==1) {
                       if (mat[i][j]&1) {
                            solver.add(i,0,j,1);
                            solver.add(j,0,i,1);
                       }
                       else {
                            solver.add(i,1,i,0);
                            solver.add(j,1,j,0);
                       }
                   }
                   else if (i%2==0 && j%2==0) {
                         if (mat[i][j]&1) {
                             solver.add(i,0,i,1);
                             solver.add(j,0,j,1);
                         }
                         else {
                             solver.add(i,1,j,0);
                             solver.add(j,1,i,0);
                         }
                   }
                   else {
                        if (mat[i][j]&1) {
                             solver.add(i,0,j,1);
                             solver.add(i,1,j,0);
                             solver.add(j,0,i,1);
                             solver.add(j,1,i,0);
                        }
                        else {
                             solver.add(i,0,j,0);
                             solver.add(i,1,j,1);
                             solver.add(j,0,i,0);
                             solver.add(j,1,i,1);
                        }
                   }
                   mat[i][j]>>=1;
              }
           }
           flag = solver.solve();
           if (flag == 0) break;
       }

       if (!flag) printf("NO\n"); else printf("YES\n");

    }
    return 0;
}
