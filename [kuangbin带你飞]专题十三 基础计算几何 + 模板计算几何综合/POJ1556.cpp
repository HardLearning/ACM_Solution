#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define pb push_back
const double eps = 1e-8;
int dcmp(double x){
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

struct Point{
    double x,y;
    Point (double x=0, double y=0):x(x),y(y){}
};

typedef Point Vector;

Vector operator +(Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y);}
Vector operator -(Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y);}
Vector operator *(Vector A, double p) { return Vector(A.x*p,A.y*p);}

double Dot(Vector A,Vector B) {return A.x*B.x+A.y*B.y;}
double Cross(Vector A,Vector B) {return A.x*B.y-A.y*B.x;}
double Length(Vector A) { return sqrt(Dot(A,A)); }

struct Line{
   Point p1,p2;
   Line(){}
   Line(Point p1,Point p2):p1(p1),p2(p2){}
};

bool isLineIntersection(Line a, Line b){
   double c1 = Cross(a.p2-a.p1,b.p1-a.p1), c2 = Cross(a.p2-a.p1,b.p2-a.p1);
   double c3 = Cross(b.p2-b.p1,a.p1-b.p1), c4 = Cross(b.p2-b.p1,a.p2-b.p1);
   return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

int n,m,l;
Point s = Point(0,5);
Point t = Point(10,5);
vector<Point>p;
vector<Line>lines;
double x,Y1,Y2,Y3,Y4;

struct Edge{
    int from,to;
    double cost;
};
const int maxn = 100;
vector<int>G[maxn];
vector<Edge>edges;

bool judge(Line a){
    int i=0, j = l-1;
    while (i<l && dcmp(lines[i].p1.x-a.p1.x)<=0) i++;
    while (j>=0 && dcmp(lines[j].p2.x-a.p2.x)>=0) j--;

    for (int k=i; k<=j; k++) if (isLineIntersection(a,lines[k])) return 0;
    return 1;
}

const double INF = 500;
struct HeapNode{
     int u;
     double d;
     bool operator <(const HeapNode& rhs) const {
        return dcmp(d-rhs.d)>0;
     }
};
bool done[maxn];
double dis[maxn];
priority_queue<HeapNode>que;

double Dijkstra(){
    memset(done,0,sizeof(done));
    for (int i=0; i<maxn; i++) dis[i] = INF;
    while (!que.empty()) que.pop();

    que.push((HeapNode){0,0});
    dis[0] = 0;

    int u;
    HeapNode x;
    while (!que.empty()){
         x = que.top();
         que.pop();

         u = x.u;
         if (done[u]) continue;
         done[u] = 1;
         for (int i=0; i<G[u].size(); i++) {
            Edge& e = edges[G[u][i]];
            if (dcmp(dis[e.to]-dis[u]-e.cost)>0) {
                dis[e.to] = dis[u] + e.cost;
                que.push((HeapNode){e.to,dis[e.to]});
            }
         }
    }
    return dis[m-1];
}

void BuildGraph(){
    m = p.size();
    l = lines.size();
    for (int i=0; i<maxn; i++) G[i].clear();
    edges.clear();

    Line L;
    for (int i=0; i<m-1; i++) {
        for (int j=i+1; j<m; j++) {
            if (dcmp(p[i].x-p[j].x)==0) continue;
            L = Line(p[i],p[j]);
            if (judge(L)) {
                edges.pb((Edge){i,j,Length(p[i]-p[j])});
                G[i].pb(edges.size()-1);
            }
        }
    }
}

int main(){
    while (scanf("%d",&n)==1 && n!=-1){
        lines.clear();
        p.clear();
        p.pb(s);
        for (int i=1; i<=n; i++) {
            scanf("%lf%lf%lf%lf%lf",&x,&Y1,&Y2,&Y3,&Y4);
            p.pb(Point(x,Y1)); p.pb(Point(x,Y2));
            p.pb(Point(x,Y3)); p.pb(Point(x,Y4));

            m = p.size();
            lines.pb(Line(Point(x,0),p[m-4]));
            lines.pb(Line(p[m-3],p[m-2]));
            lines.pb(Line(p[m-1],Point(x,10)));

        }
        p.pb(t);

        BuildGraph();
        printf("%.2f\n",Dijkstra());
    }
    return 0;
}
