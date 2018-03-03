#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;

const double eps = 1e-8;
int dcmp(double x){
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

struct Point{
    double x,y;
    Point (double x=0, double y=0):x(x),y(y){}
};

typedef Point Vector;
Vector operator -(Vector A, Vector B) {return Vector(A.x-B.x,A.y-B.y); }
double Dot(Vector A,Vector B) {return A.x*B.x+A.y*B.y; }
double Length(Vector A) {return sqrt(Dot(A,A)); }

const int maxn = 55;
double dis[maxn][maxn];
Point city[maxn],radar[maxn];
int n,m,K;

const int maxnode = 3000;
struct DLX{
    int n,m,sz;
    int U[maxnode],D[maxnode],R[maxnode],L[maxnode];
    int row[maxnode],col[maxnode];
    int H[maxn],S[maxn];
    //int ansd,ans[maxn];

    void init(int n, int m){
        this->n = n; this->m = m;
        for (int i=0; i<=m; i++) {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[m] = 0; L[0] = m;
        sz = m;
        for (int i=1; i<=n; i++) H[i] = -1;
    }

    void addRow(int r, int c){
        ++S[col[++sz]=c];
        row[sz] = r;
        D[sz] = D[c];
        U[D[c]] = sz;
        U[sz] = c;
        D[c] = sz;
        if (H[r]<0) H[r] = L[sz] = R[sz] = sz;
        else {
            R[sz] = R[H[r]];
            L[R[H[r]]] = sz;
            L[sz] = H[r];
            R[H[r]] = sz;
        }
    }

    void remove(int c){
         for (int i=D[c]; i!=c; i=D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }

    void restore(int c){
         for (int i=U[c]; i!=c; i=U[i])
            L[R[i]] = R[L[i]] = i;
    }

    bool v[maxnode];
    int cut(){
        int ret = 0;
        for (int c=R[0]; c!=0; c=R[c]) v[c] = 1;
        for (int c=R[0]; c!=0; c=R[c]) if (v[c]) {
            ret++;
            v[c] = 0;
            for (int i=D[c]; i!=c; i=D[i])
                for (int j=R[i]; j!=i; j=R[j]) v[col[j]] = 0;
        }
        return ret;
    }

    bool dfs(int d){
        if (d+cut()>K) return 0;
        if (d>K) return 0;
        if (R[0]==0) return 1;

        int c = R[0];
        for (int i=R[0]; i!=0; i=R[i]) if (S[i]<S[c]) c=i;
        for (int i = D[c]; i!=c; i=D[i]) {
            remove(i);
            for (int j=R[i]; j!=i; j=R[j]) remove(j);
            if (dfs(d+1)) return 1;
            for (int j=L[i]; j!=i; j=L[j]) restore(j);
            restore(i);
        }
        return 0;
    }
};

DLX solver;

bool judge(double d){
    solver.init(m,n);
    for (int i=1; i<=m; i++)
        for (int j=1; j<=n; j++) if (dcmp(dis[i][j]-d)<0) solver.addRow(i,j);
    return solver.dfs(0);
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
       scanf("%d%d%d",&n,&m,&K);
       double x,y;
       for (int i=1; i<=n; i++) {
           scanf("%lf%lf",&x,&y);
           city[i] = Point(x,y);
       }
       for (int i=1; i<=m; i++) {
           scanf("%lf%lf",&x,&y);
           radar[i] = Point(x,y);
       }

       for (int i=1; i<=m; i++) {
          for (int j=1; j<=n; j++) dis[i][j] = Length(radar[i]-city[j]);
       }

       double left = 0, right = 1e5, mid;
       while (dcmp(right-left)>0) {
           mid = (left+right)/2.0;
           if (judge(mid)) right = mid-eps; else left = mid+eps;
       }
       printf("%.6f\n",right);

    }
    return 0;
}
