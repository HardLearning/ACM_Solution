#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define pb push_back
const double eps = 1e-8;
int dcmp(double x){
    if (fabs(x)<eps) return 0;
    return x<0?-1:1;
}

struct Point{
   double x,y;
   Point (double x=0, double y=0):x(x),y(y){}
   bool operator ==(const Point& rhs) const {
     return dcmp(x-rhs.x)==0 && dcmp(y-rhs.y)==0;
   }
};

typedef Point Vector;

Vector operator +(Vector A, Vector B){return Vector(A.x+B.x,A.y+B.y); }
Vector operator -(Vector A, Vector B){return Vector(A.x-B.x,A.y-B.y); }
Vector operator *(Vector A, double p){return Vector(A.x*p,A.y*p); }

double Cross(Vector A,Vector B) {return A.x*B.y-A.y*B.x;}
double Dot(Vector A,Vector B) {return A.x*B.x+A.y*B.y;}
double Length(Vector A) { return sqrt(Dot(A,A));}

const int maxn = 200;
int n;
vector<Point>p;

Point cir;
double r;

bool isConvexHull(){
    int n = p.size();
    for (int i=0; i<n-2; i++)
        if (dcmp(Cross(p[i+1]-p[i],p[i+2]-p[i+1]))<0) return 0;
    return 1;
}

bool isPointOnSegment(Point p, Point a1, Point a2){
   return dcmp(Cross(a1-p,a2-p))==0 && dcmp(Dot(a1-p,a2-p))<0;
}

int isPointInPolygon(Point p,vector<Point>&poly){
    int wn = 0;
    int n = poly.size();

    for (int i=0; i<n-1; i++) {
        if (isPointOnSegment(p,poly[i],poly[i+1])) return -1;
        int k = dcmp( Cross(poly[i+1]-poly[i],p-poly[i]) );
        int d1 = dcmp(poly[i].y-p.y);
        int d2 = dcmp(poly[i+1].y-p.y);
        if (k>0 && d1<=0 && d2>0) wn++;
        if (k<0 && d2<=0 && d1>0) wn--;
    }
    if (wn!=0) return 1;
    return 0;
}

double DistanceToLine(Point P, Point A, Point B){
   if (A == B) return Length(P-A);
   Vector v1 = B-A, v2 = P-A, v3 = P-B;
   if (dcmp(Dot(v1,v2))<0) return Length(v2);
   else if (dcmp(Dot(v1,v3))>0) return Length(v3);
   else return fabs(Cross(v1,v2))/Length(v1);
}

int main(){
    double x,y;
    while (scanf("%d",&n) && n>=3) {
        scanf("%lf%lf%lf",&r,&x,&y);
        cir = (Point){x,y};
        p.clear();
        for (int i=0; i<n; i++) {
            scanf("%lf%lf",&x,&y);
            p.pb((Point){x,y});
        }
        p.pb(p[0]);

        double tmp = 0;
        for (int i=0; i<p.size()-2; i++) {
            if (dcmp(tmp)!=0) break;
            tmp = dcmp(Cross(p[i+1]-p[i],p[i+2]-p[i+1]));
        }

        if (tmp<0) reverse(p.begin(),p.end());

        if (!isConvexHull()) {
            printf("HOLE IS ILL-FORMED\n");
            continue;
        }

        if (isPointInPolygon(cir,p)!=1) {
            printf("PEG WILL NOT FIT\n");
            continue;
        }

        bool flag = 1;
        for (int i=0; i<n-1; i++) {
            if (dcmp(DistanceToLine(cir,p[i],p[i+1])-r)<0) {flag = 0; break;}
        }
        if (!flag) printf("PEG WILL NOT FIT\n");
        else printf("PEG WILL FIT\n");

    }
    return 0;
}
