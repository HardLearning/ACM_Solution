#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
int dcmp(double x){
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

struct Point{
   double x,y;
   Point(double x=0,double y=0):x(x),y(y){}
   bool operator ==(const Point& rhs) const {
      return dcmp(x-rhs.x)==0 && dcmp(y-rhs.y)==0;
   }
};

typedef Point Vector;

Vector operator +(Vector A, Vector B) {return Vector(A.x+B.x,A.y+B.y); }
Vector operator -(Vector A, Vector B) {return Vector(A.x-B.x,A.y-B.y); }
Vector operator *(Vector A, double p) {return Vector(A.x*p,A.y*p); }

double Cross(Vector A,Vector B) { return A.x*B.y-A.y*B.x; }
double Dot(Vector A,Vector B) { return A.x*B.x+A.y*B.y; }

struct Line{
    Point p1,p2;
    Line(){}
    Line(Point p1,Point p2):p1(p1),p2(p2){}

    double getK(){
       return (p1.y-p2.y)/(p1.x-p2.x);
    }
};

bool isParallel(Line a, Line b){
   return dcmp(Cross(a.p1-a.p2,b.p1-b.p2))==0;
}

bool SegmentProperIntersection(Line a, Line b){
    double c1 = Cross(a.p2-a.p1,b.p1-a.p1), c2 = Cross(a.p2-a.p1,b.p2-a.p1);
    double c3 = Cross(b.p2-b.p1,a.p1-b.p1), c4 = Cross(b.p2-b.p1,a.p2-b.p1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

Point GetLineIntersection(Point P, Vector v, Point Q, Vector w){
    Vector u = P-Q;
    double t = Cross(w,u)/Cross(v,w);
    return P+v*t;
}

bool OnSegment(Point p, Point a1, Point a2){
   return dcmp(Cross(a1-p,a2-p))==0 && dcmp(Dot(a1-p,a2-p))<0;
}

bool isIntersect(Line a, Line b, Point& p){
    if (SegmentProperIntersection(a,b)) {
        p = GetLineIntersection(a.p1,a.p1-a.p2,b.p1,b.p1-b.p2);
        return 1;
    }

    if (OnSegment(a.p1,b.p1,b.p2)) { p = a.p1; return 1; }

    if (OnSegment(b.p1,a.p1,a.p2)){ p = b.p1; return 1; }

    if (a.p1==b.p1) { p = a.p1; return 1; }

    return 0;
}

int main(){
    int T;
    scanf("%d",&T);

    double x1,y1,x2,y2;
    Line L1,L2;

    while (T--){
        scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
        if (y1>y2) {
            swap(y1,y2);
            swap(x1,x2);
        }
        L1 = Line(Point(x1,y1),Point(x2,y2));

        scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
        if (y1>y2) {
            swap(y1,y2);
            swap(x1,x2);
        }
        L2 = Line(Point(x1,y1),Point(x2,y2));

        if (dcmp(L1.p1.y-L1.p2.y)==0 || dcmp(L2.p1.y-L2.p2.y)==0) { printf("0.00\n"); continue; }

        if (isParallel(L1,L2)) { printf("0.00\n"); continue; }

        Point p;
        if (!isIntersect(L1,L2,p)) {
                printf("0.00\n");
                continue;
        }
        else {
           L1.p1 = p; L2.p1 = p;
           if (dcmp(L1.p1.x-L1.p2.x)!=0 && dcmp(L2.p1.x-L2.p2.x)!=0 ){
              double k1 = L1.getK(), k2 = L2.getK();
              if (dcmp(k1*k2)>0) {
                if ( dcmp(k1-k2)>0 && dcmp(L1.p2.x-L2.p2.x)>=0 || dcmp(k1-k2)<0 && dcmp(L1.p2.x-L2.p2.x)<=0 ) {
                  printf("0.00\n");
                  continue;
                }
              }
           }

           Line L3;
           if (L1.p2.y<L2.p2.y) {
               L3 = Line(L1.p2,Point(L1.p2.x+1,L1.p2.y));
               L2.p2 = GetLineIntersection(L2.p1,L2.p1-L2.p2,L3.p1,L3.p2-L3.p1);
           }
           else {
               L3 = Line(L2.p2,Point(L2.p2.x+1,L2.p2.y));
               L1.p2 = GetLineIntersection(L1.p1,L1.p1-L1.p2,L3.p1,L3.p2-L3.p1);
           }
           printf("%.2f\n",fabs(Cross(L2.p2-p,L1.p2-p))/2+eps);

        }

    }
    return 0;
}
