#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-10;
int dcmp(double x) {
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

const int maxn = 10000+10;
struct Point{
   double x,y;
   Point(double x=0,double y=0):x(x),y(y) {}
   bool operator <(const Point &rhs) const {
      return dcmp(x-rhs.x)<0 || (dcmp(x-rhs.x)==0 && dcmp(y-rhs.y)<0);
   }
   bool operator ==(const Point &rhs) const {
      return dcmp(x-rhs.x)==0 && dcmp(y-rhs.y)==0;
   }
};
typedef Point Vector;
Vector operator + (Vector A, Vector B) {return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A, Vector B) {return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A, double p) {return Vector(A.x*p,A.y*p); }
Vector operator / (Vector A, double p) {return Vector(A.x/p,A.y/p); }

double Cross(Vector A, Vector B) {
   return A.x*B.y-A.y*B.x;
}

int ConvexHull(Point *p, int n, Point *ch) {
   sort(p,p+n);
   int m = 0;
   for (int i=0; i<n; i++) {
      while (m>1 && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
      ch[m++] = p[i];
   }

   int k = m;
   for (int i=n-2; i>=0; i--) {
      while (m>k && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
      ch[m++] = p[i];
   }

   if (n>1) m--;
   return m;
}

void getLineGeneralEquation(Point p1, Point p2, double &A, double &B, double &C){
     A = p2.y-p1.y;
     B = p1.x-p2.x;
     C = -A*p1.x - B*p1.y;
}

double sumx,sumy;
Point p[maxn],ch[maxn];
int n;

int main(){
    int T;
    scanf("%d",&T);

    int kase = 0;
    while (T--){
        scanf("%d",&n);
        sumx = sumy = 0;
        for (int i=0; i<n; i++) {
            scanf("%lf %lf",&p[i].x,&p[i].y);
            sumx += p[i].x;
            sumy += p[i].y;
        }

        int m = ConvexHull(p,n,ch);
        m++;
        ch[m].x = ch[0].x;
        ch[m].y = ch[0].y;

        double ans = 1e18;
        double A,B,C;
        double dis,tmp;
        for (int i=0; i<m; i++) {
           getLineGeneralEquation(ch[i],ch[i+1],A,B,C);
           dis = sqrt(A*A+B*B);

           tmp = fabs(A*sumx+B*sumy+C*n)/dis;
           ans = min(ans,tmp);
        }

        printf("Case #%d: %.3f\n",++kase,ans/n);
    }
    return 0;
}
