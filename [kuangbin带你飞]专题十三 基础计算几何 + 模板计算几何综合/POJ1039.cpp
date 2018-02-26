#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-6;
int dcmp(double x){
    if (fabs(x)<eps) return 0;
    return x<0?-1:1;
}

struct Point{
   double x,y;
   Point(double x=0, double y=0):x(x),y(y){}
};

typedef Point Vector;

Vector operator +(Vector A,Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator -(Vector A,Vector B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator *(Vector A,double p) { return Vector(A.x*p,A.y*p); }

double Cross(Vector A,Vector B) {return A.x*B.y-A.y*B.x;}

const int maxn = 25;
Point up[maxn],down[maxn];
int n;
bool flag;

Point GetLineIntersection(Point p, Vector v, Point q, Vector w){
   Vector u = p-q;
   double t = Cross(w,u)/Cross(v,w);
   return p+v*t;
}

double solve(){
    Point p;
    double ans = up[1].x;
    int k;

    for (int i=1; i<=n; i++)
      for (int j=1; j<=n; j++) if (i!=j) {
          flag = 1;
          for (k=1; k<=n; k++) {
             p = GetLineIntersection(up[i],up[i]-down[j],up[k],up[k]-down[k]);
             double t = up[k].y-p.y;
             if (dcmp(t)<0 || dcmp(t-1)>0) {flag = 0; break; }
          }

          if (flag) return ans;
          if (k<=max(i,j)) continue;

          p = GetLineIntersection(up[i],up[i]-down[j],up[k],up[k]-up[k-1]);
          ans = max(ans,p.x);

          p = GetLineIntersection(up[i],up[i]-down[j],down[k],down[k]-down[k-1]);
          ans = max(ans,p.x);
      }
    return ans;
}

int main(){
    while (scanf("%d",&n)==1 && n){
        double x,y;
        for (int i=1; i<=n; i++) {
            scanf("%lf%lf",&x,&y);
            up[i] = Point(x,y);
            down[i] = Point(x,y-1);
        }

        flag  = 0;
        double ans = solve();

        if (flag) printf("Through all the pipe.\n");
        else printf("%.2f\n",ans);


    }
    return 0;
}
