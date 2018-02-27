#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
int dcmp(double x){
    if (fabs(x)<eps) return 0;
    return x<0?-1:1;
}

struct Point{
    double x,y,ang;
    Point(double x=0, double y=0):x(x),y(y){ }
};

typedef Point Vector;

Vector operator +(Vector A,Vector B) {return Vector(A.x+B.x,A.y+B.y); }
Vector operator -(Vector A,Vector B) {return Vector(A.x-B.x,A.y-B.y); }

double Cross(Vector A,Vector B) {return A.x*B.y-A.y*B.x;}
double Dot(Vector A,Vector B) {return A.x*B.x+A.y*B.y; }

const int maxn = 55;
int n;
Point p[maxn];
Point tp[maxn];

bool cmp1(Point a, Point b) {return dcmp(a.y-b.y)<0 || dcmp(a.y-b.y)==0 && dcmp(a.x-b.x)<0; }
bool cmp2(Point a, Point b) {return dcmp(a.ang-b.ang)<0 || dcmp(a.ang-b.ang)==0 && cmp1(a,b); }

int dp[maxn][maxn];
void update(Point* p, int n, int& ans){
    for (int i=0; i<n; i++) tp[i] = p[i];

    Point refer = tp[0];
    tp[0].ang = -2;

    for (int i=1; i<n; i++)  {
        Point tmp = tp[i]-refer;
        tp[i].ang = atan2(tmp.y,tmp.x);
    }
    sort(tp,tp+n,cmp2);

    for (int i=1; i<n; i++)
      for (int j=i+1; j<n; j++)
         dp[i][j] = 3;

    for (int i=1; i<n; i++)
        for (int j=i+1; j<n; j++)
          for (int k=j+1; k<n; k++)
             if (dp[i][j]>=dp[j][k] && Cross(tp[j]-tp[i],tp[k]-tp[j])>0) {
                 dp[j][k] = dp[i][j]+1;
                 ans = max(ans,dp[j][k]);
             }

}

int main(){
    int T;
    scanf("%d",&T);

    int kase = 0;
    while (T--){
        scanf("%d",&n);
        double x,y;
        for (int i=0; i<n; i++) {
            scanf("%lf%lf",&x,&y);
            p[i] = Point(x,y);
        }
        sort(p,p+n,cmp1);


        int ans = 3;
        for (int i=0; i<n; i++) {
            if (n-i<=ans) break;
            update(&p[i],n-i,ans);
        }

        printf("Case#%d: %d\n",++kase,ans);

    }
    return 0;
}
