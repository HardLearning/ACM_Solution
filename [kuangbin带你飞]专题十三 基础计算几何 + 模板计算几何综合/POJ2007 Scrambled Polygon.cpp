#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

struct Point{
   double x,y;
   Point (double x=0, double y=0):x(x),y(y){}
};

typedef Point Vector;
double Cross(Vector A, Vector B) { return A.x*B.y-A.y*B.x; }

const int maxn = 55;
int n;
Point p[maxn];

bool cmp(Point a, Point b){
   return Cross(a,b)>0;
}

int main(){
    n = 0;
    double x,y;
    while (scanf("%lf%lf",&x,&y)!=EOF){
        p[n++] = Point(x,y);
    }
    sort(p+1,p+n,cmp);
    for (int i=0; i<n; i++) cout<<"("<<p[i].x<<","<<p[i].y<<")"<<endl;
    return 0;
}
