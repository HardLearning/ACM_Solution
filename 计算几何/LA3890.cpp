#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

struct Point {
   double x,y;
   Point (double x=0, double y=0): x(x),y(y) {}
};
typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p,A.y*p); }

double Dot(Vector A, Vector B) { return A.x*B.x+A.y*B.y; }
double Cross(Vector A, Vector B) { return A.x*B.y-A.y*B.x; }
double Length(Vector A) { return sqrt(Dot(A,A)); }
Vector Normal( Vector A) { double L = Length(A); return Vector(-A.y/L,A.x/L); }

double PolygonArea(vector<Point>p) {
    int n = p.size();
    double area = 0;
    for (int i=1; i<n-1; i++) area += Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}

struct Line{
   Point P;
   Vector v;
   double ang;
   Line() {}
   Line(Point P,Vector v): P(P), v(v) { ang = atan2(v.y,v.x); }
   bool operator <(const Line & rhs) const {
      return ang < rhs.ang;
   }
};

bool OnLeft(Line L, Point p) {
    return Cross(L.v,p-L.P)>0;
}

Point GetLineIntersection(Line a, Line b) {
    Vector u = a.P - b.P;
    double t = Cross(b.v,u) / Cross(a.v,b.v);
    return a.P + a.v*t;
}

const double INF = 1e8;
const double eps = 1e-8;

vector<Point> HalfplaneIntersection(vector<Line>L){
    int n = L.size();
    sort(L.begin(),L.end());

    int first,last;
    vector<Point>p(n);
    vector<Line>q(n);
    vector<Point>ans;

    q[first = last = 0] = L[0];
    for (int i=1; i<n; i++) {
        while (first < last && !OnLeft(L[i],p[last-1])) last--;
        while (first < last && !OnLeft(L[i],p[first])) first++;
        q[++last] = L[i];
        if ( fabs(Cross(q[last].v,q[last-1].v))<eps ) {
            last--;
            if (OnLeft(q[last],L[i].P)) q[last] = L[i];
        }
        if (first<last) p[last-1] = GetLineIntersection(q[last-1],q[last]);
    }

    while (first<last && !OnLeft(q[first],p[last-1])) last--;
    if (last-first<=1) return ans;
    p[last] = GetLineIntersection(q[last],q[first]);

    for (int i=first; i<= last; i++) ans.push_back(p[i]);
    return ans;
}

int main(){
    int n;
    while (scanf("%d",&n)==1 && n) {
        vector<Vector>p,v,v2;
        double x,y;

        for (int i=0; i<n; i++) scanf("%lf%lf",&x,&y),p.push_back(Point(x,y));
        if (PolygonArea(p) < 0) reverse(p.begin(),p.end());

        for (int i=0; i<n; i++) {
            v.push_back(p[(i+1)%n]-p[i]);
            v2.push_back(Normal(v[i]));
        }

        double left = 0, right = 20000, mid;
        while (right-left>eps){
            vector<Line>L;
            double mid = (left+right)/2;
            for (int i=0; i<n; i++) L.push_back(Line(p[i]+v2[i]*mid,v[i]));
            vector<Point>poly = HalfplaneIntersection(L);
            if (poly.empty()) right = mid; else left = mid;
        }

        printf("%.6lf\n",left);
    }
    return 0;
}
