#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

const double eps = 1e-8;
int dcmp(double x){
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

struct Point{
   double x,y,z;
   int idx,cap;
   Point (double x=0, double y=0, double z=0,int idx=0, int cap=0):x(x),y(y),z(z),idx(idx),cap(cap){};
};

typedef Point Vector;
Vector operator -(Vector A,Vector B) {return Vector(A.x-B.x,A.y-B.y,A.z-B.z); }
double Dot(Vector A,Vector B) {return A.x*B.x+A.y*B.y+A.z*B.z; }
double Length(Vector A) {return sqrt(Dot(A,A)); }

const int maxn = 200+5;
double d[maxn][maxn];
int n;
Point lanch[maxn],receive[maxn];

struct Edge{
   int v,c;
   double dis;
}e[maxn];
bool cmp(Edge a, Edge b) {
   return dcmp(a.dis-b.dis)<0 || dcmp(a.dis-b.dis)==0 && a.c>b.c;
}

queue<int>que;
int future_husband[maxn],future_wife[maxn];
int nxt[maxn];
int pref[maxn][maxn],order[maxn][maxn];

void engage(int man, int woman) {
   int m = future_husband[woman];
   if (m) {
       future_wife[m] = 0;
       que.push(m);
   }
   future_wife[man] = woman;
   future_husband[woman] = man;
}

void solve(){
   while (!que.empty()) que.pop();
   for (int i=1; i<=n; i++) {
        nxt[i] = 1;
        future_wife[i] = 0;
        future_husband[i] = 0;
        que.push(i);
   }

   while (!que.empty()){
      int man = que.front(); que.pop();
      int woman = pref[man][nxt[man]++];
      if (!future_husband[woman]) engage(man,woman);
      else if (order[woman][man]<order[woman][future_husband[woman]]) engage(man,woman);
      else que.push(man);
   }
   while (!que.empty()) que.pop();

   for (int i=1; i<=n; i++) printf("%d %d\n",i,future_wife[i]);
   printf("\n");
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        double x,y,z;
        int idx,cap;
        for (int i=1; i<=n; i++) {
            scanf("%d%d%lf%lf%lf",&idx,&cap,&x,&y,&z);
            lanch[i] = Point(x,y,z,idx,cap);
        }
        for (int i=1; i<=n; i++) {
            scanf("%d%d%lf%lf%lf",&idx,&cap,&x,&y,&z);
            receive[i] = Point(x,y,z,idx,cap);
        }

        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++) d[lanch[i].idx][receive[j].idx] = Length(lanch[i]-receive[j]);

        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                e[j].v = receive[j].idx;
                e[j].c = receive[j].cap;
                e[j].dis = d[i][receive[j].idx];
            }
            sort(e+1,e+n+1,cmp);
            for (int j=1; j<=n; j++) pref[i][j] = e[j].v;
        }

        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                e[j].v = lanch[j].idx;
                e[j].c = lanch[j].cap;
                e[j].dis = d[lanch[j].idx][i];
            }
            sort(e+1,e+n+1,cmp);
            for (int j=1; j<=n; j++) order[i][e[j].v] = j;
        }

        solve();
    }
    return 0;
}
