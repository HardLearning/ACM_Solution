#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 1000+5;
int n,m;
int ans[maxn],cnt[maxn];

struct Point{
     int x,y;
     Point(int x=0, int y=0): x(x),y(y) {}
};
typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A, int p) { return Vector(A.x*p,A.y*p); }

int Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }

struct Line{
    Point p1,p2;
    Line() {}
    Line(Point p1, Point p2) : p1(p1),p2(p2) { }
    bool operator < (const Line &rhs) const {
        return p1.x < rhs.p1.x;
    }
};

Line line[maxn];
int X1,Y1,X2,Y2;

void init(){
    int u,l;
    Point p1,p2;

    scanf("%d %d %d %d %d",&m,&X1,&Y1,&X2,&Y2);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&u,&l);
        p1 = Point(u,Y1);
        p2 = Point(l,Y2);
        line[i] = Line(p1,p2);
    }
    p1 = Point(X2,Y1);
    p2 = Point(X2,Y2);
    line[n] = Line(p1,p2);
    sort(line,line+n+1);
}

bool OnLeft(Point p, Line L) {
    return Cross(L.p1-p,L.p2-p) < 0 ;
}

int main(){
    while (scanf("%d",&n)==1 && n) {
        init();

        memset(ans,0,sizeof(ans));
        memset(cnt,0,sizeof(cnt));
        int x,y;
        int left,right,mid,pt;

        int tmp = m;
        while (tmp--) {
           scanf("%d %d",&x,&y);
           Point p = Point(x,y);

           left = 0;
           right = n;
           while (left<=right) {
               mid = (left+right)>>1;
               if (OnLeft(p,line[mid])) {
                   pt = mid;
                   right = mid-1;
               }
               else left = mid+1;
           }
           ans[pt]++;
        }

        printf("Box\n");
        for (int i=0; i<=n; i++) cnt[ans[i]]++;
        for (int i=1; i<=m; i++) if (cnt[i]) printf("%d: %d\n",i,cnt[i]);
    }
    return 0;
}
