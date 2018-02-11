#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const double  eps = 1e-6;

struct Point{
   double x,y;
   Point (double x=0,double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p,A.y*p); }

double Dot(Vector A, Vector B) { return A.x*B.x+A.y*B.y; }
double Cross(Vector A, Vector B) { return A.x*B.y-A.y*B.x; }

struct Line{
   Point p;
   Vector v;
   double ang;
   Line() {}
   Line(Point p, Vector v): p(p),v(v) {ang = atan2(v.y,v.x);}
   bool operator <(const Line &rhs) const {
          return ang<rhs.ang;
   }
};

bool OnLeft(Line L, Point P) {
    return Cross(L.v,P-L.p)>0;
}

Point GetLineIntersection(Line a, Line b){
    Vector u = a.p - b.p;
    double t = Cross(b.v,u)/Cross(a.v,b.v);
    return a.p+a.v*t;
}


vector<Point> HalfplaneIntersection(vector<Line>& L) {
  int n = L.size();
  sort(L.begin(), L.end());

  int first, last;
  vector<Point> p(n);
  vector<Line> q(n);
  vector<Point> ans;

  q[first=last=0] = L[0];
  for(int i = 1; i < n; i++) {
    while(first < last && !OnLeft(L[i], p[last-1])) last--;
    while(first < last && !OnLeft(L[i], p[first])) first++;
    q[++last] = L[i];
    if(fabs(Cross(q[last].v, q[last-1].v)) < eps) {
      last--;
      if(OnLeft(q[last], L[i].p)) q[last] = L[i];
    }
    if(first < last) p[last-1] = GetLineIntersection(q[last-1], q[last]);
  }
  while(first < last && !OnLeft(q[first], p[last-1])) last--;
  if(last - first <= 1) return ans;
  p[last] = GetLineIntersection(q[last], q[first]);


  for(int i = first; i <= last; i++) ans.push_back(p[i]);
  return ans;
}


const int maxn = 50000+10;
int n;
Point p[maxn];

bool judge(int m){
   vector<Line> lines;
   for (int i=0; i<n; i++) lines.push_back(Line(p[(i+m+1)%n],p[i]-p[(i+m+1)%n]));
   return HalfplaneIntersection(lines).empty();
}

int solve() {
  if(n == 3) return 1;
  int left = 1, right = n-3, mid;
  int ans;
  while(left <= right) {
    mid = (left+right)>>1;
    if(judge(mid)) {right = mid-1; ans = mid;} else left = mid+1;
  }
  return ans;
}

int main(){
    while (scanf("%d",&n)==1 && n){
        int x,y;
        for (int i=0; i<n; i++) {
            scanf("%d%d",&x,&y);
            p[i] = Point(x,y);
        }

        printf("%d\n",solve());
    }
    return 0;
}
