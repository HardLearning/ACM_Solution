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
   bool operator ==(const Point& rhs) const{
      return x==rhs.x && y==rhs.y;
   }
};

typedef Point Vector;

Vector operator + (Vector A,Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A,Vector B) { return Vector(A.x-B.x,A.y-B.y); }

double Cross(Vector A, Vector B) { return A.x*B.y-A.y*B.x; }
double Dot(Vector A, Vector B) { return A.x*B.x+A.y*B.y;}

struct Line{
    Point p1,p2;
    Line(){}
    Line(Point p1,Point p2):p1(p1),p2(p2){}
};

bool OnSegment(Point p, Point a1, Point a2){
    return dcmp(Cross(a1-p,a2-p))==0 && dcmp(Dot(a1-p,a2-p))<0;
}

bool SegmenProperIntersection(Line a, Line b){
   double c1 = Cross(a.p2-a.p1,b.p1-a.p1), c2 = Cross(a.p2-a.p1,b.p2-a.p1);
   double c3 = Cross(b.p2-b.p1,a.p1-b.p1), c4 = Cross(b.p2-b.p1,a.p2-b.p1);
   return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

inline double Max(double x, double y) { return x>y?x:y; }
inline double Min(double x, double y) { return x<y?x:y; }

int main(){
    int T;
    scanf("%d",&T);
    Line L;
    Line L1,L2,L3,L4;
    Point p1,p2,p3,p4;
    double x1,y1,x2,y2;
    double mx,mn;
    double mx_x,mn_x,mx_y,mn_y;

    int kase = 0;
    while (T--){
        scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
        L = Line(Point(x1,y1),Point(x2,y2));
        mx_x = Max(x1,x2);
        mn_x = Min(x1,x2);
        mx_y = Max(y1,y2);
        mn_y = Min(y1,y2);

        scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
        mx = Max(x1,x2); mn = Min(x1,x2);
        x1 = mn; x2 = mx;
        mx = Max(y1,y2); mn = Min(y1,y2);
        y1 = mn; y2 = mx;
        p1 = Point(x1,y1);
        p2 = Point(x1,y2);
        p3 = Point(x2,y2);
        p4 = Point(x2,y1);

        L1 = Line(p1,p2);
        L2 = Line(p2,p3);
        L3 = Line(p3,p4);
        L4 = Line(p4,p1);

        if (p1.x<=mn_x && mx_x<=p3.x && p1.y<=mn_y && mx_y<=p3.y) {
                printf("T\n");
                continue;
        }

        if (SegmenProperIntersection(L1,L) || SegmenProperIntersection(L2,L) || SegmenProperIntersection(L3,L) || SegmenProperIntersection(L4,L)){
            printf("T\n");
            continue;
        }

        if (OnSegment(L.p1,p1,p2) || OnSegment(L.p1,p2,p3) || OnSegment(L.p1,p3,p4) || OnSegment(L.p1,p4,p1)) {
            printf("T\n");
            continue;
        }

        if (OnSegment(L.p2,p1,p2) || OnSegment(L.p2,p2,p3) || OnSegment(L.p2,p3,p4) || OnSegment(L.p2,p4,p1)) {
            printf("T\n");
            continue;
        }

        if (OnSegment(p1,L.p1,L.p2) || OnSegment(p2,L.p1,L.p2) || OnSegment(p3,L.p1,L.p2) || OnSegment(p4,L.p1,L.p2)) {
            printf("T\n");
            continue;
        }

        if (L.p1 == p1 || L.p1 == p2 || L.p1 == p3 || L.p1 == p4) {
            printf("T\n");
            continue;
        }

        if (L.p2 == p1 || L.p2 == p2 || L.p2 == p3 || L.p2 == p4) {
            printf("T\n");
            continue;
        }


        printf("F\n");
    }
    return 0;
}
