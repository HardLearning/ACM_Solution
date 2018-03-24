#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 8000+5;
struct TwoSAT{
    int n;
    int S[maxn*2],c;
    bool mark[maxn*2];
    vector<int> G[maxn*2];

    void init(int n) {
       this->n = n;
       for (int i=0; i<n*2; i++) G[i].clear();
       memset(mark,0,sizeof(mark));
    }

    void add(int x, int y) {
        G[x].push_back(y^1);
        G[y].push_back(x^1);
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

int main(){
    while (scanf("%d%d",&n,&m)==2) {
        solver.init(n);

        int a,b;
        for (int i=0; i<m; i++) {
            scanf("%d%d",&a,&b);
            a--; b--;
            solver.add(a,b);
        }

        if (!solver.solve()) printf("NIE\n");
        else {
            for (int i=0; i<n; i++) if (solver.mark[i<<1]) printf("%d\n",i<<1|1);
            else printf("%d\n",(i<<1)+2);
        }
    }
    return 0;
}
