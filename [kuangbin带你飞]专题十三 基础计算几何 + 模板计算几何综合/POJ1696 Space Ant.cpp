#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-6;
int dcmp(double x){
   if (fabs(x)<eps) return 0;
   return x<0?-1:1;
}

struct Point{
   int x,y;
   int idx;
   Point(int x=0,int y=0, int idx = 0):x(x),y(y),idx(idx) { }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y); }

int Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
int Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A,A)); }

const int maxn = 100;
int n,id;
Point p[maxn];

bool cmp(Point a, Point b){
    int c = Cross(a-p[id],b-p[id]);
    if (c>0) return 1;
    if (c==0) {
        if (dcmp(Length(a-p[id])-Length(b-p[id]))<0 ) return 1;
        return 0;
    }
    return 0;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);

        int x,y,idx;
        for (int i=1; i<=n; i++) {
             scanf("%d %d %d",&idx,&x,&y);
             p[i] = Point(x,y,idx);
             if (p[i].y<p[1].y || (p[i].y==p[1].y && p[i].x<p[1].x)) swap(p[i],p[1]);
        }
        id = 1;

        for (int i=2; i<=n; i++) {
            sort(p+id+1,p+n+1,cmp);
            id++;
        }

        printf("%d",n);
        for (int i=1; i<=n; i++) printf(" %d",p[i].idx);
        printf("\n");

    }
    return 0;
}
