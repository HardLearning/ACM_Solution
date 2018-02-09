#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

const double eps = 1e-6;
int dcmp(double x){
   if (fabs(x)< eps) return 0;
   return x<0?-1:1;
}

struct Point{
   double x,y;
   Point (double x=0, double y=0): x(x),y(y) {}
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p,A.y*p); }

double Dot (Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Cross (Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
double Length (Vector A) { return sqrt(Dot(A,A)); }


struct Line{
   Point p;
   Vector v;
   Line() {}
   Line(Point p, Vector v): p(p),v(v) {}
};

Point GetLineIntersection(Line L1, Line L2){
   Vector u = L1.p - L2.p;
   double t = Cross(L2.v,u) / Cross(L1.v,L2.v);
   return L1.p + L1.v*t;
}

double DistanceToLine(Point p, Line L){
   Vector u = p - L.p;
   return fabs(Cross(L.v,u))/Length(L.v);
}

bool judge(Line L1, Line L2){
   return dcmp(Cross(L1.v,L2.v))==0;
}

int main(){
    int n;
    while (scanf("%d",&n)==1){

        int x1,y1,x2,y2,x3,y3,x4,y4;
        Point p1,p2,p3,p4;
        Line L1,L2;

        printf("INTERSECTING LINES OUTPUT\n");
        while (n--) {
            scanf("%d%d%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
            p1 = Point(x1,y1); p2 = Point(x2,y2);
            L1 = Line(p1,p1-p2);
            p3 = Point(x3,y3); p4 = Point(x4,y4);
            L2 = Line(p3,p3-p4);

            double d1 = DistanceToLine(p1,L2);
            double d2 = DistanceToLine(p2,L2);

            if (judge(L1,L2)) {
                if (dcmp(d1)==0) printf("LINE\n");
                else printf("NONE\n");
            }
            else {
                Point p = GetLineIntersection(L1,L2);
                printf("POINT %.2f %.2f\n",p.x,p.y);
            }
        }
        printf("END OF OUTPUT\n");
    }
    return 0;
}
