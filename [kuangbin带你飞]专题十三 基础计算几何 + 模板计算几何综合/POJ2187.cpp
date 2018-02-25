#include <cstdio>
#include <algorithm>
using namespace std;

struct Point{
   int x,y;
   Point (int x=0, int y=0):x(x),y(y){}
};

typedef Point Vector;

Vector operator +(Vector A,Vector B) { return Vector(A.x+B.x,A.y+B.y); }
Vector operator -(Vector A,Vector B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator *(Vector A,double p) { return Vector(A.x*p,A.y*p); }

int Dot(Vector A,Vector B) { return A.x*B.x+A.y*B.y; }
int Cross(Vector A,Vector B) { return A.x*B.y-A.y*B.x; }
int Length(Vector A) { return Dot(A,A); }

const int maxn = 50000+10;
Point p[maxn],sol[maxn];
int n,m;

bool cmp(Point a, Point b){
   int ans = Cross(a-p[0],b-p[0]);
   return ans>0 || ans==0 && Length(a-p[0])<Length(b-p[0]);
}

int ConvexHull(Point *p,Point *ch){
    sort(p+1,p+n,cmp);
    int m = 0;
    for (int i=0; i<n; i++) {
        while (m>1 && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
        ch[m++] = p[i];
    }

    int k = m;
    for (int i=n-2; i>=0; i--){
        while (m>k && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
        ch[m++] = p[i];
    }

    if (n>1) m--;
    return m;
}

int Rotate_calipers(Point* ch, int n){
    int q=1;
    int ans = 0;
    ch[n] = ch[0];
    for (int i=0; i<n; i++) {
        while ( Cross(ch[q+1]-ch[i],ch[q+1]-ch[i+1])>Cross(ch[q]-ch[i],ch[q]-ch[i+1]) ) q = (q+1)%n;
        ans = max( ans,max( Length(ch[i]-ch[q]),Length(ch[i+1]-ch[q+1]) ) );
    }
    return ans;
}

int main(){
    while (scanf("%d",&n)==1){
        int x,y;
        for (int i=0; i<n; i++) {
            scanf("%d%d",&x,&y);
            p[i] = Point(x,y);
        }

        if (n==2) {
            printf("%d\n",Length(p[0]-p[1]));
            continue;
        }

        for (int i=1; i<n; i++) {
            if (p[i].x<p[0].x || p[i].x==p[0].x && p[i].y<p[0].y) swap(p[i],p[0]);
        }

        //sort(p+1,p+n,cmp);
        //for (int i=0; i<n; i++) printf("%d %d\n",p[i].x,p[i].y);

        m = ConvexHull(p,sol);
        //printf("%d\n",m);
        printf("%d\n",Rotate_calipers(sol,m));

    }
    return 0;
}
