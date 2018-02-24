#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

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

Vector operator +(Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator -(Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator *(Vector A, double p) { return Vector(A.x*p,A.y*p); }

double Cross(Vector A, Vector B) { return A.x*B.y-A.y*B.x;}
double Dot(Vector A, Vector B) { return A.x*B.x+A.y*B.y;}

const int maxn = 10005;
Point p[maxn],ch[maxn];
int n;

bool cmp(Point a, Point b){
   return dcmp(a.x-b.x)<0 || dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)<0;
}

int ConvexHull(Point *p, Point *ch){
    sort(p,p+n,cmp);
    int m = 0;
    for (int i=0; i<n; i++) {
        while (m>1 && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
        ch[m++] = p[i];
    }

    int k = m;
    for (int i=n-2; i>=0; i--){
        while (m>k && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
        ch[m++] = p[i];
    }

    if (n>1) m--;
    return m;
}

int main(){
    double x,y;
    while (scanf("%d",&n)==1){
        for (int i=0; i<n; i++) scanf("%lf%lf",&x,&y),p[i] = (Point){x,y};
        int m = ConvexHull(p,ch);

        double area = 0;
        Vector A,B;
        for (int i=1; i<m-1; i++) {
            A = ch[i]-ch[0];
            B = ch[i+1]-ch[0];
            area += 0.5*Cross(A,B);
        }
        printf("%d\n",(int)area/50);
    }
    return 0;
}
