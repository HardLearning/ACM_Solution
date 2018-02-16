#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define pb push_back
struct Point{
   int x,y;
   Point(int x=0, int y=0):x(x),y(y){}
   bool operator <(const Point& rhs) const{
      return x<rhs.x || (x==rhs.x && y<rhs.y);
   }
};


typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y); }

int Cross(Vector A, Vector B) { return A.x*B.y-A.y*B.x; }
double dist(Vector A, Vector B) { return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y)); }

int ConvexHull(vector<Point>& p){
     int n = p.size();
     Point ch[300+10];

     int m=0;
     for (int i=0; i<n; i++){
         while (m>1 && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
         ch[m++] = p[i];
     }

     int k=m;
     for (int i=n-2; i>=0; i--) {
        while (m>k && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0 ) m--;
        ch[m++] = p[i];
     }
     if (n>1) m--;
     return m;
}

const int INF = 1e9;
const int maxn = 300+5;
vector<Point>P;
int n,p;
int x,y;
int dp[maxn][maxn];
int cost[maxn][maxn];

inline int Min(int x, int y) {return x<y?x:y; }
inline int Cost(int a,int b){
   return abs(P[a].x+P[b].x)%p*abs(P[a].y+P[b].y)%p;
}

int DP(int a, int b){
   if (dp[a][b]!=INF) return dp[a][b];
   int ans = INF;
   for (int i=a+1; i<b; i++) ans = Min(ans,cost[a][i]+cost[i][b]+DP(a,i)+DP(i,b));
   return dp[a][b] = ans;
}

bool cmp(Point p1, Point p2){
   int tmp = Cross(p1-P[0],p2-P[0]);
   if (tmp>0) return 1;
   if (tmp==0 && dist(P[0],p1)<dist(P[0],p2)) return 1;
   return 0;
}

void init(){
   P.clear();
   int x,y;
   scanf("%d%d",&x,&y);
   P.pb(Point(x,y));
   int tmp = 0;
   Point p0 = P[0];

   for (int i=1; i<n; i++) {
      scanf("%d%d",&x,&y);
      P.pb((Point){x,y});
      if (y<p0.y || (y==p0.y && x<p0.x)) {
            tmp = i;
            p0.x = x;
            p0.y = y;
      }
   }

   P[tmp] = P[0];
   P[0] = p0;
   sort(P.begin()+1,P.end(),cmp);
}

int main(){
    while (scanf("%d%d",&n,&p)==2){
        init();

        if (ConvexHull(P)!=n) { printf("I can't cut.\n"); continue; }

        memset(cost,0,sizeof(cost));
        for (int i=0; i<n; i++)
            for (int j=i+2; j<n; j++) cost[i][j] = cost[j][i] = Cost(i,j);
        for (int i=0; i<n; i++) {
          for (int j=0; j<n; j++) dp[i][j] = INF;
          dp[i][(i+1)%n] = 0;
        }
        printf("%d\n",DP(0,n-1));
    }
    return 0;
}
