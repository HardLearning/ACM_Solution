#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const double PI = acos(-1.0);
const double eps = 1e-10;
int dcmp(double x) {
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

const int maxn = 2500;
struct Point{
   double x,y;
   Point (double x=0, double y=0): x(x),y(y) {}
   bool operator <(const Point &rhs) const {
      return x<rhs.x || (x==rhs.x && y<rhs.y);
   }
   bool operator == (const Point &rhs) const {
      return dcmp(x-rhs.x)==0 && dcmp(y-rhs.y)==0;
   }
};
typedef Point Vector;
Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p,A.y*p); }
Vector operator / (Vector A, double p) { return Vector(A.x/p,A.y/p); }

Vector Rotate(Vector A, double rad) {
   return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}

double Cross(Vector A, Vector B){
    return A.x*B.y - A.y*B.x;
}

double torad(double deg){
    return deg/180*PI;
}


int n,tot;
Point P[maxn],ch[maxn];


int ConvexHull(Point * p, int n, Point *ch){
    sort(p,p+n);
    int m = 0;

    for (int i=0; i<n; i++) {
        while (m>1 && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }

    int k = m;
    for (int i=n-2; i>=0; i--) {
        while (m>k && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if (n>1) m--;
    return m;
}

double PolygonArea(Point *p, int n) {
    double area = 0;
    for (int i=1; i<n-1; i++)
        area += Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        tot = 0;
        double area1 = 0;
        double x,y,w,h,j,ang;

        scanf("%d",&n);
        for (int i=0; i<n; i++) {
            scanf("%lf %lf %lf %lf %lf",&x,&y,&w,&h,&j);
            Point o(x,y);
            ang = -torad(j);

            P[tot++] = o + Rotate(Vector(-w/2,-h/2),ang);
            P[tot++] = o + Rotate(Vector(w/2,-h/2),ang);
            P[tot++] = o + Rotate(Vector(-w/2,h/2),ang);
            P[tot++] = o + Rotate(Vector(w/2,h/2),ang);

            area1 += w*h;
        }

        int m = ConvexHull(P,tot,ch);
        double area2 = PolygonArea(ch,m);

        printf("%.1f %%\n",area1*100/area2);
    }
    return 0;
}
