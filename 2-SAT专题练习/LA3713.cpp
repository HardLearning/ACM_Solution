#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 100000+5;
struct TwoSAT{
    int n;
    int S[maxn*2],c;
    bool mark[maxn*2];
    vector<int> G[maxn*2];

    void init(int n){
       this->n = n;
       memset(mark,0,sizeof(mark));
       for (int i=0; i<2*n; i++) G[i].clear();
    }

    void add(int x, int xval, int y, int yval) {
        x = x*2 + xval;
        y = y*2 + yval;
        G[x^1].push_back(y);
        G[y^1].push_back(x);
    }

    bool dfs(int x){
       if (mark[x^1]) return 0;
       if (mark[x]) return 1;
       mark[x] = 1;
       S[c++] = x;
       for (int i=0; i<G[x].size(); i++)
         if (!dfs(G[x][i])) return 0;
       return 1;
    }

    bool solve(){
        for (int i=0; i<2*n; i+=2) {
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
int total_age;
int age[maxn];

inline bool is_young(int x) { return age[x]*n<total_age; }
int main(){
    while (scanf("%d%d",&n,&m)==2 && n+m) {
        total_age = 0;
        for (int i=0; i<n; i++) scanf("%d",&age[i]), total_age += age[i];
        solver.init(n);

        int a,b;
        for (int i=0; i<m; i++) {
            scanf("%d%d",&a,&b);
            a--; b--;
            if (a==b) continue;
            solver.add(a,1,b,1);
            if (is_young(a) == is_young(b)) solver.add(a,0,b,0);
        }

        if (!solver.solve()) printf("No solution.\n");
        else {
            for (int i=0; i<n; i++)
                if (solver.mark[i*2]) printf("C\n");
                else if (age[i]*n<total_age) printf("B\n");
                else printf("A\n");
        }
    }
    return 0;
}
