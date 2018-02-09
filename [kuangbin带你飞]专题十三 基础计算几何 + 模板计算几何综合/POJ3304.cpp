#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-10;
int dcmp(double x){
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

const int maxn = 100+5;
struct Point{
   double x,y;
   Point (double x=0, double y=0):x(x),y(y){}
};
typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p,A.y*p); }

double Cross(Vector A, Vector B) { return A.x*B.y-A.y*B.x; }
double Dot(Vector A, Vector B) { return A.x*B.x+A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A,A)); }

struct Line{
   Point p1,p2;
   Line(){}
   Line (Point p1, Point p2): p1(p1),p2(p2) { }
};
Line line[maxn];
int n;

bool SegmentIntersection(Line L1, Line L2){
    Vector c1 = L1.p1-L2.p1, c2 = L1.p2 - L2.p1;
    Vector c3 = L1.p1-L2.p2, c4 = L1.p2 - L2.p2;
    return dcmp(Cross(c1,c2))*dcmp(Cross(c3,c4)) <= 0;
}

bool judge(Line L){
    if (dcmp(Length(L.p1-L.p2))==0) return 0;
    for (int i=1; i<=n; i++) if (!SegmentIntersection(L,line[i])) return 0;
    return 1;
}

bool solve(){
     Line L;
     for (int i=1; i<=n; i++) {
         for (int j=i; j<=n; j++) {
              L = Line(line[i].p1,line[j].p1);
              if (judge(L)) return 1;
              L = Line(line[i].p2,line[j].p1);
              if (judge(L)) return 1;

              L = Line(line[i].p1,line[j].p2);
              if (judge(L)) return 1;
              L = Line(line[i].p2,line[j].p2);
              if (judge(L)) return 1;
         }
     }
     return 0;
}

int main(){
    int T;
    scanf("%d",&T);

    double X1,Y1,X2,Y2;
    Point p1,p2;

    while (T--){
        scanf("%d",&n);
        for (int i=1; i<=n; i++) {
            scanf("%lf %lf %lf %lf",&X1,&Y1,&X2,&Y2);
            p1 = Point(X1,Y1);
            p2 = Point(X2,Y2);
            line[i] = Line(p1,p2);
        }

        if (solve()) printf("Yes!\n"); else printf("No!\n");
    }
    return 0;
}
