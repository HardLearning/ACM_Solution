#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-8;
int dcmp(double x){
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

const int maxn = 310;
struct Point{
   double x,y;
   Point (double x=0, double y=0):x(x),y(y){};
}p[maxn];
double R;
double x,y;
int n;

typedef Point Vector;
Vector operator +(Vector A, Vector B) {return Vector(A.x+B.x,A.y+B.y); }
Vector operator -(Vector A, Vector B) {return Vector(A.x-B.x,A.y-B.y); }
Vector operator *(Vector A, double p) {return Vector(A.x*p,A.y*p); }

double Dot(Vector A,Vector B) {return A.x*B.x+A.y*B.y; }
double Cross(Vector A,Vector B) {return A.x*B.y-A.y*B.x;}
double Length(Vector A) {return sqrt(Dot(A,A)); }

bool OnSegment(Point p,Point a1, Point a2){
   return dcmp(Cross(a1-p,a2-p))==0 && dcmp(Dot(a1-p,a2-p))<0;
}

typedef long long LL;
const LL mod = 10007;
LL mat[maxn][maxn];

void build_map(){
   bool flag;
   memset(mat,0,sizeof(mat));
   for (int i=1; i<=n; i++) {
      for (int j=i+1; j<=n; j++) if (dcmp(Length(p[i]-p[j])-R)<=0) {
         flag = 1;
         for (int k=1; k<=n; k++) if (i!=k && j!=k) {
             if (OnSegment(p[k],p[i],p[j])) {
                flag = 0;
                break;
             }
         }
         if (flag) {
             mat[i][j] = mat[j][i] = -1;
             mat[i][i]++; mat[j][j]++;
         }
      }
   }

}

LL det(int n){
   LL ret = 1;
   bool flag;

   for (int i=1; i<=n; i++) {
       if (mat[i][i]==0) {
           flag = 0;
           for (int j=i+1; j<=n; j++) if (!mat[j][i]) {
              flag = 1;
              for (int k=i; k<=n; k++) swap(mat[i][k],mat[j][k]);
              ret = -ret;
              break;
           }
           if (flag==0) return -1;
       }

       for (int j=i+1; j<=n; j++) {
          while (mat[j][i]) {
             LL t = mat[i][i]/mat[j][i];
             for (int k=i; k<=n; k++) {
                mat[i][k] -= mat[j][k]*t;
                mat[i][k] %= mod;
                swap(mat[i][k],mat[j][k]);
             }
             ret = -ret;
          }
       }
       ret = ret*mat[i][i]%mod;
   }

   return (ret+mod)%mod;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
       scanf("%d%lf",&n,&R);
       for (int i=1; i<=n; i++) {
          scanf("%lf%lf",&x,&y);
          p[i] = Point(x,y);
       }
       build_map();

       LL ans = det(n-1);
       printf("%I64d\n",ans);
    }
    return 0;
}
