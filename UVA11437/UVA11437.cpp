#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const double eps = 1e-10;
int dcmp(double x) {
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

struct Point{
   double x,y;
   Point(double x=0, double y=0): x(x),y(y){}
};
typedef Point Vector;

Vector operator + (const Vector &A, const Vector &B) {return Vector(A.x+B.x,A.y+B.y);}
Vector operator - (const Vector &A, const Vector &B) {return Vector(A.x-B.x,A.y-B.y);}
Vector operator * (const Vector &A, double p) { return Vector(A.x*p,A.y*p);}
Vector operator / (const Vector &A, double p) { return Vector(A.x/p,A.y/p);}

bool operator < (const Vector &A, const Vector &B){
    return A.x<B.x || (A.x == B.x && A.y < B.y);
}
bool operator == (const Vector &A, const Vector &B){
    return dcmp(A.x-B.x) == 0 && dcmp(A.y-B.y) == 0;
}

double Dot(const Vector &A, const Vector &B){
    return A.x*B.x + A.y*B.y;
}
double Cross(const Vector &A, const Vector &B){
    return A.x*B.y - A.y*B.x;
}
double Length(const Vector &A) {return sqrt(Dot(A,A));}
double Area2(Point A, Point B, Point C) {
     return Cross(B-A,C-A);
}

bool SegmentProperIntersection(const Point &a1, const Point &a2, const Point &b1, const Point &b2){
    double c1 = Cross(a2-a1,b1-a1), c2 = Cross(a2-a1,b2-a1),
           c3 = Cross(b2-b1,a1-b1), c4 = Cross(b2-b1,a2-b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

Point GetLineIntersection(const Point &P, const Vector &v, const Point & Q, const Vector &w){
     Vector u = P-Q;
     double t = Cross(w,u)/Cross(v,w);
     return P+v*t;
}


Point A,B,C,D,E,F;
Point P,Q,R;

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        double x,y;
        scanf("%lf %lf",&x,&y); A = Point(x,y);
        scanf("%lf %lf",&x,&y); B = Point(x,y);
        scanf("%lf %lf",&x,&y); C = Point(x,y);

        D = B + (C-B)*(1.0/3.0);
        E = C + (A-C)*(1.0/3.0);
        F = A + (B-A)*(1.0/3.0);

        P = GetLineIntersection(A,A-D,B,B-E);
        Q = GetLineIntersection(B,B-E,C,C-F);
        R = GetLineIntersection(A,A-D,C,C-F);

        int area = (int)(Area2(P,Q,R)*0.5+0.5);
        printf("%d\n",area);
    }
    return 0;
}
