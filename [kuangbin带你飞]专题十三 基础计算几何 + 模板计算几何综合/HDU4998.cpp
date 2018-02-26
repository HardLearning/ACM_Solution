#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double PI = acos(-1.0);
const double eps = 1e-8;
int dcmp(double x){
    if (fabs(x)<eps) return 0;
    return x<0?-1:1;
}

struct Point{
   double x,y;
   Point (double x=0, double y=0):x(x),y(y){}
};

typedef Point Vector;
Vector operator +(Vector A,Vector B) {return Vector(A.x+B.x,A.y+B.y); }
Vector operator -(Vector A,Vector B) {return Vector(A.x-B.x,A.y-B.y); }
Vector operator *(Vector A,double p) {return Vector(A.x*p,A.y*p); }

double Dot(Vector A,Vector B) {return A.x*B.x+A.y*B.y;}
double Cross(Vector A,Vector B) {return A.x*B.y-A.y*B.x;}

Point a,b;
Point ta,tb;
int n;
double x,y,ang;

Point Rotate(double x, double y, double angle, Point a){
    double tx = a.x, ty = a.y;
    a.x = x + (tx-x)*cos(angle)-(ty-y)*sin(angle);
    a.y = y + (tx-x)*sin(angle)+(ty-y)*cos(angle);
    return a;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        a = Point(0,0); b = Point(2,0);
        ta = a; tb = b;
        scanf("%d",&n);

        double ans = 0;
        for (int i=1; i<=n; i++) {
           scanf("%lf%lf%lf",&x,&y,&ang);
           ta =  Rotate(x,y,ang,ta);
           tb =  Rotate(x,y,ang,tb);
           ans += ang;
           if (ans>=2*PI) ans -= 2*PI;
        }

        double A = ta.x*ta.x-a.x*a.x+ta.y*ta.y-a.y*a.y; A *= 0.5;
        double B = tb.x*tb.x-b.x*b.x+tb.y*tb.y-b.y*b.y; B *= 0.5;

        x = (A*(tb.y-b.y)-B*(ta.y-a.y))/( (ta.x-a.x)*(tb.y-b.y)-(tb.x-b.x)*(ta.y-a.y) );
        y = (A-(ta.x-a.x)*x)/(ta.y-a.y);

        printf("%.10f %.10f %.10f\n",x,y,ans);
    }
    return 0;
}
