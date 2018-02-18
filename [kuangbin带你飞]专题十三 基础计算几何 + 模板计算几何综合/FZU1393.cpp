#include <cstdio>
#include <cmath>
using namespace std;

const double eps = 1e-6;
int dcmp(double x){
    if (fabs(x)<eps) return 0;
    return x<0?-1:1;
}

struct Point3{
   double x,y,z;
   Point3(double x=0, double y=0,double z=0):x(x),y(y),z(z){}
};

typedef Point3 Vector3;

Vector3 operator +(Vector3 A, Vector3 B) { return Vector3(A.x+B.x,A.y+B.y,A.z+B.z); }
Vector3 operator -(Vector3 A, Vector3 B) { return Vector3(A.x-B.x,A.y-B.y,A.z-B.z); }

double det(Vector3 v1, Vector3 v2, Vector3 v3){
   return v1.x*v2.y*v3.z+v2.x*v3.y*v1.z+v3.x*v1.y*v2.z-v1.x*v3.y*v2.z-v2.x*v1.y*v3.z-v3.x*v2.y*v1.z;
}

int main(){
    int T;
    scanf("%d",&T);

    double x,y,z;
    Point3 p1,p2,p3,p4;
    Vector3 v1,v2,v3;
    while (T--){
        scanf("%lf%lf%lf",&x,&y,&z); p1 = Point3(x,y,z);
        scanf("%lf%lf%lf",&x,&y,&z); p2 = Point3(x,y,z);
        scanf("%lf%lf%lf",&x,&y,&z); p3 = Point3(x,y,z);
        scanf("%lf%lf%lf",&x,&y,&z); p4 = Point3(x,y,z);

        v1 = p2 - p1;
        v2 = p3 - p1;
        v3 = p4 - p1;

        if ( dcmp(det(v1,v2,v3))==0 ) printf("Yes\n"); else printf("No\n");
    }
    return 0;
}
