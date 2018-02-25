#include <cstdio>
#include <cmath>
using namespace std;

struct Point3{
    double x,y,z;
    Point3(double x=0, double y=0, double z=0):x(x),y(y),z(z){}
};

typedef Point3 Vector3;

Vector3 operator +(Vector3 A, Vector3 B) { return Vector3(A.x+B.x,A.y+B.y,A.z+B.z); }
Vector3 operator -(Vector3 A, Vector3 B) { return Vector3(A.x-B.x,A.y-B.y,A.z-B.z); }
Vector3 operator *(Vector3 A, double p) { return Vector3(A.x*p,A.y*p,A.z*p); }

double Dot3(Vector3 A, Vector3 B) { return A.x*B.x+A.y*B.y+A.z*B.z; }
double Length(Vector3 A) { return sqrt(Dot3(A,A)); }

Point3 a,b,c;

int main(){
    double x,y,z;
    while (scanf("%lf%lf%lf",&x,&y,&z)==3){
        a = Point3(x,y,z);

        scanf("%lf%lf%lf",&x,&y,&z); b = Point3(x,y,z);
        scanf("%lf%lf%lf",&x,&y,&z); c = Point3(x,y,z);

        Vector3 ac = c-a, ab = b-a , bc = b-c;
        double d1 = Length(ac), d2 = Length(ab), d3 = Length(bc);
        double p = (d1+d2+d3)*0.5;
        double s = sqrt(p*(p-d1)*(p-d2)*(p-d3));

        double R = d1*d2*d3*0.25/s;
        double r = s/p;

        printf("%.3f\n",r*r/R/R);
    }
    return 0;
}
