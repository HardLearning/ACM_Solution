#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int maxm = 510;
const int maxn = 1010;
struct TwoSAT{
    int n;
    bool mark[maxn*2];
    vector<int> G[maxn*2];
    int S[maxn*2],c;

    void init(int n){
        this->n = n;
        for (int i=0; i<n*2; i++) G[i].clear();
        memset(mark,0,sizeof(mark));
    }

    inline void add(int x, int y) {G[x].push_back(y); }

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
        for (int i=0; i<2*n; i+=2)  if (!mark[i] && !mark[i+1]) {
            c = 0;
            if (!dfs(i)) {
                while (c>0) mark[S[--c]] = 0;
                if (!dfs(i+1)) return 0;
            }
        }
        return 1;
    }
};
TwoSAT solver;

struct Point{
   int x,y;
}p[maxm];
int n,m;

inline bool judge(int i, int j) {
   return p[j].x>=p[i].x && p[j].x<=p[i].y && p[j].y>=p[i].y;
}

int main(){
    while (scanf("%d%d",&n,&m)==2) {
        solver.init(m);
        for (int i=0; i<m; i++) {
            scanf("%d%d",&p[i].x,&p[i].y);
            if (p[i].x>p[i].y) swap(p[i].x,p[i].y);
        }

        for (int i=0; i<m; i++) {
            for (int j=i+1; j<m; j++) {
                if (judge(i,j) || judge(j,i)) {
                      solver.add(i*2,j*2+1);
                      solver.add(i*2+1,j*2);
                      solver.add(j*2,i*2+1);
                      solver.add(j*2+1,i*2);
                }
            }
        }

        if (solver.solve()) printf("panda is telling the truth...\n");
        else printf("the evil panda is lying again\n");
    }
    return 0;
}
