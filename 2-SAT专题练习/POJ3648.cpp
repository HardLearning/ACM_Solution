#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 100+5;
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
       x = x*2 + xval; y = y*2 + yval;
       G[x^1].push_back(y);
       G[y^1].push_back(x);
    }

    bool dfs(int x) {
       if (mark[x^1]) return 0;
       if (mark[x]) return 1;
       mark[x] = 1;
       S[c++] = x;
       for (int i=0; i<G[x].size(); i++) if (!dfs(G[x][i])) return 0;
       return 1;
    }

    bool solve(){
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

int a1,a2;
int v1,v2;
char c1,c2;

int main(){
    while (scanf("%d%d",&n,&m)==2) {
        solver.init(n);
        while (m--) {
            scanf("%d%c%d%c",&a1,&c1,&a2,&c2);
            if (c1 == 'h') v1 = 0; else v1 = 1;
            if (c2 == 'h') v2 = 0; else v2 = 1;
            solver.add(a1,v1,a2,v2);
        }
        solver.add(0,1,0,1);

        if (!solver.solve()) printf("bad luck\n");
        else {
            for (int i=2; i<n*2; i+=2) {
               if (solver.mark[i]) printf("%dh ",i/2);
               else printf("%dw ",i/2);
            }
            printf("\n");
        }
    }
    return 0;
}
