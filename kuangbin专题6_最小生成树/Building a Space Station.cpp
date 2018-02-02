#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
const int maxn = 100+5;
struct Edge{
   int u,v;
   double d;
   bool operator <(const Edge& rhs) const {
      return d < rhs.d;
   }
}e[maxn*maxn];
int tot,n;
int fa[maxn];

struct node{
    double x,y,z,r;
}ball[maxn];

inline int dcmp(double x){
    if (fabs(x)<eps) return 0;
    return x<0?-1:1;
}

void init(){
     for (int i=1; i<=n; i++) scanf("%lf %lf %lf %lf",&ball[i].x,&ball[i].y,&ball[i].z,&ball[i].r);
     tot = 0;
     for (int i=2; i<=n; i++)
       for (int j=1; j<i; j++) {
            double dis = sqrt((ball[i].x-ball[j].x)*(ball[i].x-ball[j].x)+(ball[i].y-ball[j].y)*(ball[i].y-ball[j].y)+(ball[i].z-ball[j].z)*(ball[i].z-ball[j].z));
            dis = dis - ball[i].r - ball[j].r;
            if (dcmp(dis)<=0) dis = 0;
            e[tot].u = i; e[tot].v = j; e[tot].d = dis;
            tot++;
     }
}

int Find(int x){
   if (fa[x]==-1) return x;
   return fa[x] = Find(fa[x]);
}

void kruskal(){
    memset(fa,-1,sizeof(fa));
    sort(e,e+tot);

    int u,v;
    double ans = 0;
    for (int i=0; i<tot; i++) {
         u = Find(e[i].u);
         v = Find(e[i].v);
         if (u!=v) {
             ans += e[i].d;
             fa[u] = v;
         }
    }
    printf("%.3f\n",ans);
}

int main(){
    while (scanf("%d",&n)==1 && n){
        init();
        kruskal();
    }
    return 0;
}
