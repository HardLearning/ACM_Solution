#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-10;
int dcmp(double x){
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

const int maxn = 500+10;
struct Point{
   double x,y;
   Point(double x=0, double y=0):x(x),y(y) {}
   bool operator <(const Point &rhs) const {
       return dcmp(x-rhs.x)<0 || (dcmp(x-rhs.x)==0 && dcmp(y-rhs.y)<0);
   }
   bool operator ==(const Point &rhs) const {
      return dcmp(x-rhs.x)==0 && dcmp(y-rhs.y)==0;
   }
};

typedef Point Vector;
Vector operator + (Point A, Point B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Point A, Point B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Point A, double p) { return Vector(A.x*p,A.y*p); }
Vector operator / (Point A, double p) { return Vector(A.x/p,A.y/p); }

double Cross(Vector A, Vector B){ return A.x*B.y - A.y*B.x; }

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }

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

bool OnSegment(Point p, Point p1, Point p2) {
    return dcmp(Cross(p1-p,p2-p))==0 && dcmp(Dot(p1-p,p2-p)) < 0;
}

int isPointInPolygon(Point p, Point *poly, int n){
   int wn = 0;
   Point p1,p2;
   for (int i=0; i<n; i++) {
      p1 = poly[i];
      p2 = poly[(i+1)%n];
      if (p == p1 || p == p2 || OnSegment(p,p1,p2)) return -1;
      int k = dcmp(Cross(p2-p1,p-p1));
      int d1 = dcmp(p1.y - p.y);
      int d2 = dcmp(p2.y - p.y);
      if (k>0 && d1<=0 && d2>0) wn++;
      if (k<0 && d2<=0 && d1>0) wn--;
   }
   if (wn != 0) return 1; // inside
   return 0; // outside
}

bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2){
    double c1 = Cross(a2-a1,b1-a1), c2 = Cross(a2-a1,b2-a1),
           c3 = Cross(b2-b1,a1-b1), c4 = Cross(b2-b1,a2-b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

bool ConvexPolygonDisjoint(Point *ch1,int n, Point *ch2, int m) {
    for (int i=0; i<n; i++)
        if (isPointInPolygon(ch1[i],ch2,m)!=0) return 0;
    for (int i=0; i<m; i++)
        if (isPointInPolygon(ch2[i],ch1,n)!=0) return 0;
    for (int i=0; i<n; i++)
      for (int j=0; j<m; j++)
        if ( SegmentProperIntersection(ch1[i],ch1[(i+1)%n],ch2[j],ch2[(j+1)%m]) )  return 0;
    return 1;
}

int n,m;
int tot1,tot2;
Point red[maxn],blue[maxn];
Point ch_red[maxn],ch_blue[maxn];

int main(){
    while (scanf("%d %d",&n,&m)==2 && n+m){
        for (int i=0; i<n; i++) scanf("%lf %lf",&red[i].x,&red[i].y);
        for (int i=0; i<m; i++) scanf("%lf %lf",&blue[i].x,&blue[i].y);

        tot1 = ConvexHull(red,n,ch_red);
        tot2 = ConvexHull(blue,m,ch_blue);

        if (ConvexPolygonDisjoint(ch_red,tot1,ch_blue,tot2)) printf("Yes\n");
        else printf("No\n");

    }
    return 0;
}
