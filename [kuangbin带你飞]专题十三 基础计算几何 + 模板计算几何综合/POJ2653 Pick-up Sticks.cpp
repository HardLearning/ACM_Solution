#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-6;
int dcmp(double x){
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

struct Point{
   double x,y;
   Point (double x=0, double y=0): x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p,A.y*p); }

double Dot(Vector A,Vector B) { return A.x*B.x + A.y*B.y; }
double Cross(Vector A,Vector B) { return A.x*B.y - A.y*B.x; }

struct Line{
   Point p1,p2;
   Line() {}
   Line(Point p1,Point p2):p1(p1),p2(p2) { }
};

const int maxn = 100000+10;
int n;
bool flag[maxn];
Line line[maxn];

bool SegmentIntersection(Line L1, Line L2){
   double c1 = Cross(L1.p2-L1.p1,L2.p1-L1.p1);
   double c2 = Cross(L1.p2-L1.p1,L2.p2-L1.p1);
   double c3 = Cross(L2.p2-L2.p1,L1.p1-L2.p1);
   double c4 = Cross(L2.p2-L2.p1,L1.p2-L2.p1);
   return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

int main(){
    while (scanf("%d",&n)==1 && n){
        double x1,y1,x2,y2;
        memset(flag,1,sizeof(flag));

        for (int i=1; i<=n; i++) {
           scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
           line[i] = Line(Point(x1,y1),Point(x2,y2));
        }

        for (int i=1; i<n; i++) {
           for (int j=i+1; j<=n; j++)
             if (SegmentIntersection(line[i],line[j])) {
                flag[i] = 0;
                break;
             }
        }
        printf("Top sticks:");
        for (int i=1; i<n; i++) if (flag[i]) printf(" %d,",i);
        printf(" %d.\n",n);
    }
    return 0;
}
