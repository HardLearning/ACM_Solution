#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-8;
int dcmp(double x) {
    if (fabs(x)<eps) return 0;
    return x<0?-1:1;
}

struct Point{
    double x,y;
    Point (double x=0, double y=0): x(x), y(y) {}
    bool operator <(const Point &rhs) const {
       return dcmp(x-rhs.x)<0 || dcmp(x-rhs.x)==0 && dcmp(y-rhs.y)<0;
    }
};

typedef Point Vector;
Vector operator +(Vector A, Vector B) {return Vector(A.x+B.x,A.y+B.y); }
Vector operator -(Vector A, Vector B) {return Vector(A.x-B.x,A.y-B.y); }
double Cross(Vector A,Vector B) {return A.x*B.y-A.y*B.x;}


const int maxn = 50000+10;
int n;
Point p[maxn];
Point poly[maxn];

int ConvexHull(){
     sort(p,p+n);
     int m = 0;
     for (int i=0; i<n; i++) {
        while (m>1 && Cross(poly[m-1]-poly[m-2],p[i]-poly[m-2]) <= 0) m--;
        poly[m++] = p[i];
     }

     int k = m;
     for (int i=n-2; i>=0; i--) {
        while (m>k && Cross(poly[m-1]-poly[m-2],p[i]-poly[m-2]) <= 0) m--;
        poly[m++] = p[i];
     }

     if (n>1) m--;
     return m;
}

int main(){
    while (scanf("%d",&n)==1) {
        double x,y;
        for (int i=0; i<n; i++) scanf("%lf%lf",&x,&y), p[i] = Point(x,y);
        int tot = ConvexHull();
        double area = 0;

        for (int i=0; i<tot; i++)
            for (int j=i+1; j<tot; j++)
              for (int k=j+1; k<tot; k++) {
                   area = max(area,fabs(Cross(poly[j]-poly[i],poly[k]-poly[j])));
              }
        printf("%.2f\n",area*0.5);
    }
    return 0;
}
