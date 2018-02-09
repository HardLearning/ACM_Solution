#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

const double eps = 1e-6;
int dcmp(double x){
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

struct Point{
   double x,y;
   Point (double x=0, double y=0): x(x),y(y) {}
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p,A.y*p); }

double Cross(Vector A, Vector B) { return A.x*B.y-A.y*B.x; }

struct Line{
   Point p1,p2;
   Line() {}
   Line(Point p1,Point p2):p1(p1),p2(p2) {}
};

bool SegmentIntersection(Line a, Line b){
   double c1 = Cross(a.p2-a.p1,b.p1-a.p1);
   double c2 = Cross(a.p2-a.p1,b.p2-a.p1);
   double c3 = Cross(b.p2-b.p1,a.p1-b.p1);
   double c4 = Cross(b.p2-b.p1,a.p2-b.p1);
   return dcmp(c1)*dcmp(c2)<=0 && dcmp(c3)*dcmp(c4)<=0;
}

const int INF = 1e15;
const int maxn = 100;
int n;
Point p[maxn];
Line line[maxn];

inline int Min(int x, int y) { return x<y?x:y; }

int main(){
    while (scanf("%d",&n)==1){
        double x1,y1,x2,y2;
        for (int i=1; i<=n; i++) {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            p[2*i-1] = Point(x1,y1);
            p[2*i] = Point(x2,y2);
            line[i] = Line(p[2*i],p[2*i-1]);
        }

        double x,y;
        Point s;
        scanf("%lf%lf",&x,&y);
        s = Point(x,y);

        if (n==0)  { printf("Number of doors = 1\n"); continue; }

        int ans = INF,sum;
        Line L;
        for (int i=1; i<=2*n; i++) {
            L = Line(s,p[i]);
            sum = 0;
            for (int j=1; j<=n; j++)
                if (SegmentIntersection(L,line[j])) sum++;
            ans = Min(ans,sum);
        }

        printf("Number of doors = %d\n",ans);
    }
    return 0;
}
