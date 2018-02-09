#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const double PI = acos(-1.0);
const double eps = 1e-6;
int dcmp(double x){
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

struct Point{
   double x,y;
   Point (double x=0, double y=0): x(x),y(y) { }
   bool operator <(const Point &rhs ) const {
      return dcmp(x-rhs.x)<0 || ( dcmp(x-rhs.x)==0 && dcmp(y-rhs.y)<0 );
   }
   bool operator ==(const Point &rhs ) const {
      return dcmp(x-rhs.x)==0 && dcmp(y-rhs.y)==0;
   }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p,A.y*p); }
Vector operator / (Vector A, double p) { return Vector(A.x/p,A.y/p); }

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Cross(Vector A, Vector B) { return A.x*B.y-A.y*B.x; }
double Length(Vector A) { return sqrt(Dot(A,A)); }
double Angle(Vector A, Vector B) { return acos(Dot(A,B)/Length(A)/Length(B)); }

Vector Rotate(Vector A, double rad) {
   return Vector( A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad) );
}

Vector Normal(Vector A) {
   double L = Length(A);
   return Vector(-A.y/L,A.x/L);
}

Point GetLineIntersection(Point P, Vector v, Point Q, Vector w) {
    Vector u = P-Q;
    double t = Cross(w,u)/Cross(v,w);
    return P + v*t;
}

Point GetLineProjection(Point P, Point A, Point B) {
    Vector v = B-A;
    return A+v*(Dot(v,P-A)/Dot(v,v));
}

double DistanceToLine(Point P, Point A, Point B){
    Vector v1 = B-A, v2 = P-A;
    return fabs(Cross(v1,v2))/Length(v1);
}

struct Line {
   Point p;
   Vector v;
   Line(Point p, Vector v): p(p),v(v) { }
   Point point(double t) {
       return p + v*t;
   }
   Line move(double d) {
       return Line(p+Normal(v)*d,v);
   }
};

struct Circle{
   Point c;
   double r;
   Circle(Point c, double r): c(c),r(r) { }
   Point point(double a){
       return Point(c.x+cos(a)*r,c.y+sin(a)*r);
   }
};

Point GetLineIntersection(Line a, Line b) {
   return GetLineIntersection(a.p,a.v,b.p,b.v);
}

double angle(Vector v){
    return atan2(v.y,v.x);
}

int getLineCircleIntersection(Line L, Circle C, double &t1, double &t2, vector<Point>& sol){
    double a = L.v.x, b = L.p.x-C.c.x, c = L.v.y, d = L.p.y-C.c.y;
    double e = a*a+c*c, f = 2*(a*b+c*d), g = b*b + d*d - C.r*C.r;
    double delta = f*f - 4*e*g;

    if (dcmp(delta)<0) return 0;
    if (dcmp(delta)==0) {
        t1 = t2 = -f / (2*e);
        sol.push_back(L.point(t1));
        return 1;
    }

    t1 = (-f -sqrt(delta)) / (2*e); sol.push_back(L.point(t1));
    t2 = (-f +sqrt(delta)) / (2*e); sol.push_back(L.point(t2));
    return 2;

}

int getCircleCircleIntersection(Circle C1,Circle C2,vector<Point>&sol){
    double d = Length(C1.c - C2.c);
    if (dcmp(d) == 0) {
        if (dcmp(C1.r-C2.r)==0) return -1;
        return 0;
    }
    if (dcmp(C1.r+C2.r-d)<0) return 0;
    if (dcmp(fabs(C1.r-C2.r)-d)>0) return 0;

    double a = angle(C2.c-C1.c);
    double da = acos( (C1.r*C1.r+d*d-C2.r*C2.r)/(2*C1.r*d) );
    Point p1 = C1.point(a-da), p2 = C1.point(a+da);

    sol.push_back(p1);
    if (p1==p2) return 1;
    sol.push_back(p2);
    return 2;
}

/* problem 1 */
Circle CircumscribedCircle(Point p1, Point p2, Point p3){
   double Bx = p2.x-p1.x, By = p2.y-p1.y;
   double Cx = p3.x-p1.x, Cy = p3.y-p1.y;
   double D = 2*(Bx*Cy-By*Cx);
   double cx = (Cy*(Bx*Bx+By*By)-By*(Cx*Cx+Cy*Cy))/D + p1.x;
   double cy = (Bx*(Cx*Cx+Cy*Cy)-Cx*(Bx*Bx+By*By))/D + p1.y;
   Point p = Point(cx,cy);
   return Circle(p,Length(p1-p));
}

/* problem 2 */
Circle InscribedCircle(Point p1, Point p2, Point p3){
     double a = Length(p2-p3);
     double b = Length(p3-p1);
     double c = Length(p1-p2);
     Point p = (p1*a + p2*b + p3*c)/(a+b+c);
     return Circle(p,DistanceToLine(p,p1,p2));
}

/* problem 3 */
int getTangents(Point p, Circle C, Vector *v){
   Vector u = C.c - p;
   double dist = Length(u);
   if (dist < C.r) return 0;
   else if (dcmp(dist-C.r) == 0) {
      v[0] = Rotate(u,PI/2);
      return 1;
   }
   else {
      double ang = asin(C.r/dist);
      v[0] = Rotate(u,-ang);
      v[1] = Rotate(u,+ang);
      return 2;
   }
}

/* problem 4 */
vector<Point> CircleThroughPointTangentToLineGivenRadius(Point p, Line L, double r) {
    vector<Point> ans;
    double t1,t2;
    getLineCircleIntersection(L.move(-r),Circle(p,r),t1,t2,ans);
    getLineCircleIntersection(L.move(r),Circle(p,r),t1,t2,ans);
    return ans;
}

vector<Point> CircleTangentToLinesGivenRadius(Line a, Line b, double r){
    vector<Point> ans;
    Line L1 = a.move(-r), L2 = a.move(r);
    Line L3 = b.move(-r), L4 = b.move(r);
    ans.push_back(GetLineIntersection(L1,L3));
    ans.push_back(GetLineIntersection(L2,L3));
    ans.push_back(GetLineIntersection(L1,L4));
    ans.push_back(GetLineIntersection(L2,L4));
    return ans;
}

vector<Point> CircleTangentToTwoDisJointCirclesWithRadius(Circle c1, Circle c2, double r) {
    vector<Point> ans;
    Vector v = c2.c - c1.c;
    double dist = Length(v);
    int d = dcmp(dist-c1.r-c2.r-r*2);
    if (d>0) return ans;
    getCircleCircleIntersection(Circle(c1.c,c1.r+r),Circle(c2.c,c2.r+r),ans);
    return ans;
}

//formatting
double lineAngleDegree(Vector v){
    double ang = angle(v)*180.0/PI;
    while (dcmp(ang)<0) ang += 360.0;
    while (dcmp(ang-180)>=0) ang -= 180.0;
    return ang;
}

void format(Circle c){
   printf("(%.6f,%.6f,%6f)\n",c.c.x,c.c.y,c.r);
}

void format(vector<double> ans){
    int n = ans.size();
    sort(ans.begin(),ans.end());
    printf("[");
    if (n){
        printf("%.6f",ans[0]);
        for (int i=1; i<n; i++) printf(",%.6f",ans[i]);
    }
    printf("]\n");
}

void format(vector<Point> ans){
   int n = ans.size();
   sort(ans.begin(),ans.end());
   printf("[");
   if (n) {
      printf("(%.6f,%.6f)",ans[0].x,ans[0].y);
      for (int i=1; i<n; i++) printf(",(%.6f,%.6f)",ans[i].x,ans[i].y);
   }
   printf("]\n");
}

Line getLine(double x1, double y1, double x2, double y2){
   Point p1(x1,y1);
   Point p2(x2,y2);
   return Line(p1,p2-p1);
}

int main(){
    char cmd[100];
    double X1,Y1,X2,Y2,X3,Y3,X4,Y4;
    double xp,yp,xc,yc,r1,r2,r;
    while (scanf("%s",cmd)!=EOF){
       if (strcmp(cmd,"CircumscribedCircle")==0) {
          scanf("%lf%lf%lf%lf%lf%lf",&X1,&Y1,&X2,&Y2,&X3,&Y3);
          format(CircumscribedCircle(Point(X1,Y1),Point(X2,Y2),Point(X3,Y3)));
          continue;
       }

       if (strcmp(cmd,"InscribedCircle")==0) {
          scanf("%lf%lf%lf%lf%lf%lf",&X1,&Y1,&X2,&Y2,&X3,&Y3);
          format(InscribedCircle(Point(X1,Y1),Point(X2,Y2),Point(X3,Y3)));
          continue;
       }

       if (strcmp(cmd,"TangentLineThroughPoint")==0) {
          scanf("%lf%lf%lf%lf%lf",&xc,&yc,&r,&xp,&yp);
          Vector v[2];
          vector<double>ans;
          int cnt = getTangents(Point(xp,yp),Circle(Point(xc,yc),r),v);
          for (int i=0; i<cnt; i++) ans.push_back(lineAngleDegree(v[i]));
          format(ans);
          continue;
       }

       if (strcmp(cmd,"CircleThroughAPointAndTangentToALineWithRadius")==0){
            scanf("%lf%lf%lf%lf%lf%lf%lf",&xp,&yp,&X1,&Y1,&X2,&Y2,&r);
            format(CircleThroughPointTangentToLineGivenRadius(Point(xp,yp),getLine(X1,Y1,X2,Y2),r));
            continue;
       }

       if (strcmp(cmd,"CircleTangentToTwoLinesWithRadius")==0) {
           scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf",&X1,&Y1,&X2,&Y2,&X3,&Y3,&X4,&Y4,&r);
           format(CircleTangentToLinesGivenRadius(getLine(X1,Y1,X2,Y2),getLine(X3,Y3,X4,Y4),r));
           continue;
       }

       if (strcmp(cmd,"CircleTangentToTwoDisjointCirclesWithRadius")==0) {
            scanf("%lf%lf%lf%lf%lf%lf%lf",&X1,&Y1,&r1,&X2,&Y2,&r2,&r);
            format(CircleTangentToTwoDisJointCirclesWithRadius(Circle(Point(X1,Y1),r1),Circle(Point(X2,Y2),r2),r));
       }
    }
    return 0;
}
