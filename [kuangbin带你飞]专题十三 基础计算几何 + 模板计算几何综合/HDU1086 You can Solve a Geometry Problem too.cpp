#include <cstdio>
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
   bool operator ==(const Point& rhs) const {
      return dcmp(x-rhs.x)==0 && dcmp(y-rhs.y)==0;
   }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y); }

double Cross(Vector A, Vector B) { return A.x*B.y-A.y*B.x; }
double Dot(Vector A, Vector B) { return A.x*B.x+A.y*B.y; }

struct Line{
   Point p1,p2;
   Line() {}
   Line(Point p1, Point p2): p1(p1),p2(p2) {}
};

bool SegmentProperIntersection(Line a, Line b){
   double c1 = Cross(a.p2-a.p1,b.p1-a.p1), c2 = Cross(a.p2-a.p1,b.p2-a.p1);
   double c3 = Cross(b.p2-b.p1,a.p1-b.p1), c4 = Cross(b.p2-b.p1,a.p2-b.p1);
   return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

bool OnSegment(Point p, Point a1, Point a2){
    return dcmp(Cross(a1-p,a2-p))==0 && dcmp(Dot(a1-p,a2-p))<0;
}

bool isIntersect(Line a, Line b){
    if (SegmentProperIntersection(a,b)) return 1;
    if (OnSegment(a.p1,b.p1,b.p2) || OnSegment(a.p2,b.p1,b.p2) || OnSegment(b.p1,a.p1,a.p2) || OnSegment(b.p2,a.p1,a.p2)) return 1;
    if (a.p1==b.p1 || a.p1==b.p2 || a.p2==b.p1 || a.p2==b.p2) return 1;
    return 0;
}

const int maxn = 100+5;
int n;
Line line[maxn];

int main(){
    double x1,y1,x2,y2;
    while (scanf("%d",&n)==1 && n){
        for (int i=1; i<=n; i++) {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            line[i] = Line(Point(x1,y1),Point(x2,y2));
        }

        int ans = 0;
        for (int i=1; i<n; i++)
            for (int j=i+1; j<=n; j++) if (isIntersect(line[i],line[j])) ans++;
        printf("%d\n",ans);
    }
    return 0;
}
