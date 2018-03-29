#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 10000+5;
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

    void add(int x, int xval , int y, int yval) {
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
int a[maxn],b[maxn];
int x,y,z;

int main(){
    int T;
    scanf("%d",&T);
    for (int kase = 1; kase <= T; kase++) {
        scanf("%d%d",&n,&m);
        for (int i=0; i<n; i++) {
           scanf("%d",&a[i]);
           if (a[i]==1) b[i] = 2;
           else if (a[i]==2) b[i] = 3;
           else b[i] = 1;
           if (a[i]>b[i]) swap(a[i],b[i]);
        }

        solver.init(n);
        while (m--) {
           scanf("%d%d%d",&x,&y,&z);
           x--; y--;
           if (z == 0) {
              if (a[x]!=a[y]) {
                 solver.add(x,0,y,1);
                 solver.add(y,0,x,1);
              }
              if (a[x]!=b[y]) {
                 solver.add(x,0,y,0);
                 solver.add(y,1,x,1);
              }
              if (b[x]!=b[y]) {
                 solver.add(x,1,y,0);
                 solver.add(y,1,x,0);
              }
              if (b[x]!=a[y]) {
                 solver.add(x,1,y,1);
                 solver.add(y,0,x,0);
              }
           }
           else {
              if (a[x]==a[y]) {
                 solver.add(x,0,y,1);
                 solver.add(y,0,x,1);
              }
              if (a[x]==b[y]) {
                 solver.add(x,0,y,0);
                 solver.add(y,1,x,1);
              }
              if (b[x]==b[y]) {
                 solver.add(x,1,y,0);
                 solver.add(y,1,x,0);
              }
              if (b[x]==a[y]) {
                 solver.add(x,1,y,1);
                 solver.add(y,0,x,0);
              }
           }
        }

        if (solver.solve()) printf("Case #%d: yes\n",kase);
        else printf("Case #%d: no\n",kase);
    }
    return 0;
}
