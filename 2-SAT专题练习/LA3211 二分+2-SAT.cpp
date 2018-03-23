#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
using namespace std;

const int maxn = 2000+5;
struct TwoSAT {
    int n;
    vector<int> G[maxn*2];
    bool mark[maxn*2];
    int S[maxn*2],c;

    void init(int n){
        this->n = n;
        for (int i=0; i<n*2; i++) G[i].clear();
        memset(mark,0,sizeof(mark));
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
int T[maxn][2];

inline int Max(int x, int y) {return x>y?x:y; }

bool judge(int mid) {
     solver.init(n);
     for (int i=0; i<n; i++)
        for (int a=0; a<2; a++)
           for (int j=i+1; j<n; j++)
              for (int b=0; b<2; b++)
                 if (abs(T[i][a]-T[j][b])<mid) solver.add(i,a^1,j,b^1);
    return solver.solve();
}

int main(){
    while (scanf("%d",&n)==1 && n){
        int left = 0, right = 0;
        for (int i=0; i<n; i++) {
            for (int j=0; j<2; j++) {
                scanf("%d",&T[i][j]);
                right = Max(right,T[i][j]);
            }
        }

        int mid,ans;
        while (left<=right) {
            mid = (left+right)>>1;
            if (judge(mid)) {
                ans = mid;
                left = mid+1;
            }
            else right = mid-1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
