#include <cstdio>
#include <cmath>
using namespace std;

const double PI = acos(-1.0);
const double eps = 1e-6;
int dcmp(double x){
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

struct Point{
   double x,y;
   Point(double x=0, double y=0):x(x),y(y){}
};

typedef Point Vector;

Vector operator +(Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator -(Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y); }

double Cross(Vector A, Vector B) { return A.x*B.y-A.y*B.x; }
double Dot(Vector A, Vector B) { return A.x*B.x+A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A,A));}
double calc(Vector A, Vector B) { return acos(Dot(A,B)/Length(A)/Length(B))*180.0/PI; }

const int maxn = 100+5;
int n;
Point p[maxn];

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
       scanf("%d",&n);
       double x,y;
       for (int i=1; i<=n; i++) {
           scanf("%lf%lf",&x,&y);
           p[i] = Point(x,y);
       }

       int ans = 0;
       double ang1,ang2,ang3;

       for (int i=1; i<=n; i++) {
          for (int j=i+1; j<=n; j++) {
              for (int k=j+1; k<=n; k++) {
                 if (dcmp(Cross(p[i]-p[j],p[i]-p[k]))==0 ) continue;

                 ang1 = calc(p[j]-p[i],p[k]-p[i]);
                 ang2 = calc(p[i]-p[j],p[k]-p[j]);
                 ang3 = calc(p[i]-p[k],p[j]-p[k]);

                 if (dcmp(ang1-90)<0 && dcmp(ang2-90)<0 && dcmp(ang3-90)<0) ans++;
              }
          }
       }

       printf("%d\n",ans);
    }
    return 0;
}
