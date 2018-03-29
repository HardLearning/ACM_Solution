#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

const double eps = 1e-8;
int dcmp(double x){
    if (fabs(x)<eps) return 0;
    return x<0?-1:1;
}

const int maxn = 100+5;
struct Point{
   int x,y;
   Point(int x=0, int y=0):x(x),y(y){}
};
Point p1[maxn],p2[maxn];
int n;

struct TwoSAT{
    int S[maxn<<1],c;
    bool mark[maxn<<1];
    vector<int> G[maxn<<1];
    int n;

    void init(int n) {
       this->n = n;
       memset(mark,0,sizeof(mark));
       for (int i=0; i<n*2; i++) G[i].clear();
    }

    void add(int x, int xval, int y, int yval) {
       x = x*2 + xval;
       y = y*2 + yval;
       G[y^1].push_back(x);
       G[x^1].push_back(y);
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

double dis1[maxn][maxn][2];
double dis2[maxn][maxn][2];

inline double Length(Point a, Point b) {
   return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}

bool judge(double mid) {
    mid = mid*2;
    solver.init(n);
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
             if ( dcmp(dis1[i][j][0]-mid)<0 ) solver.add(i,0,j,0);
             if ( dcmp(dis2[i][j][0]-mid)<0 ) solver.add(i,1,j,0);
             if ( dcmp(dis1[i][j][1]-mid)<0 ) solver.add(i,0,j,1);
             if ( dcmp(dis2[i][j][1]-mid)<0 ) solver.add(i,1,j,1);
        }
    }
    return solver.solve();
}

int main(){
    while (scanf("%d",&n)==1) {
        int x,y;
        for (int i=0; i<n; i++) {
            scanf("%d%d",&x,&y); p1[i] = Point(x,y);
            scanf("%d%d",&x,&y); p2[i] = Point(x,y);
        }

        for (int i=0; i<n; i++) {
            for (int j=i+1; j<n; j++) dis1[i][j][0] = Length(p1[i],p1[j]), dis1[i][j][1] = Length(p1[i],p2[j]);
            for (int j=i+1; j<n; j++) dis2[i][j][0] = Length(p2[i],p1[j]), dis2[i][j][1] = Length(p2[i],p2[j]);
        }

        double left = 0, right = 1e5;
        double mid, ans = 0;
        while (right-left>eps) {
            mid = (left+right)*0.5;
            if (judge(mid)) {
                ans = mid;
                left = mid+eps;
            }
            else right = mid-eps;
        }

        printf("%.2f\n",ans);
    }
    return 0;
}
